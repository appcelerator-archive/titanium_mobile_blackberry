/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiRootObject.h"

#include <bb/cascades/Page>
#include <bb/cascades/Sheet>
#include <bb/cascades/Container>
#include <bb/cascades/Label>
#include <bb/cascades/DockLayout>
#include <bb/cascades/Color>

#include "NativeStringInterface.h"
#include "TiGenericFunctionObject.h"
#include "TiLocaleObject.h"
#include "TiLogger.h"
#include "TiMessageStrings.h"
#include "TiTitaniumObject.h"
#include "TiTimeoutManager.h"
#include "TiV8EventContainerFactory.h"
#include "V8Utils.h"
#include <QSettings>
#include "TitaniumRuntime.h"

#include "TiModuleRegistry.h"
#include "TiCore.h"

#include "TiModule.h"
#include "tibb.h"

#include <fstream>
#include <sstream>

#include <QString>
#include <QUrl>

#include <unistd.h>
 #include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

#include "Modules/Filesystem/TiFilesystemModule.h"
#include "Modules/Geolocation/TiGeolocationModule.h"
#include "Modules/Platform/TiPlatformModule.h"
#include "Modules/Utils/TiUtilsModule.h"
#include "Modules/UI/BlackBerry/TiUIBlackberryModule.h"
#include "Modules/App/TiAppModule.h"
#include "Modules/Blackberry/TiBlackberryModule.h"

using namespace titanium;

static Handle<ObjectTemplate> g_rootTemplate;

static QMap<QString, v8::Persistent<Value> > _commonJSModules;
static QString ThrowJSException(TryCatch tryCatch)
{
	QString str;
	HandleScope scope;

	if(tryCatch.HasCaught())
    {
    	Handle<Message> message = tryCatch.Message();
    	if(!message.IsEmpty()) {
        	Handle<Value> fileName = message->GetScriptResourceName();
        	Local<String> srcLine = message->GetSourceLine();
        	Ti::TiHelper::Log(QString("File Name: ").append(Ti::TiHelper::QStringFromValue(fileName)));
        	Ti::TiHelper::Log(QString("Source Line: ").append(Ti::TiHelper::QStringFromValue(srcLine)));
        	str.append("File: ").append(Ti::TiHelper::QStringFromValue(fileName)).append("\n");
        	str.append("Source: ").append(Ti::TiHelper::QStringFromValue(srcLine)).append("\n\n");
    	}
    	QString stackTrace = Ti::TiHelper::QStringFromValue(tryCatch.StackTrace());
    	if (!stackTrace.isEmpty()) {
    		str.append(stackTrace);
    	} else {
    	    Local<Value> er = tryCatch.Exception();

    	    bool isErrorObject =
    	    		er->IsObject() &&
    	    		!(er->ToObject()->Get(String::New("message"))->IsUndefined()) &&
    	    		!(er->ToObject()->Get(String::New("name"))->IsUndefined());

    	    if (isErrorObject) {
    	    	Local<String> name = er->ToObject()->Get(String::New("name"))->ToString();
    	    	str.append(Ti::TiHelper::QStringFromValue(name) + "\n");
    	    }
    	    Local<String> message = !isErrorObject ? er->ToString() : er->ToObject()->Get(String::New("message"))->ToString();
    	    str.append(Ti::TiHelper::QStringFromValue(message) + "\n");
    	}

    }
	return str;
}


TiRootObject::TiRootObject()
    : TiObject("")
{
	context_ = TitaniumRuntime::getContenxt();
}

TiRootObject::~TiRootObject()
{
    if (!context_.IsEmpty())
    {
        context_.Dispose();
    }
    foreach(QString str, _commonJSModules.keys()) {
    	_commonJSModules[str].Dispose();
    }
    NativeStringInterface::deleteInstance();
}

