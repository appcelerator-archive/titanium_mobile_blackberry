/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiRootObject.h"

#include "NativeStringInterface.h"
#include "TiGenericFunctionObject.h"
#include "TiMessageStrings.h"
#include "TiLogger.h"
#include "TiTitaniumObject.h"
#include "TiV8EventContainerFactory.h"
#include <fstream>

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
    TiGenericFunctionObject::addGenericFunctionToParent(this, "alert", this, _alert);
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

    string bootstrapJavascript;
    {
        ifstream ifs("app/native/framework/bootstrap.js");
        if (!ifs)
        {
            TiLogger::getInstance().log(Ti::Msg::ERROR__Cannot_load_bootstrap_js);
            return -1;
        }
        getline(ifs, bootstrapJavascript, string::traits_type::to_char_type(string::traits_type::eof()));
        ifs.close();
    }

    TryCatch tryCatch;
    Handle<Script> compiledBootstrapScript = Script::Compile(String::New(bootstrapJavascript.c_str()));
    if (compiledBootstrapScript.IsEmpty())
    {
        String::Utf8Value error(tryCatch.Exception());
        TiLogger::getInstance().log(*error);
        return -1;
    }
    Handle<Value> bootstrapResult = compiledBootstrapScript->Run();
    if (bootstrapResult.IsEmpty())
    {
        String::Utf8Value error(tryCatch.Exception());
        TiLogger::getInstance().log(*error);
        return -1;
    }

    Handle<Script> compiledScript = Script::Compile(String::New(javaScript));
    if (compiledScript.IsEmpty())
    {
        String::Utf8Value error(tryCatch.Exception());
        TiLogger::getInstance().log(*error);
        return -1;
    }
    Handle<Value> result = compiledScript->Run();
    if (result.IsEmpty())
    {
        String::Utf8Value error(tryCatch.Exception());
        TiLogger::getInstance().log(*error);
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

Handle<Value> TiRootObject::_alert(void*, TiObject*, const Arguments& args)
{
    // TODO: finish this
    (void)args;
    return Undefined();
}

Handle<Value> TiRootObject::_clearInterval(void*, TiObject*, const Arguments& args)
{
    // TODO: finish this
    (void)args;
    return Undefined();
}

Handle<Value> TiRootObject::_clearTimeout(void*, TiObject*, const Arguments& args)
{
    // TODO: finish this
    (void)args;
    return Undefined();
}

Handle<Value> TiRootObject::_require(void*, TiObject*, const Arguments& args)
{
    // TODO: finish this
    (void)args;
    return Undefined();
}

Handle<Value> TiRootObject::_setInterval(void*, TiObject*, const Arguments& args)
{
    // TODO: finish this
    (void)args;
    return Undefined();
}

Handle<Value> TiRootObject::_setTimeout(void*, TiObject*, const Arguments& args)
{
    // TODO: finish this
    (void)args;
    return Undefined();
}

