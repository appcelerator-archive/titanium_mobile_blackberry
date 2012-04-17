/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiV8Event.h"

TiV8Event::TiV8Event()
{
}

TiV8Event::~TiV8Event()
{
    if (!function_.IsEmpty())
    {
        function_.Dispose();
    }
    if (!source_.IsEmpty())
    {
        source_.Dispose();
    }
}

void TiV8Event::fire(void* fireDataObject)
{
    HandleScope handleScope;
    if (function_.IsEmpty())
    {
        return;
    }
    Handle < Object > dataObject = *((Persistent<Object>*) fireDataObject);
    dataObject->Set(String::New("source"), source_);
    function_->Call(function_, 1, (Handle<Value>*) &dataObject);
}

TiV8Event* TiV8Event::createEvent(const char* eventName, Handle<Function> eventScript, Handle<Object> source)
{
    HandleScope handleScope;
    TiV8Event* obj = new TiV8Event();
    obj->function_ = Persistent < Function > ::New(eventScript);
    obj->source_ = Persistent < Object > ::New(source);
    return obj;
}
