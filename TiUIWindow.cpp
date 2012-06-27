/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIWindow.h"
#include "TiGenericFunctionObject.h"

TiUIWindow::TiUIWindow(const char* name)
    : TiUIBase(name)
{
}

TiUIWindow::~TiUIWindow()
{
}

TiUIBase* TiUIWindow::createWindow(NativeObjectFactory* objectFactory)
{
    TiUIWindow* obj = new TiUIWindow("");
    obj->setNativeObjectFactory(objectFactory);
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
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_WINDOW);
        setNativeObject(obj);
        obj->release();
    }
}

Handle<Value> TiUIWindow::open_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIWindow* obj = (TiUIWindow*) userContext;
    NativeObject* no = obj->getNativeObject();
    no->completeInitialization();
    vector<ObjectEntry>::iterator it;
    for (it = obj->childControls_.begin(); it != obj->childControls_.end(); it++)
    {
        (*it)->setupEvents();
    }
    no->open();
    no->release();
    return Undefined();
}

