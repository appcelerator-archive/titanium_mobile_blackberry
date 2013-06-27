/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIScrollView.h"

TiUIScrollView::TiUIScrollView()
    : TiUIBase("ScrollView")
{
}

TiUIScrollView::~TiUIScrollView()
{
}

TiUIScrollView* TiUIScrollView::createScrollView(NativeObjectFactory* nativeObjectFactory)
{
    TiUIScrollView* obj = new TiUIScrollView;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUIScrollView::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_SCROLL_VIEW, this);
        setNativeObject(obj);
        obj->release();
    }
}

