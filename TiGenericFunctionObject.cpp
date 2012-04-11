/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiGenericFunctionObject.h"

TiGenericFunctionObject::TiGenericFunctionObject()
{
    context_ = NULL;
    callback_ = NULL;
}

TiGenericFunctionObject::TiGenericFunctionObject(const char* name)
        : TiObject(name)
{
    context_ = NULL;
    callback_ = NULL;
}

TiGenericFunctionObject::~TiGenericFunctionObject()
{
}

bool TiGenericFunctionObject::isFunction() const
{
    return true;
}

Handle<Value> TiGenericFunctionObject::onFunctionCall(const Arguments& args)
{
    HandleScope handleScope;
    Handle < Value > result = callback_(context_, this, args);
    return handleScope.Close(result);
}

void TiGenericFunctionObject::addGenericFunctionToParent(TiObject* parent, const char* name, void* userContext,
                                                         GENERIC_FUNCTION_CALLBACK callback)
{
    TiGenericFunctionObject* obj = new TiGenericFunctionObject(name);
    obj->context_ = userContext;
    obj->callback_ = callback;
    parent->addMember(obj);
    obj->release();
}
