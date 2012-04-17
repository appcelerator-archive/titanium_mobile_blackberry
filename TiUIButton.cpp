/*
 * TiUIButton.cpp
 *
 *  Created on: 2012-04-17
 *      Author: dcampbell
 */

#include "TiUIButton.h"

TiUIButton::TiUIButton(NativeObjectFactory* nativeObjectFactory):
    TiUIBase(nativeObjectFactory,"")
{
}

TiUIButton::~TiUIButton()
{
}

TiUIButton* TiUIButton::createButton(NativeObjectFactory* nativeObjectFactory)
{
    TiUIButton* obj=new TiUIButton(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUIButton::initializeTiObject(TiObject* parentContext)
{
    if (!hasInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(NO_TYPE_BUTTON);
        setNativeObject(obj);
        obj->release();
    }
}

