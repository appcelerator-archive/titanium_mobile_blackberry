/*
 * TiUISlider.cpp
 *
 *  Created on: 2012-04-17
 *      Author: dcampbell
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
    if (!hasInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(NO_TYPE_SLIDER);
        setNativeObject(obj);
        obj->release();
    }
}

