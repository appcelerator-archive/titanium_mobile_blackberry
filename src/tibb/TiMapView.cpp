/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiMapView.h"
#include "TiGenericFunctionObject.h"
#include "NativeMapViewObject.h"

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
    TiGenericFunctionObject::addGenericFunctionToParent(this, "removeAnnotation", this, _removeAnnotation);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "addAnnotation", this, _addAnnotation);

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

Handle<Value> TiMapView::_removeAnnotation(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiMapView* obj = (TiMapView*) userContext;
	NativeMapViewObject* nativeMapViewObject = (NativeMapViewObject*) obj->getNativeObject();

	TiObject* tiObj = TiObject::getTiObjectFromJsObject(args[0]);
	NativeObject* annotation = (NativeObject*)tiObj->getNativeObject();

	nativeMapViewObject->removeAnnotation(annotation);

	return Undefined();
}

Handle<Value> TiMapView::_addAnnotation(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiMapView* obj = (TiMapView*) userContext;
	NativeMapViewObject* nativeMapViewObject = (NativeMapViewObject*) obj->getNativeObject();

	TiObject* tiObj = TiObject::getTiObjectFromJsObject(args[0]);
	NativeObject* annotation = (NativeObject*)tiObj->getNativeObject();

	nativeMapViewObject->addAnnotation(annotation);

	return Undefined();
}
