/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITextArea.h"

TiUITextArea::TiUITextArea()
    : TiUIBase("")
{
}

TiUITextArea::~TiUITextArea()
{
}

TiUITextArea* TiUITextArea::createTextArea(NativeObjectFactory* nativeObjectFactory)
{
    TiUITextArea* obj = new TiUITextArea;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUITextArea::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_TEXT_AREA, this);
        setNativeObject(obj);
        obj->release();
    }
}
