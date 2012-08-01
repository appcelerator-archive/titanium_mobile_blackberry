/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUISwitch.h"

TiUISwitch::TiUISwitch()
    : TiUIBase("")
{
}

TiUISwitch::~TiUISwitch()
{
}

TiUISwitch* TiUISwitch::createSwitch(NativeObjectFactory* nativeObjectFactory)
{
    TiUISwitch* obj = new TiUISwitch;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUISwitch::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiProxy::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_TOGGLEBUTTON);
        setNativeObject(obj);
        obj->release();
    }
}
