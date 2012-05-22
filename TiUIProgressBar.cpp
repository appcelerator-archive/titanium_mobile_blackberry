/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIProgressBar.h"

TiUIProgressBar::TiUIProgressBar(NativeObjectFactory* nativeObjectFactory)
    : TiUIBase(nativeObjectFactory, "")
{
}

TiUIProgressBar::~TiUIProgressBar()
{
}

TiUIBase* TiUIProgressBar::createProgressBar(NativeObjectFactory* nativeObjectFactory)
{
    TiUIProgressBar* obj = new TiUIProgressBar(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUIProgressBar::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_PROGRESSBAR);
        setNativeObject(obj);
        obj->release();
    }
}

