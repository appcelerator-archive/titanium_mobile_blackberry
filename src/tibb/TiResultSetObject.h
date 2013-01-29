/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIRESULTSETOBJECT_H_
#define TIRESULTSETOBJECT_H_

/*
 * TiResultSetObject
 *
 * TCP socket that implements the Titanium.IOStream interface.
 *
 * Titanium.Database.ResultSet namespace
 */

#include "TiProxy.h"

class NativeObjectFactory;

class TiResultSetObject : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent);
    static TiResultSetObject* createTCP(NativeObjectFactory* objectFactory);

protected:
    virtual ~TiResultSetObject();
    virtual void onCreateStaticMembers();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiResultSetObject();
    TiResultSetObject(const TiResultSetObject&);
    TiResultSetObject& operator=(const TiResultSetObject&);

    void setTiBufferMappingProperties(const TiProperty* props, int propertyCount);
    static VALUE_MODIFY _valueModify(int propertyNumber, TiObject* value, void* context);
    static Handle<Value> _getValue(int propertyNumber, void* context);

    static Handle<Value> _connect(void* userContext, TiObject* caller, const Arguments& args);
};


#endif /* TIRESULTSETOBJECT_H_ */
