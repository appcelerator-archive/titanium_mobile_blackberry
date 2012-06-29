/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiRootObject.h"

#include "TiGenericFunctionObject.h"
#include "TiJSONObject.h"
#include "TiLogger.h"
#include "TiStringObject.h"
#include "TiTitaniumObject.h"
#include "TiV8EventContainerFactory.h"

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
}

void TiRootObject::onCreateStaticMembers()
{
    TiObject* ti = TiTitaniumObject::createObject(objectFactory_);
    addMember(ti);
    addMember(ti, "Ti");

    TiJSONObject::addObjectToParent(this, objectFactory_);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "L", this, _L);   // TODO: use the same object as Ti.Locale.getString
    TiGenericFunctionObject::addGenericFunctionToParent(this, "alert", this, _alert);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "clearInterval", this, _clearInterval);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "clearTimeout", this, _clearTimeout);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "decodeURIComponent", this, _decodeURIComponent);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "encodeURIComponent", this, _encodeURIComponent);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "require", this, _require);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setInterval", this, _setInterval);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setTimeout", this, _setTimeout);
}

VALUE_MODIFY TiRootObject::onChildValueChange(TiObject* childObject, Handle<Value> oldValue, Handle<Value> newValue)
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

    TryCatch tryCatch;
    Handle<Script> compiledScript = Script::Compile(String::New(javaScript));
    if (compiledScript.IsEmpty())
    {
        String::Utf8Value error(tryCatch.Exception());
        TiLogger::getInstance().log(string(*error) + "\n");
        return -1;
    }
    Handle<Value>result = compiledScript->Run();
    if (result.IsEmpty())
    {
        String::Utf8Value error(tryCatch.Exception());
        TiLogger::getInstance().log(string(*error) + "\n");
        return -1;
    }
    onStartMessagePump();
    return (messageLoopEntry)(context);
}

/* Methods defined by Global */
Handle<Value> TiRootObject::_L(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: finish this
    return Undefined();
}

Handle<Value> TiRootObject::_alert(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: finish this
    return Undefined();
}

Handle<Value> TiRootObject::_clearInterval(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: finish this
    return Undefined();
}

Handle<Value> TiRootObject::_clearTimeout(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: finish this
    return Undefined();
}

Handle<Value> TiRootObject::_decodeURIComponent(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: finish this
    return Undefined();
}

Handle<Value> TiRootObject::_encodeURIComponent(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: finish this
    return Undefined();
}

Handle<Value> TiRootObject::_require(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: finish this
    return Undefined();
}

Handle<Value> TiRootObject::_setInterval(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: finish this
    return Undefined();
}

Handle<Value> TiRootObject::_setTimeout(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: finish this
    return Undefined();
}

