/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiPropertySetFunctionObject.h"

TiPropertySetFunctionObject::TiPropertySetFunctionObject(const char* name)
        : TiObject(name)
{
}

TiPropertySetFunctionObject::~TiPropertySetFunctionObject()
{
}

void TiPropertySetFunctionObject::addPropertySetter(TiObject* parent, TiObject* property, const char* setterName)
{
    TiPropertySetFunctionObject* object = new TiPropertySetFunctionObject(setterName);
    object->property_ = property;
    parent->addMember(object);
    object->release();
}

bool TiPropertySetFunctionObject::isFunction() const
{
    return true;
}

Handle<Value> TiPropertySetFunctionObject::onFunctionCall(const Arguments& args)
{
    HandleScope handle_scope;
    if (args.Length() < 1)
    {
        // TODO: expand this exception message
        return ThrowException(String::New("missing argument"));
    }
    property_->setValue(args[0]);
    return Undefined();
}
