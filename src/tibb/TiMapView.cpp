/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiMapView.h"
#include "TiGenericFunctionObject.h"

TiMapView::TiMapView(const char* name)
    : TiUIBase(name)
{
}

TiMapView::TiMapView()
    : TiUIBase("")
{
}

TiMapView::~TiMapView()
{
}

TiMapView* TiMapView::createMapView(NativeObjectFactory* nativeObjectFactory)
{
	TiMapView* obj = new TiMapView;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiMapView::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
}


void TiMapView::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_MAPVIEW, this);
        setNativeObject(obj);
        obj->release();
    }
}
