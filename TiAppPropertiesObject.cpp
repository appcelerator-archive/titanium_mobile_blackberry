/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiAppPropertiesObject.h"

#include "TiGenericFunctionObject.h"
#include "TiLogger.h"
#include "TiMessageStrings.h"

#define APP_PROP_TYPE_BOOL "bool"
#define APP_PROP_TYPE_DOUBLE "double"
#define APP_PROP_TYPE_INT "int"
#define APP_PROP_TYPE_LIST "list"
#define APP_PROP_TYPE_OBJECT "object"
#define APP_PROP_TYPE_STRING "string"

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
static string stringify(Handle<Value> object)
{
    Handle<Context> context = Context::GetCurrent();
    Handle<Object> global = context->Global();

    Handle<Object> JSON = global->Get(String::New("JSON"))->ToObject();
    Handle<Function> JSON_stringify = Handle<Function>::Cast(JSON->Get(String::New("stringify")));

    return *String::Utf8Value(JSON_stringify->Call(JSON, 1, &object));
}

static Local<Value> parseJson(string json)
{
    Handle<Context> context = Context::GetCurrent();
    Handle<Object> global = context->Global();

    Handle<Object> JSON = global->Get(String::New("JSON"))->ToObject();
    Handle<Function> JSON_parse =
        Handle<Function>::Cast(JSON->Get(String::New("parse")));

    Handle<Value> value = String::New(json.c_str());

    return JSON_parse->Call(JSON, 1, &value);
}

Handle<Value> TiAppPropertiesObject::_get(string key, const char* type, Handle<Value> defaultValue)
{
    string typeValueString = db.get(key);
    if (typeValueString.empty())
    {
        return defaultValue;
    }

    HandleScope scope;
    Local<Object> typeValue = parseJson(typeValueString)->ToObject();
    string storedType = *String::Utf8Value(typeValue->Get(String::New("type")));
    Local<Value> value = typeValue->Get(String::New("value"));
    if (storedType == type)
    {
        return scope.Close(value);
    }
    else
    {
        return ThrowException(String::New(Ti::Msg::Type_does_not_match));
    }
}

Handle<Value> TiAppPropertiesObject::_set(string key, const char* type, Handle<Value> value)
{
    HandleScope scope;
    Local<Object> typeValue = Object::New();
    typeValue->Set(String::New("type"), String::New(type));
    typeValue->Set(String::New("value"), value);
    string typeValueString = stringify(typeValue);
    db.set(key, typeValueString);
    return Undefined();
}

Handle<Value> TiAppPropertiesObject::_nullOrDefaultValue(Handle<Value> defaultValue)
{
    if (defaultValue->IsUndefined())
    {
        return Null();
    }
    return defaultValue;
}

Handle<Value> TiAppPropertiesObject::_getBool(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsString() && !args[0]->IsStringObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
    }
    Handle<Value> defaultValue = Null();
    if (args.Length() > 1)
    {
        defaultValue = _nullOrDefaultValue(args[1]);
        if (!defaultValue->IsNull() && !defaultValue->IsBoolean() && !defaultValue->IsBooleanObject())
        {
            return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "Boolean").c_str()));
        }
    }

    string key = *String::Utf8Value(args[0]);
    return _get(key, APP_PROP_TYPE_BOOL, defaultValue);
}


Handle<Value> TiAppPropertiesObject::_setBool(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 2)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsString() && !args[0]->IsStringObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
    }
    if (!args[1]->IsBoolean() && !args[1]->IsBooleanObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "Boolean").c_str()));
    }

    string key = *String::Utf8Value(args[0]);
    Handle<Boolean> value = args[1]->ToBoolean();
    return _set(key, APP_PROP_TYPE_BOOL, value);
}

Handle<Value> TiAppPropertiesObject::_getDouble(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsString() && !args[0]->IsStringObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
    }
    Handle<Value> defaultValue = Null();
    if (args.Length() > 1)
    {
        defaultValue = _nullOrDefaultValue(args[1]);
        if (!defaultValue->IsNull() && !defaultValue->IsNumber() && !defaultValue->IsNumberObject())
        {
            return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "Number").c_str()));
        }
    }

    string key = *String::Utf8Value(args[0]);
    return _get(key, APP_PROP_TYPE_DOUBLE, defaultValue);
}


