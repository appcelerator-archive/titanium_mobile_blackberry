/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIScrollableView.h"

TiUIScrollableView::TiUIScrollableView()
    : TiUIBase("")
{
}

TiUIScrollableView::~TiUIScrollableView()
{
}

TiUIScrollableView* TiUIScrollableView::createScrollableView(NativeObjectFactory* nativeObjectFactory)
{
    TiUIScrollableView* obj = new TiUIScrollableView;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUIScrollableView::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_SCROLLABLE_VIEW, this);
        setNativeObject(obj);
        obj->release();
    }
}

