/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiStreamObject.h"

#include "TiBufferObject.h"
#include "TiBufferStreamObject.h"
#include "TiConstants.h"
#include "TiGenericFunctionObject.h"
#include "TiIOStreamObject.h"
#include "TiMessageStrings.h"

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
    ADD_STATIC_TI_VALUE("MODE_APPEND", Number::New(Ti::Stream::MODE_APPEND), this);
    ADD_STATIC_TI_VALUE("MODE_READ", Number::New(Ti::Stream::MODE_READ), this);
    ADD_STATIC_TI_VALUE("MODE_WRITE", Number::New(Ti::Stream::MODE_WRITE), this);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createStream", this, _createStream);
}

Handle<Value> TiStreamObject::_createStream(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsObject())
    {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }

    Handle<Object> params = args[0]->ToObject();
    if (!params->Has(String::New("source")) || !params->Has(String::New("mode")))
    {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }
    Handle<Value> source = params->Get(String::New("source"));
    Handle<Value> mode = params->Get(String::New("mode"));
    Handle<Value> pos = Number::New(0);
    TiObject* sourceObj = getTiObjectFromJsObject(source);
    TiIOStreamObject* resultObj = NULL;
    {
        TiBufferObject* bufferObj = dynamic_cast<TiBufferObject*>(sourceObj);
        if (bufferObj != NULL)
        {
            resultObj = TiBufferStreamObject::createBufferStream(params);
            if (mode->ToNumber()->Value() == Ti::Stream::MODE_APPEND)
            {
                pos = source->ToObject()->Get(String::New("length"))->ToNumber();
            }
        }
        else
        {
            // TODO: check for blob, and validate mode
            return ThrowException(String::New(Ti::Msg::Invalid_arguments));
        }
    }

    if (resultObj == NULL)
    {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }
    Handle<Object> result = resultObj->getValue()->ToObject();
    result->Set(String::New("source"), source);
    result->Set(String::New("mode"), mode);
    result->Set(String::New("pos"), pos);
    return result;
}
