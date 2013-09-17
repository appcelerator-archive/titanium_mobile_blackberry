/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiRootObject.h"

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
#include "Modules/Platform/TiPlatformModule.h"

using namespace titanium;

static Handle<ObjectTemplate> g_rootTemplate;
static const string rootFolder = "app/native/assets/";

// Application properties defined at compile in tiapp.xml
// can be read using this settings instance. It is read only.
static QSettings defaultSettings("app/native/assets/app_properties.ini",
                                 QSettings::IniFormat);

TiRootObject::TiRootObject()
    : TiObject("")
{
}

TiRootObject::~TiRootObject()
{
    if (!context_.IsEmpty())
    {
        context_.Dispose();
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
    TiGenericFunctionObject::addGenericFunctionToParent(this, "globalRequire", this, _globalRequire);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setInterval", this, _setInterval);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setTimeout", this, _setTimeout);


	Local<Object> tiObj = context_->Global()->Get(String::New("Ti"))->ToObject();
    tiObj->Set(String::New("Filesystem"), TiFilesystemModule::CreateModule());



	Local<Object> tiObj = context_->Global()->Get(String::New("Ti"))->ToObject();
    tiObj->Set(String::New("Platform"), TiPlatformModule::CreateModule());
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
    obj->Set(String::New(name), newValue);

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
    context_ = Context::New(NULL, g_rootTemplate);
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
        ifstream ifs((string("app/native/framework/") + bootstrapFilename).c_str());
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
    string err_msg;
    if (compiledScript.IsEmpty())
    {
        ReportException(tryCatch, true, err_msg);
        return 1;
    }
    compiledScript->Run();
    if (tryCatch.HasCaught())
    {
        ReportException(tryCatch, true, err_msg);
        scriptHasError = true;
    }

    // show script error
    QString deployType = defaultSettings.value("deploytype").toString();
    if (scriptHasError && deployType.compare(QString("development")) == 0) {

		// clean up display data
		size_t start_pos = 0;
		while((start_pos = err_msg.find("\n", start_pos)) != std::string::npos) {
			err_msg.replace(start_pos, 1, "\\n");
		}

		start_pos = 0;
		while((start_pos = err_msg.find("'", start_pos)) != std::string::npos) {
			err_msg.erase(start_pos, 1);
		}

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

Handle<Value> TiRootObject::_globalRequire(void*, TiObject*, const Arguments& args)
{
	if (args.Length() < 2) {
		return ThrowException(String::New(Ti::Msg::Missing_argument));
	}

	string id = *String::Utf8Value(args[0]->ToString());

	// Require in native modules, if none found move to loading CommonJS modules
	TiModule* module = getModuleByName(id);

	if (module != NULL) {
		return module->startup();
	}

	// CommonJS path rules
	string parentFolder = *String::Utf8Value(args[1]->ToString());
	if (id.find("/") == 0) {
		id.replace(id.find("/"), std::string("/").length(), rootFolder);
	}
	else if (id.find("./") == 0) {
		id.replace(id.find("./"), std::string("./").length(), parentFolder);
	}
	else if (id.find("../") == 0) {
		// count ../../../ in id and strip off back of parentFolder
		int count = 0;
		size_t idx = 0;
		size_t pos = 0;
		while (true) {
			idx = id.find("../", pos);
			if (idx == std::string::npos) {
				break;
			} else {
				pos = idx + 3;
				count++;
			}
		}

		// strip leading ../../ off module id
		id = id.substr(pos);

		// strip paths off the parent folder
		idx = 0;
		pos = parentFolder.size();
		for (int i = 0; i < count; i++) {
			idx = parentFolder.find_last_of("/", pos);
			pos = idx - 1;
		}

		if (idx == std::string::npos) {
			return ThrowException(String::New("Unable to find module"));
		}

		parentFolder = parentFolder.substr(0, idx + 1);

		id = parentFolder + id;
	}
	else {
		string tempId = rootFolder + id;

		ifstream ifs((tempId + ".js").c_str());
		if (!ifs) {
			id = parentFolder + id;
		}
		else {
			id = rootFolder + id;
		}
	}

	string filename = id + ".js";

	// check if cached
	static map<string, Persistent<Value> > cache;
	map<string, Persistent<Value> >::const_iterator cachedValue = cache.find(id);
	if (cachedValue != cache.end())	{
		return cachedValue->second;
	}

	string javascript;
	{
		ifstream ifs((filename).c_str());
		if (!ifs)
		{
			Local<Value> taggedMessage = String::New((string(Ti::Msg::No_such_native_module) + " " + id).c_str());
			return ThrowException(taggedMessage);
		}
		getline(ifs, javascript, string::traits_type::to_char_type(string::traits_type::eof()));
		ifs.close();
	}

	// wrap the module
	{
		size_t idx = filename.find_last_of("/");
		parentFolder = filename.substr(0, idx + 1);
		static const string requireWithParent = "var require = function (id) { return globalRequire(id, '" + parentFolder + "')};\n";
		static const string preWrap = "(function () {" + requireWithParent + "\nvar module = { exports: {} }; var exports = module.exports;\n";
		static const string postWrap = "\nreturn module.exports; })();";
		javascript =  preWrap + javascript + postWrap;
	}

	TryCatch tryCatch;
	Handle<Script> compiledScript = Script::Compile(String::New(javascript.c_str()), String::New(filename.c_str()));
	if (compiledScript.IsEmpty())
	{
		std::string err_msg;
		DisplayExceptionLine(tryCatch, err_msg);
		return tryCatch.ReThrow();
	}

	Persistent<Value> result = Persistent<Value>::New(compiledScript->Run());
	if (result.IsEmpty())
	{
		return tryCatch.ReThrow();
	}

	// cache result
	cache.insert(pair<string, Persistent<Value> >(id, result));

	return result;
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

