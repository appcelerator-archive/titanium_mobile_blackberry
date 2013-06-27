/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIPicker.h"
#include "TiGenericFunctionObject.h"

TiUIPicker::TiUIPicker()
    : TiUIBase("Picker")
{
}

TiUIPicker::~TiUIPicker()
{
}

TiUIPicker* TiUIPicker::createPicker(NativeObjectFactory* nativeObjectFactory)
{
    TiUIPicker* obj = new TiUIPicker;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUIPicker::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        //currently cascades only supports date/time picker that is why we should create native DateTimePicker object here
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_DATE_TIME_PICKER, this);
        setNativeObject(obj);
        obj->release();
    }
}

void TiUIPicker::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
}
