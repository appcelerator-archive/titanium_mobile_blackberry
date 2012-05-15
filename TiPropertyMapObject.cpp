/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiPropertyMapObject.h"

TiPropertyMapObject::TiPropertyMapObject(const char* name)
    : TiObject(name)
{
}

TiPropertyMapObject::~TiPropertyMapObject()
{
}

TiPropertyMapObject* TiPropertyMapObject::addProperty(TiObject* parent, const char* name, int propertyNumber,
        int supportedTypes,
        MODIFY_VALUE_CALLBACK cb, void* context)
{
    TiPropertyMapObject* object = new TiPropertyMapObject(name);
    object->propertyNumber_ = propertyNumber;
    object->supportedTypes_ = supportedTypes;
    object->callback_ = cb;
    object->context_ = context;
    parent->addMember(object);
    return object;
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
    if (supportedTypes_ & NATIVE_TYPE_BOOL)
    {
        if (newValue->IsBoolean())
        {
            stringValue = Handle<String>::Cast(newValue);
            String::Utf8Value utf(stringValue);
            return (callback_)(propertyNumber_, *utf, context_);
        }
    }
    if (supportedTypes_ & NATIVE_TYPE_INT)
    {
        if ((newValue->IsInt32()) || (newValue->IsUint32()))
        {
            stringValue = Handle<String>::Cast(newValue);
            String::Utf8Value utf(stringValue);
            return (callback_)(propertyNumber_, *utf, context_);
        }
    }
    if (supportedTypes_ & NATIVE_TYPE_DOUBLE)
    {
        if (newValue->IsNumber())
        {
            stringValue = Handle<String>::Cast(newValue);
            String::Utf8Value utf(stringValue);
            return (callback_)(propertyNumber_, *utf, context_);
        }
    }
    if (supportedTypes_ & NATIVE_TYPE_CSTRING)
    {
        if (newValue->IsString())
        {
            stringValue = Handle<String>::Cast(newValue);
            String::Utf8Value utf(stringValue);
            return (callback_)(propertyNumber_, *utf, context_);
        }
    }
    return VALUE_MODIFY_INVALID_TYPE;
}
