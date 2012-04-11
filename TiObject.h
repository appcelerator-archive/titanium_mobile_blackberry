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

#include "TiObjectScope.h"
#include "NativeObject.h"
#include "NativeObjectFactory.h"

#include <v8.h>

using namespace v8;
using namespace std;

// void ADD_STATUS_TI_VALUE(const char* name, Handle<Value> value, TiObject* parent)

#define ADD_STATIC_TI_VALUE(N,V,P)		{TiObject* __ti__=new TiObject((N),(V));(P)->addMember(__ti__);__ti__->release();}

class TiObject;

struct OBJECT_ENTRY
{
    OBJECT_ENTRY();
    ~OBJECT_ENTRY();
    void setObjectName(const char* objectName);
    const char* getObjectName() const;

    TiObject* obj_;
    void* userContext_;
    char* objectName_;
};

#define JS_TYPE_UNDEFINED           1
#define JS_TYPE_STRING              2
#define JS_TYPE_NUMBER              4
#define JS_TYPE_FUNCTION            8

#define NATIVE_TYPE_VOID            0
#define NATIVE_TYPE_CSTRING         1
#define NATIVE_TYPE_INT             2
#define NATIVE_TYPE_DOUBLE          3

enum VALUE_MODIFY
{
    VALUE_MODIFY_ALLOW, VALUE_MODIFY_DENY, VALUE_MODIFY_NOT_SUPPORTED, VALUE_MODIFY_INVALID
};

#define TI_PROP_PERMISSION_READ         1
#define TI_PROP_PERMISSION_WRITE        2
#define TI_PROP_PERMISSION_DELETE       4

struct TI_PROPERTY
{
    const char* propertyName;
    const char* propertySetterFunctionName;
    const char* defaultValue;
    int permissions;
    int nativePropertyNumber;
};

class TiObject
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
    void addRef();
    void release();
    virtual const char* getName() const;
    virtual void addMember(TiObject* object, const char* name = NULL);
    virtual Handle<Value> getValue();
    virtual VALUE_MODIFY setValue(Handle<Value> value);
    virtual bool hasMembers() const;
    virtual bool isFunction() const;
    virtual bool canAddMembers() const;
    virtual bool hasInitialized() const;
    virtual bool isUIObject() const;
    virtual void setTiMappingProperties(const TI_PROPERTY* prop, int propertyCount);
    virtual TiObject* getParentObject() const;
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
private:
    static Handle<Value> propGetter_(Local<String> prop, const AccessorInfo& info);
    static Handle<Value> propSetter_(Local<String> prop, Local<Value> value, const AccessorInfo& info);
    static Handle<Value> functCallback_(const Arguments& args);
    Persistent<Value> value_;

    int refCount_;
    char* name_;
    OBJECT_ENTRY** childObject_;
    int childObjectCount_;
    bool hasInitialized_;
    TiObject* parentObject_;
};

#endif /* TIOBJECT_H_ */