void TiRootObject::onCreateStaticMembers()
{
    TiObject* ti = TiTitaniumObject::createObject(objectFactory_);
    addMember(ti);

    createStringMethods();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "L", this, _L);   // TODO: use the same object as Ti.Locale.getString
    TiGenericFunctionObject::addGenericFunctionToParent(this, "clearInterval", this, _clearInterval);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "clearTimeout", this, _clearTimeout);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "require", this, _require);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setInterval", this, _setInterval);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setTimeout", this, _setTimeout);


	Local<Object> tiObj = context_->Global()->Get(String::New("Ti"))->ToObject();
    tiObj->Set(String::New("Filesystem"), TiFilesystemModule::CreateModule(), DontDelete);
    tiObj->Set(String::New("Geolocation"), TiGeolocationModule::CreateModule(), DontDelete);
    tiObj->Set(String::New("Platform"), TiPlatformModule::CreateModule(), DontDelete);
    tiObj->Set(String::New("Utils"), TiUtilsModule::CreateModule(), DontDelete);
    tiObj->Set(String::New("App"), TiAppModule::CreateModule(), DontDelete);
    tiObj->Set(String::New("BlackBerry"), TiBlackberryModule::CreateModule(), DontDelete);

    Local<Object> tiUI = tiObj->Get(String::New("UI"))->ToObject();
    tiUI->Set(String::New("BlackBerry"), TiUIBlackberryModule::CreateModule(), DontDelete);

}

VALUE_MODIFY TiRootObject::onChildValueChange(TiObject* childObject, Handle<Value>, Handle<Value> newValue)
{
    Local<Object> obj = getValue()->ToObject();
    obj->Set(String::New(childObject->getName()), newValue);
    return VALUE_MODIFY_ALLOW;
}


void TiRootObject::addMember(TiObject* object, const char* name)
{
    TiObject::addMember(object, name);
    if (name == NULL)
    {
        name = object->getName();
    }
    Handle<Object> obj = getValue()->ToObject();
    Handle<Value> newValue = object->getValue();
    if (newValue.IsEmpty())
    {
        newValue = globalTemplate_->NewInstance();
        object->forceSetValue(newValue);
        TiObject::setTiObjectToJsObject(newValue, object);
    }
    obj->Set(String::New(name), newValue, DontDelete);

}

TiRootObject* TiRootObject::createRootObject()
{
    TiRootObject* obj = new TiRootObject;
    return obj;
}

