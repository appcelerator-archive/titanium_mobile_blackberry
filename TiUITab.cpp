/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITab.h"

TiUITab::TiUITab(NativeObjectFactory* nativeObjectFactory)
    : TiUIBase(nativeObjectFactory, "")
{
}

TiUITab::~TiUITab()
{
}

TiUIBase* TiUITab::createTab(NativeObjectFactory* nativeObjectFactory)
{
    TiUITab* obj = new TiUITab(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUITab::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_TAB);
        setNativeObject(obj);
        obj->release();
    }
}
