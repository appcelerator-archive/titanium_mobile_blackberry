/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TISTRINGOBJECT_H_
#define TISTRINGOBJECT_H_

#include "TiObject.h"


/*
 * TiStringObject
 *
 * String namespace
 */
class TiStringObject : public TiObject
{
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);

protected:
    virtual ~TiStringObject();
    virtual void onCreateStaticMembers();
    virtual bool canAddMembers() const;

private:
    explicit TiStringObject();
    explicit TiStringObject(NativeObjectFactory* objectFactory);

    /* Not copiable; Not assignable */
    TiStringObject(const TiStringObject&);
    TiStringObject& operator=(const TiStringObject&);

    static Handle<Value> _format(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _formatCurrency(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _formatDate(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _formatDecimal(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _formatTime(void* userContext, TiObject* caller, const Arguments& args);

    NativeObjectFactory* objectFactory_;
};

#endif /* TISTRINGOBJECT_H_ */
