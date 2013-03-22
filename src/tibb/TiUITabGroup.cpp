/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITabGroup.h"
#include "TiGenericFunctionObject.h"
#include "NativeMessageStrings.h"
#include "NativeTabGroupObject.h"

TiUITabGroup::TiUITabGroup()
    : TiUIBase("")
{
}

TiUITabGroup::~TiUITabGroup()
{
}

TiUITabGroup* TiUITabGroup::createTabGroup(NativeObjectFactory* objectFactory)
{
    TiUITabGroup* obj = new TiUITabGroup;
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUITabGroup::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "open", this, _open);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "addTab", this, _addTab);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "removeTab", this, _removeTab);
}

void TiUITabGroup::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_TABGROUP, this);
        setNativeObject(obj);
        obj->release();
    }
}

Handle<Value> TiUITabGroup::_open(void* userContext, TiObject*, const Arguments&)
{
    HandleScope handleScope;
    TiUITabGroup* obj = (TiUITabGroup*) userContext;
    NativeTabGroupObject* no = static_cast<NativeTabGroupObject*>(obj->getNativeObject());
    no->open();
    no->release();
    return Undefined();
}

Handle<Value> TiUITabGroup::_addTab(void* userContext, TiObject* caller, const Arguments& args)
{
    TiUIBase::_add(userContext, caller, args);
    return Undefined();
}

Handle<Value> TiUITabGroup::_removeTab(void* userContext, TiObject* caller, const Arguments& args)
{
    TiUIBase::_remove(userContext, caller, args);
    return Undefined();
}

