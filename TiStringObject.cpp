/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiStringObject.h"

#include "TiGenericFunctionObject.h"


TiStringObject::TiStringObject(NativeObjectFactory* objectFactory)
    : TiObject("String")
{
    objectFactory_ = objectFactory;
}

TiStringObject::~TiStringObject()
{
}

void TiStringObject::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory)
{
    TiStringObject* obj = new TiStringObject(objectFactory);
    parent->addMember(obj);
    obj->release();
}

void TiStringObject::onCreateStaticMembers()
{
    TiGenericFunctionObject::addGenericFunctionToParent(this, "format", this, _format);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "formatCurrency", this, _formatCurrency);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "formatDate", this, _formatDate);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "formatDecimal", this, _formatDecimal);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "formatTime", this, _formatTime);
}

bool TiStringObject::canAddMembers() const
{
    return false;
}

Handle<Value> TiStringObject::_format(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: Implement
    return Undefined();
}

Handle<Value> TiStringObject::_formatCurrency(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: Implement
    return Undefined();
}

Handle<Value> TiStringObject::_formatDate(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: Implement
    return Undefined();
}

Handle<Value> TiStringObject::_formatDecimal(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: Implement
    return Undefined();
}

Handle<Value> TiStringObject::_formatTime(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: Implement
    return Undefined();
}
