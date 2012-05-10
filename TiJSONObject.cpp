/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiJSONObject.h"

#include "TiGenericFunctionObject.h"


TiJSONObject::TiJSONObject(NativeObjectFactory* objectFactory)
    : TiObject("JSON")
{
    objectFactory_ = objectFactory;
}

TiJSONObject::~TiJSONObject()
{
}

void TiJSONObject::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory)
{
    TiJSONObject* obj = new TiJSONObject(objectFactory);
    parent->addMember(obj);
    obj->release();
}

void TiJSONObject::onCreateStaticMembers()
{
    TiGenericFunctionObject::addGenericFunctionToParent(this, "parse", this, _parse);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "stringify", this, _stringify);
}

bool TiJSONObject::canAddMembers() const
{
    return false;
}

Handle<Value> TiJSONObject::_parse(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: Implement
    return Undefined();
}

Handle<Value> TiJSONObject::_stringify(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: Implement
    return Undefined();
}
