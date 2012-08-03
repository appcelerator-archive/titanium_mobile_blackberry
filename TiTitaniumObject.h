/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TITITANIUMOBJECT_H_
#define TITITANIUMOBJECT_H_

#include "TiObject.h"

class TiCascadesApp;

/*
 * TiTitaniumObject
 *
 * Titanium namespace
 */
class TiTitaniumObject : public TiObject
{
public:
    static TiObject* createObject(NativeObjectFactory* objectFactory);

protected:
    virtual ~TiTitaniumObject();
    virtual void onCreateStaticMembers();
    virtual bool canAddMembers() const;
    virtual NativeObjectFactory* getNativeObjectFactory() const;

private:
    explicit TiTitaniumObject();
    TiTitaniumObject(const TiTitaniumObject&);
    TiTitaniumObject& operator=(const TiTitaniumObject&);
    static Handle<Value> _include(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createBuffer(void* userContext, TiObject* caller, const Arguments& args);
    NativeObjectFactory* objectFactory_;
};

#endif /* TITITANIUMOBJECT_H_ */
