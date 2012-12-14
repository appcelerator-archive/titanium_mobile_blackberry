/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiPropertyGetObject.h"

TiPropertyGetObject::TiPropertyGetObject(const char* propertyName) :
    TiObject(propertyName),
    context_(NULL),
    getCallback_(NULL)
{
}

TiPropertyGetObject::~TiPropertyGetObject()
{
}

TiObject* TiPropertyGetObject::createGetProperty(TiObject* parent, const char* name,
        void* context, GET_PROPERTY_CALLBACK cb)
{
    TiPropertyGetObject* obj = new TiPropertyGetObject(name);
    obj->context_ = context;
    obj->getCallback_ = cb;
    parent->addMember(obj);
    return obj;
}

Handle<Value> TiPropertyGetObject::getValue() const
{
    if (getCallback_ == NULL)
    {
        return Undefined();
    }
    return (getCallback_)(context_);
}

VALUE_MODIFY TiPropertyGetObject::onValueChange(Handle<Value>, Handle<Value>)
{
    // Read only
    return VALUE_MODIFY_DENY;
}
