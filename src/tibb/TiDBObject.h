/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIDBOBJECT_H_
#define TIDBOBJECT_H_

#include "TiProxy.h"

class NativeObjectFactory;

/*
 * TiDBObject
 *
 * DB object that wraps SQLite database engine.
 *
 * Titanium.Database.DB namespace
 */
class TiDBObject : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);
    static TiDBObject* createDB(NativeObjectFactory* objectFactory, const Arguments& args);

protected:
    virtual ~TiDBObject();
    virtual void onCreateStaticMembers();
    virtual void initializeTiObject(TiObject* parentContext, const Arguments& args);

    static Handle<Value> _execute(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _close(void* userContext, TiObject* caller, const Arguments& args);

private:
    TiDBObject();
    explicit TiDBObject(NativeObjectFactory* objectFactory);
    TiDBObject(const TiDBObject&);
    TiDBObject& operator=(const TiDBObject&);

    NativeObjectFactory* objectFactory_;
};


#endif /* TIDBOBJECT_H_ */