int TiRootObject::executeScript(NativeObjectFactory* objectFactory, const char* javaScript,
                                MESSAGELOOPENTRY messageLoopEntry, void* context)
{
    HandleScope handleScope;
    objectFactory_ = objectFactory;
    globalTemplate_ = ObjectTemplate::New();
    TiV8EventContainerFactory* eventFactory = TiV8EventContainerFactory::createEventContainerFactory(globalTemplate_);
    objectFactory->setEventContainerFactory(eventFactory);
    onSetGetPropertyCallback(&globalTemplate_);
    onSetFunctionCallback(&globalTemplate_);
    g_rootTemplate = ObjectTemplate::New();
    forceSetValue(context_->Global());
    context_->Global()->SetHiddenValue(String::New("globalTemplate_"), External::New(&globalTemplate_));
    context_->Global()->SetHiddenValue(String::New("context_"), External::New(&context_));
    setTiObjectToJsObject(context_->Global(), this);
    Context::Scope context_scope(context_);
    initializeTiObject(NULL);
    bool scriptHasError = false;

    const char* bootstrapFilename = "bootstrap.js";
    string bootstrapJavascript;
    {
        ifstream ifs(Ti::TiHelper::getAssetPath(QString(bootstrapFilename)).toLocal8Bit().constData());
        if (!ifs)
        {
            TiLogger::getInstance().log(Ti::Msg::ERROR__Cannot_load_bootstrap_js);
            return -1;
        }
        getline(ifs, bootstrapJavascript, string::traits_type::to_char_type(string::traits_type::eof()));
        ifs.close();
    }

    TryCatch tryCatch;
    Handle<Script> compiledBootstrapScript = Script::Compile(String::New(bootstrapJavascript.c_str()), String::New(bootstrapFilename));
    if (compiledBootstrapScript.IsEmpty())
    {
        String::Utf8Value error(tryCatch.Exception());
        TiLogger::getInstance().log(*error);
        return -1;
    }
    Handle<Value> bootstrapResult = compiledBootstrapScript->Run();
    if (bootstrapResult.IsEmpty())
    {
        Local<Value> exception = tryCatch.Exception();
        // FIXME: need a way to prevent double "filename + line" output
        Handle<Message> msg = tryCatch.Message();
        stringstream ss;
        ss << bootstrapFilename << " line ";
        if (msg.IsEmpty())
        {
            ss << "?";
        }
        else
        {
            ss << msg->GetLineNumber();
        }
        ss << ": " << *String::Utf8Value(exception);
        TiLogger::getInstance().log(ss.str().c_str());
        return -1;
    }

    const char* filename = "app.js";
    Handle<Script> compiledScript = Script::Compile(String::New(javaScript), String::New(filename));
    QString error_str;
    if (compiledScript.IsEmpty())
    {
    	ThrowJSException(tryCatch);
        return 1;
    }
    compiledScript->Run();
    if (tryCatch.HasCaught())
    {
    	error_str = ThrowJSException(tryCatch);
        scriptHasError = true;
    }
    // show script error
    QString deployType = Ti::TiHelper::getAppSetting("deploytype").toString();
    if (scriptHasError && deployType.compare(QString("development")) == 0) {

		bb::cascades::Page* page = bb::cascades::Page::create();
		bb::cascades::Container* background = bb::cascades::Container::create();
		background->setLayout(bb::cascades::DockLayout::create());
		background->setBackground(bb::cascades::Color::Red);
		page->setContent(background);

		bb::cascades::Container* container = bb::cascades::Container::create();
		container->setHorizontalAlignment(bb::cascades::HorizontalAlignment::Center);
		container->setVerticalAlignment(bb::cascades::VerticalAlignment::Center);
		background->add(container);

		bb::cascades::Label *label = bb::cascades::Label::create();
		label->textStyle()->setColor(bb::cascades::Color::White);
		label->setText(error_str);
		label->setMultiline(true);
		container->add(label);

	    bb::cascades::Application::instance()->setScene(bb::cascades::Page::create());

	    bb::cascades::Sheet *sheet = bb::cascades::Sheet::create();
		sheet->setPeekEnabled(false);
		sheet->setContent(page);
		sheet->open();


		/*
    	static const string javaScriptErrorAlert = string("var win1 = Titanium.UI.createWindow({") +
											   string("backgroundColor:'red'") +
											   string("});") +
											   string("var label1 = Titanium.UI.createLabel({") +
											   string("color:'white',") +
											   string("textAlign:'center',") +
											   string("text:") +
											   "'" + err_msg + "'," +
											   string("font:{fontSize:8,fontFamily:'Helvetica Neue',fontStyle:'Bold'},") +
											   string("});") +
											   string("win1.add(label1);") +
											   string("win1.open();");


    	compiledScript = Script::Compile(String::New(javaScriptErrorAlert.c_str()));
    	compiledScript->Run();
    	*/
    }

    onStartMessagePump();
    return (messageLoopEntry)(context);
}

Handle<Object> TiRootObject::createProxyObject()
{
    return globalTemplate_->NewInstance();
}

void TiRootObject::createStringMethods()
{
    Local<Value> str = context_->Global()->Get(String::New("String"));
    if (!str->IsObject())
    {
        // This should never happen
        ThrowException(String::New(Ti::Msg::INTERNAL__Global_String_symbol_is_not_an_object));
    }
    Local<Object> strObj = str->ToObject();
    const NativeStringInterface* nsi = objectFactory_->getNativeStringInterface();
    strObj->Set(String::New("format"), FunctionTemplate::New(nsi->format)->GetFunction());
    strObj->Set(String::New("formatCurrency"), FunctionTemplate::New(nsi->formatCurrency)->GetFunction());
    strObj->Set(String::New("formatDate"), FunctionTemplate::New(nsi->formatDate)->GetFunction());
    strObj->Set(String::New("formatDecimal"), FunctionTemplate::New(nsi->formatDecimal)->GetFunction());
    strObj->Set(String::New("formatTime"), FunctionTemplate::New(nsi->formatTime)->GetFunction());
}

