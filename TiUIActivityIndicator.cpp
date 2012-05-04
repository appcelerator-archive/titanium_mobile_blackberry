/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIActivityIndicator.h"
#include "TiGenericFunctionObject.h"

TiUIActivityIndicator::TiUIActivityIndicator(NativeObjectFactory* nativeObjectFactory)
:TiUIBase(nativeObjectFactory, "")
{
}

TiUIActivityIndicator::~TiUIActivityIndicator()
{
}

TiUIActivityIndicator* TiUIActivityIndicator::createActivityIndicator(NativeObjectFactory* nativeObjectFactory)
{
	TiUIActivityIndicator* obj = new TiUIActivityIndicator(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUIActivityIndicator::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "show", this, show_);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "hide", this, hide_);
}

void TiUIActivityIndicator::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_ACTIVITYINDICATOR);
        setNativeObject(obj);
        obj->release();
    }
}

Handle<Value> TiUIActivityIndicator::show_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIActivityIndicator* obj = (TiUIActivityIndicator*) userContext;
    NativeObject* no = obj->getNativeObject();
    no->start();
    no->release();
    return Undefined();
}

Handle<Value> TiUIActivityIndicator::hide_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIActivityIndicator* obj = (TiUIActivityIndicator*) userContext;
    NativeObject* no = obj->getNativeObject();
    no->stop();
    no->release();
    return Undefined();
}
