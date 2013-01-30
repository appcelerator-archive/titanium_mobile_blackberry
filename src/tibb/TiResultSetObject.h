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

    static Handle<Value> _isValidRow(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _fieldByName(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _field(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _next(void* userContext, TiObject* caller, const Arguments& args);

private:
    TiResultSetObject();
    explicit TiResultSetObject(NativeObjectFactory* objectFactory);
    TiResultSetObject(const TiResultSetObject&);
    TiResultSetObject& operator=(const TiResultSetObject&);

    NativeObjectFactory* objectFactory_;
};


#endif /* TIRESULTSETOBJECT_H_ */
