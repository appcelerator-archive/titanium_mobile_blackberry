/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITextField.h"

TiUITextField::TiUITextField(NativeObjectFactory* nativeObjectFactory)
        : TiUIBase(nativeObjectFactory, "")
{
}

TiUITextField::~TiUITextField()
{
}

TiUITextField* TiUITextField::createTextField(NativeObjectFactory* nativeObjectFactory)
{
    TiUITextField* obj = new TiUITextField(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUITextField::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_TEXT_FIELD);
        setNativeObject(obj);
        obj->release();
    }
}
