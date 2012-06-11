/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiDateObject.h"

TiDateObject::TiDateObject(NativeObjectFactory* objectFactory)
    : TiObject("Date")
{
    objectFactory_ = objectFactory;
}

TiDateObject::~TiDateObject()
{
}

void TiDateObject::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory)
{
    TiDateObject* obj = new TiDateObject(objectFactory);
    parent->addMember(obj);
    obj->release();
}

void TiDateObject::onCreateStaticMembers()
{
}

bool TiDateObject::canAddMembers() const
{
    return false;
}
