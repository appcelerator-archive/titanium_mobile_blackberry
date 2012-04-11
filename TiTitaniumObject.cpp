/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiTitaniumObject.h"
#include "TiUIObject.h"
#include "TiAPIObject.h"

TiTitaniumObject::TiTitaniumObject()
        : TiObject("Titanium")
{
    objectFactory_ = NULL;
}

TiTitaniumObject::~TiTitaniumObject()
{
}

TiObject* TiTitaniumObject::createObject(NativeObjectFactory* objectFactory)
{
    TiTitaniumObject* obj = new TiTitaniumObject;
    obj->objectFactory_ = objectFactory;
    return obj;
}

void TiTitaniumObject::onCreateStaticMembers()
{
    ADD_STATIC_TI_VALUE("buildDate", String::New(__DATE__), this);
    ADD_STATIC_TI_VALUE("version", Number::New(2.0), this);
    // TODO: remove hard coded version number
    TiUIObject::addObjectToParent(this, objectFactory_);
    TiAPIObject::addObjectToParent(this);
}

bool TiTitaniumObject::canAddMembers() const
{
    return false;
}
