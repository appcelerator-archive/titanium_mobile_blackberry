/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiProxy.h"

#include "TiGenericFunctionObject.h"
#include "TiV8Event.h"


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
    const TiProxy* obj = (TiProxy*) userContext;
    Handle<String> eventName = Handle<String>::Cast(args[0]);
    Handle<Function> func = Handle<Function>::Cast(args[1]);
    String::Utf8Value eventNameUTF(eventName);
    obj->onAddEventListener(*eventNameUTF, func);
    return Undefined();
}

Handle<Value> TiProxy::_fireEvent(void* userContext, TiObject*, const Arguments& args)
{
    if (args.Length() < 2)
    {
        return Undefined();
    }
    const TiProxy* obj = (TiProxy*) userContext;
    NativeObject* no = obj->getNativeObject();
    const String::Utf8Value name(args[0]->ToString());
    const TiObject event("", args[1]);
    no->fireEvent(*name, &event);
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
    if ((args.Length() != 2) || (!args[0]->IsString()) || (!args[1]->IsFunction()))
    {
        return Undefined();
    }
    const TiProxy* obj = (TiProxy*) userContext;
    Handle<String> eventName = Handle<String>::Cast(args[0]);
    Handle<Function> func = Handle<Function>::Cast(args[1]);
    String::Utf8Value eventNameUTF(eventName);
    obj->onRemoveEventListener(*eventNameUTF, func);
    return Undefined();
}

void TiProxy::onAddEventListener(const char* eventName, Handle<Function> eventFunction) const
{
    HandleScope handleScope;
    NativeObject* no = getNativeObject();
    if (no == NULL)
    {
        return;
    }
    Handle<Object> source = Handle<Object>::Cast(getValue());
    TiV8Event* event = TiV8Event::createEvent(eventName, eventFunction, source);
    no->setEventHandler(eventName, event);
    no->release();
    int id = event->getId();
    eventFunction->SetHiddenValue(String::New("_event_ptr_"), External::New(event));
    eventFunction->SetHiddenValue(String::New("_event_id_"), Integer::New(id));
}

void TiProxy::onRemoveEventListener(const char*, Handle<Function> eventFunction) const
{
    HandleScope handleScope;
    NativeObject* no = getNativeObject();
    if (no == NULL)
    {
        return;
    }
    // Get the event subscriber's id so we know which to remove from the event container.
    Handle<Int32> v8id = eventFunction->GetHiddenValue(String::New("_event_id_"))->ToInt32();
    if ((v8id.IsEmpty()) || (v8id->Value() == 0))
    {
        return;
    }
    // Make sure that the function being removed has been added to this event container.
    Handle<Value> v8extValue = eventFunction->GetHiddenValue(String::New("_event_ptr_"));
    if ((!v8extValue.IsEmpty()) || (!v8extValue->IsExternal()))
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
    no->removeEventHandler(v8id->Value());
}
