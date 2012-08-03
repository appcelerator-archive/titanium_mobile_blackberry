/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIBUFFEROBJECT_H_
#define TIBUFFEROBJECT_H_

#include "TiProxy.h"

/*
 * TiBufferObject
 *
 * Buffer is a mutable, resizable container for raw data.
 * A Buffer works like a resizable array of byte values.
 * Use the Titanium.createBuffer method to create a buffer.
 *
 * Titanium.Buffer namespace
 */
class TiBufferObject : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent);
    static TiBufferObject* createBuffer(NativeObjectFactory* objectFactory);

protected:
    virtual ~TiBufferObject();
    virtual void onCreateStaticMembers();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiBufferObject();
    TiBufferObject(const TiBufferObject&);
    TiBufferObject& operator=(const TiBufferObject&);

    void setTiBufferMappingProperties(const TiProperty* props, int propertyCount);
    static VALUE_MODIFY _valueModify(int propertyNumber, TiObject* value, void* context);
    static Handle<Value> _getValue(int propertyNumber, void* context);

    static Handle<Value> _append(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _copy(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _fill(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _insert(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _clone(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _clear(void* userContext, TiObject* caller, const Arguments& args);
};

#endif /* TIBUFFEROBJECT_H_ */
