/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiStreamObject.h"

#include "TiBufferStreamObject.h"
#include "TiGenericFunctionObject.h"


TiStreamObject::TiStreamObject()
    : TiProxy("Stream")
{
}

TiStreamObject::~TiStreamObject()
{
}

void TiStreamObject::addObjectToParent(TiObject* parent)
{
    TiStreamObject* obj = new TiStreamObject;
    parent->addMember(obj);
}

void TiStreamObject::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createStream", this, _createStream);
}

Handle<Value> TiStreamObject::_createStream(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    return TiBufferStreamObject::createBufferStream(args[0])->getValue();
}
