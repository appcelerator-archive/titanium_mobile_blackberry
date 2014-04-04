/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiV8Event.h"
#include "TiCore.h"

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
    	tryCatch.SetVerbose(true);
        String::Utf8Value error(tryCatch.Exception());
        Ti::TiHelper::Log(QString("[ERROR] ").append(*error));
        Ti::TiHelper::Log(QString("[ERROR] ").append(ThrowJSException(tryCatch)));
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
