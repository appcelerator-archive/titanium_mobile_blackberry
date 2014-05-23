/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiGenericFunctionObject.h"

Handle<Value> TiGenericFunctionObject::onInvoke(const Arguments& args) {
    HandleScope scope;
    TiGenericFunctionObject* obj = static_cast<TiGenericFunctionObject*>(
        External::Unwrap(args.Data()));
    Handle<Value> result = obj->callback_(obj->context_, obj, args);
    return scope.Close(result);
}

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

void TiGenericFunctionObject::addGenericFunctionToParent(TiObject* parent, const char* name, void* userContext,
        GENERIC_FUNCTION_CALLBACK callback)
{
    TiGenericFunctionObject* obj = new TiGenericFunctionObject(name);
    obj->context_ = userContext;
    obj->callback_ = callback;
    parent->addMember(obj);

    Local<FunctionTemplate> tmpl = FunctionTemplate::New(onInvoke, External::Wrap(obj));
    obj->setValue(tmpl->GetFunction());

    obj->release();
}

