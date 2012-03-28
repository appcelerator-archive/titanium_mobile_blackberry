/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIObject.h"
#include "TiGenericFunctionObject.h"

TiUIObject::TiUIObject()
        : TiObject("UI")
{
}

TiUIObject::~TiUIObject()
{
}

void TiUIObject::addObjectToParent(TiObject* parent)
{
    TiUIObject* obj = new TiUIObject;
    parent->addMember(obj);
    obj->release();
}

void TiUIObject::onCreateStaticMembers()
{
    TiGenericFunctionObject::addGenericFunctionToParent(this,
                                                        "setBackgroundColor",
                                                        this,
                                                        setBackgroundColor_);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createTabGroup",
                                                        this, createTabGroup_);
}

Handle<Value> TiUIObject::setBackgroundColor_(void* userContext,
                                              TiObject* caller,
                                              const Arguments& args)
{
    return Undefined();
}

Handle<Value> TiUIObject::createTabGroup_(void* userContext, TiObject* caller,
                                          const Arguments& args)
{
    return Undefined();
}
