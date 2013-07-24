/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "ReplaceWithModuleName.h"

#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <map>

using namespace std;

map<string, string> properties;

/**
 * This class uses the TiModule interface to extend the Titanium BlackBerry SDK,  The Titanium BlackBerry SDK
 * use the V8 JavaScript engine, this class shows how a native module developer might expose native functionality
 * using V8.
 *
 * This is just a simple starter module, the code is derived from https://developers.google.com/v8/embed.
 */

// Helper to covert V8 string value to standard string
string ObjectToString(Local<Value> value) {
  String::Utf8Value utf8_value(value);
  return string(*utf8_value);
}

ReplaceWithModuleName::ReplaceWithModuleName()
{
}

Handle<Value> ReplaceWithModuleName::startup()
{
	HandleScope handleScope;

	Handle<ObjectTemplate> obj = ObjectTemplate::New();
	obj->Set(String::New("example"), FunctionTemplate::New(ReplaceWithModuleName::Example));
	obj->SetAccessor(String::New("exampleProp"), ReplaceWithModuleName::GetProperty, ReplaceWithModuleName::SetProperty);

	return handleScope.Close(obj->NewInstance());
}

Handle<Value> ReplaceWithModuleName::Example(const v8::Arguments& args)
{
    HandleScope handleScope;
	std::string value = "Hello World";

    return handleScope.Close(Number::New(atof(value.c_str())));
}

Handle<Value> ReplaceWithModuleName::GetProperty(Local<String> name,
                                             const AccessorInfo& info) {
  string key = ObjectToString(name);

  map<string, string>::iterator iter = properties.find(key);
  if (iter == properties.end()) return Handle<Value>();

  const string& value = (*iter).second;
  return String::New(value.c_str(), value.length());
}

void ReplaceWithModuleName::SetProperty(Local<String> name,
                                             Local<Value> value_obj,
                                             const AccessorInfo& info) {
  string key = ObjectToString(name);

  string value = ObjectToString(value_obj);
  properties[key] = value;
}

