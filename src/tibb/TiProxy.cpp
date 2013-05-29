/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiProxy.h"

#include "NativeProxyObject.h"
#include "TiGenericFunctionObject.h"
#include "TiPropertySetGetObject.h"
#include "TiV8Event.h"


const char* POINTER = "_event_ptr_";
const char* OWNER   = "_event_owner_";
const char* ID      = "_event_id_";

TiProxy::TiProxy()
{
}

TiProxy::TiProxy(const char* name):
    TiObject(name)
{
}

TiProxy::~TiProxy()
{
}

void TiProxy::onCreateStaticMembers()
{
    TiObject::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "addEventListener", this, _addEventListener);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "fireEvent", this, _fireEvent);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "removeEventListener", this, _removeEventListener);
}

void TiProxy::createSettersAndGetters(const char* name, SET_PROPERTY_CALLBACK setter, GET_PROPERTY_CALLBACK getter)
{
    TiPropertySetGetObject::createProperty(this, name, this, setter, getter);
}

Handle<Value> TiProxy::createProxy(void*, TiObject*, const Arguments&)
{
	// for subclass;
	return Undefined();
}

Handle<Value> TiProxy::createProxy(TiProxy *proxy, void* userContext, const Arguments& args)
{
    
    TiProxy *module = static_cast<TiProxy*>(userContext);
    HandleScope handleScope;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result = global->NewInstance();

    proxy->setNativeObjectFactory(module->getNativeObjectFactory());
    proxy->initializeTiObject(NULL);
    proxy->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        proxy->setParametersFromObject(proxy, settingsObj);
    }
    setTiObjectToJsObject(result, proxy);
    return handleScope.Close(result);
}

Handle<Value> TiProxy::_addEventListener(void* userContext, TiObject*, const Arguments& args)
{
    // JavaScript usage:
    //
    // arg[0] = event name (string)
    // arg[1] = event function (function)
    //
    // myobject.addEventListener('myevent',function(e) {...});
    //
    if ((args.Length() != 2) || (!args[0]->IsString()) || (!args[1]->IsFunction()))
    {
        return Undefined();
    }
    TiProxy* obj = (TiProxy*) userContext;
    Handle<String> eventName = Handle<String>::Cast(args[0]);
    Handle<Function> func = Handle<Function>::Cast(args[1]);
    String::Utf8Value eventNameUTF(eventName);
    obj->onAddEventListener(*eventNameUTF, func);
    return Undefined();
}

Handle<Value> TiProxy::_fireEvent(void* userContext, TiObject*, const Arguments& args)
{
    if (args.Length() < 1) {
        return Undefined();
    }

    const TiProxy* obj = (TiProxy*) userContext;
    NativeObject* no = obj->getNativeObject();
    if (!no) return Undefined();

    const String::Utf8Value name(args[0]->ToString());
    if (args.Length() >= 2) {
        const TiObject event("", args[1]);
        no->fireEvent(*name, &event);
    } else {
        no->fireEvent(*name, NULL);
    }
    no->release();

    return Undefined();
}

Handle<Value> TiProxy::_removeEventListener(void* userContext, TiObject*, const Arguments& args)
{
    // JavaScript usage:
    //
    // arg[0] = event name (string)
    // arg[1] = event function (function)
    //
    // myobject.removeEventListener('myevent',function(e) {...});
    //
    if ((args.Length() < 2) || (!args[0]->IsString()) || (!args[1]->IsFunction()))
    {
        return Undefined();
    }
    TiProxy* obj = (TiProxy*) userContext;
    Handle<String> eventName = Handle<String>::Cast(args[0]);
    Handle<Function> func = Handle<Function>::Cast(args[1]);
    String::Utf8Value eventNameUTF(eventName);
    obj->onRemoveEventListener(*eventNameUTF, func);
    return Undefined();
}

void TiProxy::onAddEventListener(const char* eventName, Handle<Function> eventFunction)
{
    NativeObject* no = getNativeObject();
    if (no == NULL)
    {
        // To support events we need to create a native proxy
        // instance here if no native object has been set yet.
        no = new NativeProxyObject(this);
        setNativeObject(no);
    }
    Handle<Object> source = Handle<Object>::Cast(getValue());
    TiV8Event* event = TiV8Event::createEvent(eventName, eventFunction, source);
    no->setEventHandler(eventName, event);
    no->release();
    no = NULL;
    int id = event->getId();
    eventFunction->SetHiddenValue(String::New("POINTER"), External::New(event));
    eventFunction->SetHiddenValue(String::New("OWNER"), External::New(this));
    eventFunction->SetHiddenValue(String::New("ID"), Integer::New(id));
}

void TiProxy::onRemoveEventListener(const char* eventName, Handle<Function> eventFunction)
{
    NativeObject* no = getNativeObject();
    if (no == NULL)
    {
        return;
    }
    // Get the event subscriber's id so we know which to remove from the event container.
    Handle<Int32> v8id = eventFunction->GetHiddenValue(String::New("ID"))->ToInt32();
    if ((v8id.IsEmpty()) || (v8id->Value() == 0))
    {
        return;
    }
    // Make sure that the function being removed has been added to this event container.
    Handle<Value> v8extValue = eventFunction->GetHiddenValue(String::New("OWNER"));
    if ((v8extValue.IsEmpty()) || (!v8extValue->IsExternal()))
    {
        return;
    }
    Handle<External> v8ext = Handle<External>::Cast(v8extValue);
    TiProxy* referencedControl = (TiProxy*)v8ext->Value();
    if (referencedControl != this)
    {
        // User was attempting to remove an event handler from a control that it
        // doesn't belong to.
        return;
    }
    no->removeEventHandler(eventName, v8id->Value());
    no->release();
    no = NULL;

    // Free up the memory used by the TiV8Event
    Handle<Value> v8evtValue = eventFunction->GetHiddenValue(String::New("POINTER"));
    if ((v8evtValue.IsEmpty()) || (!v8evtValue->IsExternal()))
    {
        return;
    }
    Handle<External> v8evt = Handle<External>::Cast(v8evtValue);
    delete(TiV8Event*)v8evt->Value();
}

void TiProxy::setParametersFromObject(void* userContext, Local<Object> obj)
{
    HandleScope handleScope;
    Handle<Value> value;
    Handle<Value> controlValue = getValue();
    if (!controlValue->IsObject())
    {
        return;
    }
    Handle<Array> propNames = obj->GetPropertyNames();
    uint32_t props = propNames->Length();
    Local<Value> propValue;
    for (uint32_t i = 0; i < props; i++)
    {
        Handle<String> propString = Handle<String>::Cast(propNames->Get(Integer::New(i)));
        String::Utf8Value propNameUTF(propString);
        Local<Value> propValue = obj->Get(propString);
        TiObject* foundProp = onLookupMember(*propNameUTF);
        if (foundProp != NULL)
        {
            TiObject* addObj = getTiObjectFromJsObject(propValue);
            if (addObj)
            {
                TiProxy* obj = (TiProxy*) userContext;
                TiProxy* uiObj = (TiProxy*) addObj;
                NativeObject* childNO = uiObj->getNativeObject();
                NativeObject* parentNO = obj->getNativeObject();
                parentNO->addChildNativeObject(childNO);
                parentNO->release();
            }
            else
            {
                foundProp->setValue(propValue);
            }
        }
        else
        {
            // Set any custom properties onto the JS object.
            getValue()->ToObject()->ForceSet(propString, propValue);
        }
    }
}
