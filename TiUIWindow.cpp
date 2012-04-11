/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIWindow.h"
#include "TiGenericFunctionObject.h"

TiUIWindow::TiUIWindow(NativeObjectFactory* objectFactory, const char* name)
        : TiUIBase(objectFactory, name)
{
}

TiUIWindow::~TiUIWindow()
{
}

TiUIWindow* TiUIWindow::createWindow(NativeObjectFactory* objectFactory, const char* name)
{
    TiUIWindow* obj = new TiUIWindow(objectFactory, name);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUIWindow::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "open", this, open_);
}

void TiUIWindow::initializeTiObject(TiObject* parentContext)
{
    if (!hasInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(NO_TYPE_WINDOW);
        setNativeObject(obj);
        obj->release();
    }
}

Handle<Value> TiUIWindow::open_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIWindow* obj = (TiUIWindow*) userContext;
    NativeObject* no = obj->getNativeObject();
    no->open();
    no->release();
    return Undefined();
}

