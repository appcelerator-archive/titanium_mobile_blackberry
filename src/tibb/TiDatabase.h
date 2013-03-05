/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIDATABASE_H_
#define TIDATABASE_H_

#include "TiProxy.h"

class NativeObjectFactory;

/*
 * TiDatabase
 *
 * The top level database module.
 * The database module is a wrapper around the SQLite database engine.
 *
 * Titanium.Database namespace
 */
class TiDatabase : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);
    //static Handle<Value> open(void* userContext, TiObject* caller, const Arguments& args);

protected:
    virtual ~TiDatabase();
    virtual void onCreateStaticMembers();
    static Handle<Value> _open(void* userContext, TiObject* caller, const Arguments& args);

private:
    TiDatabase();
    explicit TiDatabase(NativeObjectFactory* objectFactory);
    TiDatabase(const TiDatabase&);
    TiDatabase& operator=(const TiDatabase&);

    NativeObjectFactory* objectFactory_;
};

#endif /* TIDATABASE_H_ */
