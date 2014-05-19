/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_JSON_H
#define TI_JSON_H

#include "v8.h"
#include "V8Utils.h"

using namespace v8;

class JSON {
public:
    static Local<String> Stringify(Local<Value> obj)
    {
        HandleScope scope;

        Handle<Context> context = Context::GetCurrent();
        Handle<Object> global = context->Global();

        Handle<Object> JSON = global->Get(String::New("JSON"))->ToObject();
        Handle<Function> JSON_stringify = Handle<Function>::Cast(JSON->Get(String::New("stringify")));

        return scope.Close(JSON_stringify->Call(JSON, 1, &obj)->ToString());
    }
    static Local<Value> Parse(const char* str)
	{
        Handle<Context> context = Context::GetCurrent();
        Handle<Object> global = context->Global();

        Handle<Object> JSON = global->Get(String::New("JSON"))->ToObject();
        Handle<Function> JSON_parse = Handle<Function>::Cast(JSON->Get(String::New("parse")));

        Handle<Value> value = String::New(str);

        return JSON_parse->Call(JSON, 1, &value);
	}
    static Local<Value> Parse(Local<Value> str)
	{
    	QString json = titanium::V8ValueToQString(str);
        return JSON::Parse(json.toLocal8Bit().data());
	}
    static Local<Value> Parse(QString str)
	{
        return JSON::Parse(str.toLocal8Bit().data());
	}

};

#endif

