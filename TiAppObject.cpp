/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiAppObject.h"

#include "TiAppPropertiesObject.h"

TiAppObject::TiAppObject()
    : TiObject("App")
{
}

TiAppObject::~TiAppObject()
{
}

void TiAppObject::addObjectToParent(TiObject* parent)
{
    TiAppObject* obj = new TiAppObject;
    parent->addMember(obj);
}

void TiAppObject::onCreateStaticMembers()
{
    TiAppPropertiesObject::addObjectToParent(this);
}