/* Methods defined by Global */
Handle<Value> TiRootObject::_L(void* arg1, TiObject* arg2, const Arguments& arg3)
{
    return TiLocaleObject::_getString(arg1, arg2, arg3);
}

Handle<Value> TiRootObject::_clearInterval(void*, TiObject*, const Arguments& args)
{
    if ((args.Length() != 1) || (!args[0]->IsNumber()))
    {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }
    clearTimeoutHelper(args, true);
    return Undefined();
}

Handle<Value> TiRootObject::_clearTimeout(void*, TiObject*, const Arguments& args)
{
    if ((args.Length() != 1) || (!args[0]->IsNumber()))
    {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }
    clearTimeoutHelper(args, false);
    return Undefined();
}

void TiRootObject::clearTimeoutHelper(const Arguments& args, bool interval)
{
    Handle<Number> number = Handle<Number>::Cast(args[0]);
    TiTimeoutManager* timeoutManager = TiTimeoutManager::instance();
    timeoutManager->clearTimeout((int)number->Value(), interval);
}

static QString readJsFile(QString filePath) {
	QFile file(filePath);
	QString jsContent;
	if(!file.open(QIODevice::ReadOnly)) {
		return jsContent;
	}
	jsContent.append(file.readAll());
	file.close();
	return jsContent;
}


Handle<Value> TiRootObject::_require(void* userContext, TiObject* caller, const Arguments& args)
{
	HandleScope scope;
	Handle<Value> nativeModule = TiModuleRegistry::GetModule(QString(*String::Utf8Value(args[0]->ToString())));
	if(!nativeModule->IsUndefined())
	{
		return scope.Close(nativeModule);
	}
	QString fileName = Ti::TiHelper::QStringFromValue(args[0]);
	fileName.append(".js");
	QString filePath = Ti::TiHelper::getAssetPath(fileName);

	if(_commonJSModules.contains(filePath))
	{
		return scope.Close(_commonJSModules.value(filePath));
	}

	QString js = readJsFile(filePath);
	if(js.isEmpty()) {
		ThrowException(String::New(
								QString("Module not found ").append(fileName).toLocal8Bit().constData()
						));
		return scope.Close(Undefined());
	}
	js.prepend("(function () {"
			   "	var module = {"
			   "		exports: {}"
			   "	};"
			   "	var exports = module.exports;"
			   "	Ti.API.info('inside \"" + filePath + "\" module');"
			);
	js.append("	\n"
			  "	return module.exports;\n"
			  "})();\n");

	Handle<Script> script = Script::Compile(Ti::TiHelper::ValueFromQString(js)->ToString() , Ti::TiHelper::ValueFromQString(fileName));
	TryCatch tryCatch;
	if (script.IsEmpty())
	{
		ThrowException(tryCatch.ReThrow());
		return scope.Close(Undefined());
	}
	Persistent<Value> result = Persistent<Value>::New(script->Run());
	if (result.IsEmpty())
	{
		ThrowException(tryCatch.ReThrow());
		return scope.Close(Undefined());
	}
	_commonJSModules.insert(filePath, result);
	return scope.Close(result);
}

Handle<Value> TiRootObject::_setInterval(void*, TiObject*, const Arguments& args)
{
    return setTimeoutHelper(args, true);
}

Handle<Value> TiRootObject::_setTimeout(void*, TiObject*, const Arguments& args)
{
    return setTimeoutHelper(args, false);
}

Handle<Value> TiRootObject::setTimeoutHelper(const Arguments& args, bool interval)
{
    HandleScope handleScope;
    if ((args.Length() != 2) || (!args[0]->IsFunction()) || (!args[1]->IsNumber()))
    {
        ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }
    Handle<Function> function = Handle<Function>::Cast(args[0]);
    Handle<Number> number = Handle<Number>::Cast(args[1]);
    TiTimeoutManager* timeoutManager = TiTimeoutManager::instance();
    int id = timeoutManager->createTimeout((int)number->Value(), function, interval);
    Handle<Number> timerId = Number::New(id);
    return timerId;
}

