/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIAPPPROPERTIESOBJECT_H_
#define TIAPPPROPERTIESOBJECT_H_

#include "TiObject.h"

#include "NativeSimpleDBInterface.h"

/*
 * TiAppPropertiesObject
 *
 * Object that represents name space: Titanium.App.Properties
 */

class TiAppPropertiesObject : public TiObject
{
public:
    static void addObjectToParent(TiObject* parent);

protected:
    virtual ~TiAppPropertiesObject();
    virtual void onCreateStaticMembers();

private:
    TiAppPropertiesObject();
    TiAppPropertiesObject(const TiAppPropertiesObject&);
    TiAppPropertiesObject& operator=(const TiAppPropertiesObject&);

    static NativeSimpleDBInterface db;

    static Handle<Value> _get(string key, const char* type, Handle<Value> defaultValue);
    static Handle<Value> _set(string key, const char* type, Handle<Value> value);
    static Handle<Value> _nullOrDefaultValue(Handle<Value> defaultValue);

    static Handle<Value> _getBool(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _setBool(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _getDouble(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _setDouble(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _getInt(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _setInt(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _getList(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _setList(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _getObject(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _setObject(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _getString(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _setString(void* userContext, TiObject* caller, const Arguments& args);

    static Handle<Value> _hasProperty(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _listProperties(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _removeProperty(void* userContext, TiObject* caller, const Arguments& args);
};

#endif /* TIAPPPROPERTIESOBJECT_H_ */
