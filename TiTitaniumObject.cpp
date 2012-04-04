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
    cascadesApp_=NULL;
}

TiTitaniumObject::~TiTitaniumObject()
{
}

TiObject* TiTitaniumObject::createObject(TiCascadesApp& cascadesApp)
{
    TiTitaniumObject* obj=new TiTitaniumObject;
    obj->cascadesApp_=&cascadesApp;
    return obj;
}

void TiTitaniumObject::onCreateStaticMembers()
{
    ADD_STATIC_TI_VALUE("buildDate", String::New(__DATE__), this);
    ADD_STATIC_TI_VALUE("version", Number::New(2.0), this);
    TiUIObject::addObjectToParent(this,*cascadesApp_);
    TiAPIObject::addObjectToParent(this);
}

bool TiTitaniumObject::canAddMembers() const
{
    return false;
}
