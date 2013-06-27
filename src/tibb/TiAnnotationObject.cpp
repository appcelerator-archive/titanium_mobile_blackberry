/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiAnnotationObject.h"
#include "TiGenericFunctionObject.h"

TiAnnotationObject::TiAnnotationObject()
    : TiUIBase("Annotation")
{
}

TiAnnotationObject::~TiAnnotationObject()
{
}

TiAnnotationObject* TiAnnotationObject::createAnnotationObject(NativeObjectFactory* nativeObjectFactory)
{
	TiAnnotationObject* obj = new TiAnnotationObject;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiAnnotationObject::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
}


void TiAnnotationObject::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_ANNOTATION, this);
        setNativeObject(obj);
        obj->release();
    }
}
