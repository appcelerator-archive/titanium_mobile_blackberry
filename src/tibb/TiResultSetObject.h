/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIRESULTSETOBJECT_H_
#define TIRESULTSETOBJECT_H_

#include "TiProxy.h"

class NativeObjectFactory;

/*
 * TiResultSetObject
 *
 * ResultSet object that wraps SQLite database engine.
 *
 * Titanium.Database.ResultSet namespace
 */
class TiResultSetObject : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);
    static TiResultSetObject* createResultSet(NativeObjectFactory* objectFactory);

protected:
    virtual ~TiResultSetObject();
    virtual void onCreateStaticMembers();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiResultSetObject();
    explicit TiResultSetObject(NativeObjectFactory* objectFactory);
    TiResultSetObject(const TiResultSetObject&);
    TiResultSetObject& operator=(const TiResultSetObject&);

    void setTiResultSetMappingProperties(const TiProperty* props, int propertyCount);
    static VALUE_MODIFY _valueModify(int propertyNumber, TiObject* value, void* context);
    static Handle<Value> _getValue(int propertyNumber, void* context);

    static Handle<Value> _isValidRow(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _fieldByName(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _field(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _next(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _close(void* userContext, TiObject* caller, const Arguments& args);

    NativeObjectFactory* objectFactory_;
};


#endif /* TIRESULTSETOBJECT_H_ */
