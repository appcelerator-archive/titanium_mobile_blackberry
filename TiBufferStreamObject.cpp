/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiBufferStreamObject.h"


TiBufferStreamObject::TiBufferStreamObject()
    : TiIOStreamObject("BufferStream")
{
}

TiBufferStreamObject::~TiBufferStreamObject()
{
}

void TiBufferStreamObject::addObjectToParent(TiObject* parent)
{
    TiBufferStreamObject* obj = new TiBufferStreamObject;
    parent->addMember(obj);
}

TiBufferStreamObject* TiBufferStreamObject::createBufferStream(Handle<Value> /*params*/)
{
    Handle<Object> global = Context::GetCurrent()->Global();
    Handle<Object> staticTiObject = global->Get(String::New("Ti"))->ToObject();
    Handle<Object> staticBsObject = staticTiObject->Get(String::New("BufferStream"))->ToObject();
    Handle<Object> result = staticBsObject->Clone();
    TiBufferStreamObject* bsObject = new TiBufferStreamObject;
    bsObject->setValue(result);
    // TODO: this messes things up
    //setTiObjectToJsObject(result, bsObject);
    return bsObject;
}

void TiBufferStreamObject::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();
}
