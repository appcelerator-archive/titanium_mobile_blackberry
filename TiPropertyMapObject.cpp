/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiPropertyMapObject.h"
#include "TiUIBase.h"

TiPropertyMapObject::TiPropertyMapObject(const char* name)
    : TiObject(name)
    , callback_(NULL)
    , getCallback_(NULL)
{
    nativeObject_ = NULL;
    parentObject_ = NULL;
}

TiPropertyMapObject::~TiPropertyMapObject()
{
    if (nativeObject_ != NULL)
    {
        nativeObject_->release();
        nativeObject_ = NULL;
    }
}

TiPropertyMapObject* TiPropertyMapObject::addProperty(TiUIBase* parent, const char* name, int propertyNumber,
        MODIFY_VALUE_CALLBACK cb, void* context)
{
    TiPropertyMapObject* object = new TiPropertyMapObject(name);
    object->propertyNumber_ = propertyNumber;
    object->callback_ = cb;
    object->context_ = context;
    parent->addMember(object);
    object->parentObject_ = parent;
    object->nativeObject_ = parent->getNativeObject();
    return object;
}

TiPropertyMapObject* TiPropertyMapObject::addProperty(TiObject* parent, const char* name, int propertyNumber,
        GET_PROPERTY_VALUE_CALLBACK cb, void* context)
{
    TiPropertyMapObject* object = new TiPropertyMapObject(name);
    object->propertyNumber_ = propertyNumber;
    object->getCallback_ = cb;
    object->context_ = context;
    parent->addMember(object);
    return object;
}

Handle<Value> TiPropertyMapObject::getValue() const
{
    if (getCallback_ == NULL)
    {
        return TiObject::getValue();
    }
    return (getCallback_)(propertyNumber_, context_);
}

VALUE_MODIFY TiPropertyMapObject::onValueChange(Handle<Value> oldValue, Handle<Value> newValue)
{
    HandleScope handleScope;
    VALUE_MODIFY modify = TiObject::onValueChange(oldValue, newValue);
    Handle<String> stringValue;
    if (modify != VALUE_MODIFY_ALLOW)
    {
        return modify;
    }
    TiObject* value = new TiObject;
    value->setValue(newValue);
    modify = (callback_)(propertyNumber_, value, context_);
    if (modify == VALUE_MODIFY_ALLOW)
    {
        forceSetValue(value->getValue());
    }
    value->release();
    return modify;
}
