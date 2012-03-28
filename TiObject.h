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
    TiObject* obj_;
    void* userContext_;
    char* objectName_;
    void setObjectName(const char* objectName);
    const char* getObjectName() const;
};

class TiObject
{
public:
    TiObject();
    TiObject(const char* objectName);
    TiObject(const char* objectName, Handle<Value> value);
    virtual ~TiObject();
    void addRef();
    void release();
    virtual const char* getName() const;
    virtual void addMember(TiObject* object, const char* name = NULL);
    virtual Handle<Value> getValue();
    virtual bool hasMembers();
    virtual bool isFunction() const;
    virtual bool canAddMembers() const;
    virtual bool hasInitialized() const;
protected:
    virtual void initializeTiObject(TiObject* parentObject);
    virtual Handle<Value> onFunctionCall(const Arguments& args);
    virtual void onCreateStaticMembers();
    virtual TiObject* onLookupMember(const char* memberName);
    virtual void onSetGetPropertyCallback(Handle<ObjectTemplate>* objTemplate);
    virtual void onSetFunctionCallback(Handle<ObjectTemplate>* objTemplate);
    virtual Handle<ObjectTemplate>* getGlobalTemplate();
    virtual void setGlobalTemplate(Handle<ObjectTemplate>* globalTemplate);
    virtual bool userCanAddMember(const char* propertyName);
private:
    static Handle<Value> propGetter_(Local<String> prop,
                                     const AccessorInfo& info);
    static Handle<Value> propSetter_(Local<String> prop, Local<Value> value,
                                     const AccessorInfo& info);
    static Handle<Value> functCallback_(const Arguments& args);
    Persistent<Value> value_;

    int refCount_;
    char* name_;
    OBJECT_ENTRY** childObject_;
    int childObjectCount_;
    Handle<ObjectTemplate>* globalTemplate_;
    bool hasInitialized_;
};

#endif /* TIOBJECT_H_ */
