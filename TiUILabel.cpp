/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUILabel.h"
#include <string.h>

TiUILabel::TiUILabel(NativeObjectFactory* nativeObjectFactory)
        : TiUIBase(nativeObjectFactory, "")
{
}

TiUILabel::~TiUILabel()
{
}

TiUILabel* TiUILabel::createLabel(NativeObjectFactory* nativeObjectFactory)
{
    TiUILabel* obj = new TiUILabel(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUILabel::initializeTiObject(TiObject* parentContext)
{
    if (!hasInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(NO_TYPE_LABEL);
        setNativeObject(obj);
        obj->release();
    }
}

