/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIImageButton.h"

TiUIImageButton::TiUIImageButton()
    : TiUIBase("ImageButton")
{
}

TiUIImageButton::~TiUIImageButton()
{
}

TiUIImageButton* TiUIImageButton::createButton(NativeObjectFactory* nativeObjectFactory)
{
    TiUIImageButton* obj = new TiUIImageButton;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUIImageButton::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_IMAGE_BUTTON, this);
        setNativeObject(obj);
        obj->release();
    }
}

