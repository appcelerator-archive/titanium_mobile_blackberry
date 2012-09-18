/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiRootObject.h"

#include "NativeStringInterface.h"
#include "TiGenericFunctionObject.h"
#include "TiLogger.h"
#include "TiMessageStrings.h"
#include "TiTitaniumObject.h"
#include "TiTimeoutManager.h"
#include "TiV8EventContainerFactory.h"

#include <fstream>
#include <sstream>

#include <QString>
#include <QUrl>

static Handle<ObjectTemplate> g_rootTemplate;

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
    addMember(ti, "Ti");

    createStringMethods();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "L", this, _L);   // TODO: use the same object as Ti.Locale.getString
    TiGenericFunctionObject::addGenericFunctionToParent(this, "clearInterval", this, _clearInterval);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "clearTimeout", this, _clearTimeout);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "require", this, _require);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setInterval", this, _setInterval);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setTimeout", this, _setTimeout);
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
        TiLogger::getInstance().log(ss.str());
        return -1;
    }

    const char* filename = "app.js";
    Handle<Script> compiledScript = Script::Compile(String::New(javaScript), String::New(filename));
    if (compiledScript.IsEmpty())
    {
        String::Utf8Value error(tryCatch.Exception());
        TiLogger::getInstance().log(*error);
        return -1;
    }
    Handle<Value> result = compiledScript->Run();
    if (result.IsEmpty())
    {
        Local<Value> exception = tryCatch.Exception();
        // FIXME: need a way to prevent double "filename + line" output
        Handle<Message> msg = tryCatch.Message();
        stringstream ss;
        ss << filename << " line ";
        if (msg.IsEmpty())
        {
            ss << "?";
        }
        else
        {
            ss << msg->GetLineNumber();
        }
        ss << ": " << *String::Utf8Value(exception);
        TiLogger::getInstance().log(ss.str());
        return -1;
    }
    onStartMessagePump();
    return (messageLoopEntry)(context);
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
Handle<Value> TiRootObject::_L(void*, TiObject*, const Arguments& args)
{
    // TODO: finish this
    (void)args;
    return Undefined();
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

Handle<Value> TiRootObject::_require(void*, TiObject*, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    Handle<String> v8Id = args[0]->ToString();
    string id = *String::Utf8Value(v8Id);

    // check if cached
    static map<string, Persistent<Value> > cache;
    map<string, Persistent<Value> >::const_iterator cachedValue = cache.find(id);
    if (cachedValue != cache.end())
    {
        return cachedValue->second;
    }

    string filename = id + ".js";
    // TODO: need to make this relative and support com.example.module
    static const string baseFolder = "app/native/assets/";
    string javascript;
    {
        ifstream ifs((baseFolder + filename).c_str());
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
        static const string preWrap = "(function () { var module = { exports: {} }; var exports = module.exports;\n";
        static const string postWrap = "\nreturn module.exports; })();";
        javascript = preWrap + javascript + postWrap;
    }

    // TODO: set the correct context

    TryCatch tryCatch;
    Handle<Script> compiledScript = Script::Compile(String::New(javascript.c_str()), String::New(filename.c_str()));
    if (compiledScript.IsEmpty())
    {
        return ThrowException(tryCatch.Exception());
    }
    Persistent<Value> result = (Persistent<Value>)compiledScript->Run();
    if (result.IsEmpty())
    {
        Handle<Message> msg = tryCatch.Message();
        stringstream ss;
        ss << filename << " line ";
        if (msg.IsEmpty())
        {
            ss << "?";
        }
        else
        {
            ss << msg->GetLineNumber() - 1; // -1 for the wrapper
        }
        ss << ": " << *String::Utf8Value(tryCatch.Exception());
        return ThrowException(String::New(ss.str().c_str()));
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