Handle<Value> TiAppPropertiesObject::_setDouble(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 2)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsString() && !args[0]->IsStringObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
    }
    if (!args[1]->IsNumber() && !args[1]->IsNumberObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "Number").c_str()));
    }

    string key = *String::Utf8Value(args[0]);
    Handle<Number> value = args[1]->ToNumber();
    return _set(key, APP_PROP_TYPE_DOUBLE, value);
}

Handle<Value> TiAppPropertiesObject::_getInt(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsString() && !args[0]->IsStringObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
    }
    Handle<Value> defaultValue = Null();
    if (args.Length() > 1)
    {
        defaultValue = _nullOrDefaultValue(args[1]);
        if (!defaultValue->IsNull() && !defaultValue->IsInt32())
        {
            return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "Integer").c_str()));
        }
    }

    string key = *String::Utf8Value(args[0]);
    return _get(key, APP_PROP_TYPE_INT, defaultValue);
}


Handle<Value> TiAppPropertiesObject::_setInt(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 2)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsString() && !args[0]->IsStringObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
    }
    if (!args[1]->IsInt32())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "Integer").c_str()));
    }

    string key = *String::Utf8Value(args[0]);
    Handle<Integer> value = args[1]->ToInteger();
    return _set(key, APP_PROP_TYPE_INT, value);
}

Handle<Value> TiAppPropertiesObject::_getList(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsString() && !args[0]->IsStringObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
    }
    Handle<Value> defaultValue = Null();
    if (args.Length() > 1)
    {
        defaultValue = _nullOrDefaultValue(args[1]);
        if (!defaultValue->IsNull() && !defaultValue->IsArray())
        {
            return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "Array").c_str()));
        }
    }

    string key = *String::Utf8Value(args[0]);
    return _get(key, APP_PROP_TYPE_LIST, defaultValue);
}


Handle<Value> TiAppPropertiesObject::_setList(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 2)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsString() && !args[0]->IsStringObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
    }
    if (!args[1]->IsArray())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "Array").c_str()));
    }

    string key = *String::Utf8Value(args[0]);
    return _set(key, APP_PROP_TYPE_LIST, args[1]);
}

Handle<Value> TiAppPropertiesObject::_getObject(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsString() && !args[0]->IsStringObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
    }
    Handle<Value> defaultValue = Null();
    if (args.Length() > 1)
    {
        defaultValue = _nullOrDefaultValue(args[1]);
        if (!defaultValue->IsNull() && !defaultValue->IsObject())
        {
            return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "Object").c_str()));
        }
    }

    string key = *String::Utf8Value(args[0]);
    return _get(key, APP_PROP_TYPE_OBJECT, defaultValue);
}


Handle<Value> TiAppPropertiesObject::_setObject(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 2)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsString() && !args[0]->IsStringObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
    }
    if (!args[1]->IsObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "Object").c_str()));
    }

    string key = *String::Utf8Value(args[0]);
    return _set(key, APP_PROP_TYPE_OBJECT, args[1]);
}

Handle<Value> TiAppPropertiesObject::_getString(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsString() && !args[0]->IsStringObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
    }
    Handle<Value> defaultValue = Null();
    if (args.Length() > 1)
    {
        defaultValue = _nullOrDefaultValue(args[1]);
        if (!defaultValue->IsNull() && !defaultValue->IsString() && !defaultValue->IsStringObject())
        {
            return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
        }
    }

    string key = *String::Utf8Value(args[0]);
    return _get(key, APP_PROP_TYPE_STRING, defaultValue);
}


Handle<Value> TiAppPropertiesObject::_setString(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 2)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsString() && !args[0]->IsStringObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
    }
    if (!args[1]->IsString() && !args[1]->IsStringObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
    }

    string key = *String::Utf8Value(args[0]);
    Handle<String> value = args[1]->ToString();
    return _set(key, APP_PROP_TYPE_STRING, value);
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
    return db.contains(key) ? True() : False();
}

Handle<Value> TiAppPropertiesObject::_listProperties(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    list<string> keys = db.keys();
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
    db.remove(key);
    return Undefined();
}
