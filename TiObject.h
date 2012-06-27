/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIOBJECT_H_
#define TIOBJECT_H_

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <tchar.h>
#endif

#include <string.h>
#include <map>
#include <string>

#include "TiBase.h"
#include "TiObjectScope.h"
#include "NativeObject.h"
#include "NativeObjectFactory.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <v8.h>
#pragma GCC diagnostic warning "-Wunused-parameter"

using namespace v8;
using namespace std;

// void ADD_STATUS_TI_VALUE(const char* name, Handle<Value> value, TiObject* parent)

#define ADD_STATIC_TI_VALUE(N,V,P)      {TiObject* __ti__=new TiObject((N),(V));(P)->addMember(__ti__);__ti__->release();}

class TiObject;

class ObjectEntry
{
public:
    ObjectEntry();
    ObjectEntry(const ObjectEntry& entry);
    ObjectEntry(TiObject* obj);
    ~ObjectEntry();
    const ObjectEntry& operator =(const ObjectEntry& entry);
    TiObject* getObject() const;
    TiObject* operator ->() const;
private:
    TiObject* obj_;
    void* userContext_;
};

#define JS_TYPE_UNDEFINED           1
#define JS_TYPE_STRING              2
#define JS_TYPE_NUMBER              4
#define JS_TYPE_FUNCTION            8

#define NATIVE_TYPE_VOID            0
#define NATIVE_TYPE_CSTRING         1
#define NATIVE_TYPE_INT             2
#define NATIVE_TYPE_DOUBLE          3
#define NATIVE_TYPE_BOOL            4
#define NATIVE_TYPE_OBJECT          5

enum VALUE_MODIFY
{
    VALUE_MODIFY_ALLOW,
    VALUE_MODIFY_DENY,
    VALUE_MODIFY_NOT_SUPPORTED,
    VALUE_MODIFY_INVALID,
    VALUE_MODIFY_INVALID_TYPE,
    VALUE_MODIFY_IGNORE,
};

#define TI_PROP_PERMISSION_READ         1
#define TI_PROP_PERMISSION_WRITE        2
#define TI_PROP_PERMISSION_DELETE       4

struct TiProperty
{
    const char* propertyName;
    int permissions;
    int nativePropertyNumber;
};

/*
 * TiObject
 *
 * Base class that reflects Javascript objects
 *
 */

class TiObject : public TiBase
{
public:
    TiObject();
    TiObject(const char* objectName);
    TiObject(const char* objectName, Handle<Value> value);
    virtual ~TiObject();
    static char* getStringFromObject(Handle<Value> value, const char* defaultString);
    static void freeString(char* str);
    static TiObject* getTiObjectFromJsObject(Handle<Value> value);
    static void setTiObjectToJsObject(Handle<Value> jsObject, TiObject* tiObj);
    static Handle<ObjectTemplate> getObjectTemplateFromJsObject(Handle<Value> value);
    virtual const char* getName() const;
    virtual void addMember(TiObject* object, const char* name = NULL);
    virtual Handle<Value> getValue() const;
    virtual Handle<Value> evaluate() const;
    virtual VALUE_MODIFY setValue(Handle<Value> value);
    virtual void forceSetValue(Handle<Value> value);
    virtual bool hasMembers() const;
    virtual bool isFunction() const;
    virtual bool canAddMembers() const;
    virtual bool isInitialized() const;
    virtual bool isUIObject() const;
    virtual void setTiMappingProperties(const TiProperty* prop, int propertyCount);
    virtual TiObject* getParentObject() const;
    virtual NativeObjectFactory* getNativeObjectFactory() const;
    virtual void setNativeObjectFactory(NativeObjectFactory* objectFactory);
    virtual NativeObject* getNativeObject() const;
    virtual void setupEvents();

protected:
    virtual void initializeTiObject(TiObject* parentObject);
    virtual Handle<Value> onFunctionCall(const Arguments& args);
    virtual void onCreateStaticMembers();
    virtual TiObject* onLookupMember(const char* memberName);
    virtual void onSetGetPropertyCallback(Handle<ObjectTemplate>* objTemplate);
    virtual void onSetFunctionCallback(Handle<ObjectTemplate>* objTemplate);
    virtual bool userCanAddMember(const char* propertyName) const;
    virtual void onSetProperty(const char* propertyName, Local<Value> value);
    virtual void onStartMessagePump();
    virtual VALUE_MODIFY onValueChange(Handle<Value> oldValue, Handle<Value> newValue);
    virtual VALUE_MODIFY onChildValueChange(TiObject* childObject, Handle<Value> oldValue, Handle<Value> newValue);
    virtual void setNativeObject(NativeObject* nativeObject);
    virtual void onSetupEvents();

private:
    static Handle<Value> propGetter_(Local<String> prop, const AccessorInfo& info);
    static Handle<Value> propSetter_(Local<String> prop, Local<Value> value, const AccessorInfo& info);
    static Handle<Value> functCallback_(const Arguments& args);
    Persistent<Value> value_;

    string name_;
    bool isInitialized_;
    TiObject* parentObject_;
    map<string, ObjectEntry> childObjectMap_;
    NativeObject* nativeObject_;
    NativeObjectFactory* nativeObjectFactory_;
    bool areEventsInitialized_;

#ifdef _TI_DEBUG_
    const char* cstrName_;
    string debugMembers_;
    const char* cstrdebugMembers_;
#endif // _TI_DEBUG_
};

#endif /* TIOBJECT_H_ */
