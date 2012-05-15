/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIJSONOBJECT_H_
#define TIJSONOBJECT_H_

#include "TiObject.h"


/*
 * TiJSONObject
 *
 * JSON namespace
 */
class TiJSONObject : public TiObject
{
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);

protected:
    virtual ~TiJSONObject();
    virtual void onCreateStaticMembers();
    virtual bool canAddMembers() const;

private:
    explicit TiJSONObject();
    explicit TiJSONObject(NativeObjectFactory* objectFactory);

    /* Not copiable; Not assignable */
    TiJSONObject(const TiJSONObject&);
    TiJSONObject& operator=(const TiJSONObject&);

    static Handle<Value> _parse(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _stringify(void* userContext, TiObject* caller, const Arguments& args);

    NativeObjectFactory* objectFactory_;
};

#endif /* TIJSONOBJECT_H_ */
