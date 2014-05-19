/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiV8Event.h"
#include <TiCore.h>

TiV8Event::TiV8Event()
{
}

TiV8Event::~TiV8Event()
{
    if (!function_.IsEmpty())
    {
        function_.Dispose();
    }
}

void TiV8Event::fire(void* fireDataObject)
{
    HandleScope handleScope;
    if (function_.IsEmpty())
    {
        return;
    }
    Handle<Context> context = function_->CreationContext();
    Context::Scope context_scope(context);
    Handle<Value> result;
    TryCatch tryCatch;
    if (fireDataObject == NULL)
    {
        //make a function call with no arguments
        result = function_->Call(context->Global(), 0, 0);
    }
    else
    {
        Handle<Object> dataObject = *((Persistent<Object>*) fireDataObject);
        dataObject->Set(String::New("source"), source_);
        // This calls the Javascript function that handles the event. It has
        // the form of: function(e) {...}
        // The "1" in the following function refers to the number of arguments that
        // are passed the the Javascript function. In this case there is one
        // argument: "e". The argument is an object with properties relating
        // to the event that was triggered.
        result = function_->Call(source_, 1, (Handle<Value>*) &dataObject);
    }
    if (result.IsEmpty())
    {
        Ti::TiErrorScreen::ShowWithTryCatch(tryCatch);
    }
}

TiV8Event* TiV8Event::createEvent(const char*, Handle<Function> eventScript, Handle<Object> source)
{
    HandleScope handleScope;
    TiV8Event* obj = new TiV8Event();
    obj->function_ = Persistent<Function>::New(eventScript);
    obj->source_ = source;
    return obj;
}
