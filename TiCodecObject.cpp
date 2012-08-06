/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiCodecObject.h"

#include "TiConstants.h"
#include "TiGenericFunctionObject.h"

TiCodecObject::TiCodecObject()
    : TiProxy("Codec")
{
}

TiCodecObject::~TiCodecObject()
{
}

void TiCodecObject::addObjectToParent(TiObject* parent)
{
    TiCodecObject* obj = new TiCodecObject();
    parent->addMember(obj);
    obj->release();
}

void TiCodecObject::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();

    TiGenericFunctionObject::addGenericFunctionToParent(this, "decodeNumber", this, _decodeNumber);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "decodeString", this, _decodeString);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "encodeNumber", this, _encodeNumber);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "encodeString", this, _encodeString);

    // Adding javascript constants from Ti.Codec
    ADD_STATIC_TI_VALUE("BIG_ENDIAN", Number::New(Ti::Codec::BIG_ENDIAN), this);
    ADD_STATIC_TI_VALUE("LITTLE_ENDIAN", Number::New(Ti::Codec::LITTLE_ENDIAN), this);
    // TODO: Add charset constants
}

Handle<Value> TiCodecObject::_decodeNumber(void* /*userContext*/, TiObject* /*caller*/, const Arguments& /*args*/)
{
    return Undefined();
}

Handle<Value> TiCodecObject::_decodeString(void* /*userContext*/, TiObject* /*caller*/, const Arguments& /*args*/)
{
    return Undefined();
}

Handle<Value> TiCodecObject::_encodeNumber(void* /*userContext*/, TiObject* /*caller*/, const Arguments& /*args*/)
{
    return Undefined();
}

Handle<Value> TiCodecObject::_encodeString(void* /*userContext*/, TiObject* /*caller*/, const Arguments& /*args*/)
{
    return Undefined();
}
