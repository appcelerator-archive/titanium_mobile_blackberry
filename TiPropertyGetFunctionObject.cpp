/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiPropertyGetFunctionObject.h"

#include "TiMessageStrings.h"

TiPropertyGetFunctionObject::TiPropertyGetFunctionObject(const char* name)
    : TiObject(name)
{
    property_ = NULL;
}

TiPropertyGetFunctionObject::~TiPropertyGetFunctionObject()
{
}

void TiPropertyGetFunctionObject::addPropertyGetter(TiObject* parent, TiObject* property, const char* getterName)
{
    TiPropertyGetFunctionObject* object = new TiPropertyGetFunctionObject(getterName);
    object->property_ = property;
    parent->addMember(object);
    object->release();
}

bool TiPropertyGetFunctionObject::isFunction() const
{
    return true;
}

Handle<Value> TiPropertyGetFunctionObject::onFunctionCall(const Arguments& args)
{
    HandleScope handleScope;
    // Getter methods don't have any arguments, e.g. mylabel.getText()
    if (args.Length() != 0)
    {
        // TODO: expand this exception message
        return ThrowException(String::New(Ti::Msg::Too_many_arguments));
    }
    return handleScope.Close(property_->getValue());
}
