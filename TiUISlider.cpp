/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUISlider.h"

TiUISlider::TiUISlider(NativeObjectFactory* nativeObjectFactory)
    : TiUIBase(nativeObjectFactory, "")
{
}

TiUISlider::~TiUISlider()
{
}

TiUISlider* TiUISlider::createSlider(NativeObjectFactory* nativeObjectFactory)
{
    TiUISlider* obj = new TiUISlider(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUISlider::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_SLIDER);
        setNativeObject(obj);
        obj->release();
    }
}

