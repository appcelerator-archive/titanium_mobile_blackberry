/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiAppPropertiesObject.h"

#include "NativeException.h"
#include "TiGenericFunctionObject.h"
#include "TiLogger.h"
#include "TiMessageStrings.h"

TiAppPropertiesObject::TiAppPropertiesObject()
    : TiObject("Properties")
{
}

TiAppPropertiesObject::~TiAppPropertiesObject()
{
}

void TiAppPropertiesObject::addObjectToParent(TiObject* parent)
{
    TiAppPropertiesObject* obj = new TiAppPropertiesObject;
    parent->addMember(obj);
}

void TiAppPropertiesObject::onCreateStaticMembers()
{
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getBool", this, _getBool);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setBool", this, _setBool);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getDouble", this, _getDouble);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setDouble", this, _setDouble);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getInt", this, _getInt);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setInt", this, _setInt);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getList", this, _getList);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setList", this, _setList);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getObject", this, _getObject);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setObject", this, _setObject);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "getString", this, _getString);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setString", this, _setString);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "hasProperty", this, _hasProperty);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "listProperties", this, _listProperties);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "removeProperty", this, _removeProperty);
}

NativeSimpleDBInterface TiAppPropertiesObject::db("app/native/framework/TiAppProperties.db", "TiAppProperties");

// TODO: move these to a util file
static Local<String> stringify(Handle<Value> object)
{
    HandleScope scope;

    Handle<Context> context = Context::GetCurrent();
    Handle<Object> global = context->Global();

    Handle<Object> JSON = global->Get(String::New("JSON"))->ToObject();
    Handle<Function> JSON_stringify = Handle<Function>::Cast(JSON->Get(String::New("stringify")));

    return scope.Close(JSON_stringify->Call(JSON, 1, &object)->ToString());
}

static Local<Value> parseJson(const string& json)
{
    Handle<Context> context = Context::GetCurrent();
    Handle<Object> global = context->Global();

    Handle<Object> JSON = global->Get(String::New("JSON"))->ToObject();
    Handle<Function> JSON_parse = Handle<Function>::Cast(JSON->Get(String::New("parse")));

    Handle<Value> value = String::New(json.c_str());

    return JSON_parse->Call(JSON, 1, &value);
}

static Local<Value> convertType(TiAppPropertiesObject::PropertyType type, Local<Value> value) {
    switch (type) {
    case TiAppPropertiesObject::BoolProperty:
        return value->ToBoolean();
    case TiAppPropertiesObject::DoubleProperty:
    case TiAppPropertiesObject::IntProperty:
        return value->ToNumber();
    case TiAppPropertiesObject::ObjectProperty:
        return value->ToObject();
    case TiAppPropertiesObject::ListProperty:
        return value;
    case TiAppPropertiesObject::StringProperty:
        return value->ToString();
    default:
        return Local<Value>();
    }
}

Handle<Value> TiAppPropertiesObject::_get(const Arguments& args, PropertyType type)
{
    HandleScope scope;

    Local<Value> key = args[0], defaultValue = args[1];

    if (key->IsUndefined() || key->IsNull()) {
        return Undefined();
    }

    string json;
    try {
        json = db.get(*String::Utf8Value(key));
    } catch (NativeException& ne) {
        return ThrowException(String::New(ne.what()));
    }

    if (json.empty()) {
        return defaultValue;
    }

    // Parse JSON value and return value as type requested by caller.
    return scope.Close(convertType(type, parseJson(json)));
}

Handle<Value> TiAppPropertiesObject::_set(const Arguments& args, PropertyType type)
{
    HandleScope scope;

    Local<Value> key = args[0], value = args[1];

    if (key->IsUndefined() || key->IsNull()) {
        return Undefined();
    }

    // Remove property if value is set to null or undefined.
    if (value->IsUndefined() || value->IsNull()) {
        db.remove(*String::Utf8Value(key));
        return Undefined();
    }

    // Serialize the property value to JSON.
    Local<String> json = stringify(convertType(type, value));

    try {
        db.set(*String::Utf8Value(key), *String::Utf8Value(json));
    } catch (NativeException& ne) {
        return ThrowException(String::New(ne.what()));
    }

    return Undefined();
}

Handle<Value> TiAppPropertiesObject::_getBool(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    return _get(args, BoolProperty);
}


Handle<Value> TiAppPropertiesObject::_setBool(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    return _set(args, BoolProperty);
}

Handle<Value> TiAppPropertiesObject::_getDouble(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    return _get(args, DoubleProperty);
}


Handle<Value> TiAppPropertiesObject::_setDouble(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    return _set(args, DoubleProperty);
}

Handle<Value> TiAppPropertiesObject::_getInt(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    return _get(args, IntProperty);
}


Handle<Value> TiAppPropertiesObject::_setInt(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    return _set(args, IntProperty);
}

Handle<Value> TiAppPropertiesObject::_getList(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    return _get(args, ListProperty);
}


Handle<Value> TiAppPropertiesObject::_setList(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    return _set(args, ListProperty);
}

Handle<Value> TiAppPropertiesObject::_getObject(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    return _get(args, ObjectProperty);
}


Handle<Value> TiAppPropertiesObject::_setObject(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    return _set(args, ObjectProperty);
}

Handle<Value> TiAppPropertiesObject::_getString(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    return _get(args, StringProperty);
}


Handle<Value> TiAppPropertiesObject::_setString(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    return _set(args, StringProperty);
}

Handle<Value> TiAppPropertiesObject::_hasProperty(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsString() && !args[0]->IsStringObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
    }

    string key = *String::Utf8Value(args[0]);
    try
    {
        return db.contains(key) ? True() : False();
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }
}

Handle<Value> TiAppPropertiesObject::_listProperties(void* /*userContext*/, TiObject* /*caller*/, const Arguments& /*args*/)
{
    list<string> keys;
    try
    {
        keys = db.keys();
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }

    HandleScope scope;
    Local<Array> properties = Array::New(keys.size());
    uint32_t index = 0;
    for (list<string>::const_iterator it = keys.begin(); it != keys.end(); it++)
    {
        properties->Set(index++, String::New((*it).c_str()));
    }
    return scope.Close(properties);
}

Handle<Value> TiAppPropertiesObject::_removeProperty(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsString() && !args[0]->IsStringObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
    }

    string key = *String::Utf8Value(args[0]);
    try
    {
        db.remove(key);
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}
