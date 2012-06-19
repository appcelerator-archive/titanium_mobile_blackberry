/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUISwitch.h"

TiUISwitch::TiUISwitch(NativeObjectFactory* nativeObjectFactory)
    : TiUIBase(nativeObjectFactory, "")
{
}

TiUISwitch::~TiUISwitch()
{
}

TiUIBase* TiUISwitch::createSwitch(NativeObjectFactory* nativeObjectFactory)
{
    TiUISwitch* obj = new TiUISwitch(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUISwitch::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_TOGGLEBUTTON);
        setNativeObject(obj);
        obj->release();
    }
}
