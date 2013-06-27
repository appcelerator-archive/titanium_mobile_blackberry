/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIButton.h"

TiUIButton::TiUIButton()
    : TiUIBase("Button")
{
}

TiUIButton::~TiUIButton()
{
}

TiUIButton* TiUIButton::createButton(NativeObjectFactory* nativeObjectFactory)
{
    TiUIButton* obj = new TiUIButton;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUIButton::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_BUTTON, this);
        setNativeObject(obj);
        obj->release();
    }
}

