/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIMAP_H_
#define TIMAP_H_

#include "TiProxy.h"

typedef TiProxy* (*CREATEOBJECTCALLBACK)(NativeObjectFactory*);

/*
 * TiMap
 *
 * Titanium.Map namespace
 */
class TiMap : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);

protected:
    virtual ~TiMap();
    virtual void onCreateStaticMembers();

private:
    TiMap();
    TiMap(NativeObjectFactory* objectFactory);
    static Handle<Value> _createControlHelper(void* userContext, CREATEOBJECTCALLBACK createCallback, const Arguments& args);
    static Handle<Value> _createView(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createAnnotation(void* userContext, TiObject* caller, const Arguments& args);

    NativeObjectFactory* objectFactory_;
    NativeObject* contentContainer_;
};

#endif /* TIMAP_H_ */
