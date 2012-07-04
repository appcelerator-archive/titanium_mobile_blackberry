/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiAPIObject.h"
#include "TiGenericFunctionObject.h"
#include "TiLogger.h"
#include "TiMessageStrings.h"

TiAPIObject::TiAPIObject()
    : TiObject("API")
{
}

TiAPIObject::~TiAPIObject()
{
}

void TiAPIObject::addObjectToParent(TiObject* parent)
{
    TiAPIObject* obj = new TiAPIObject;
    parent->addMember(obj);
}

void TiAPIObject::onCreateStaticMembers()
{
    TiGenericFunctionObject::addGenericFunctionToParent(this, "debug", this, _debug);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "info", this, _info);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "warn", this, _warn);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "error", this, _error);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "log", this, _log);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "timestamp", this, _timestamp);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "trace", this, _trace);
}

Handle<Value> TiAPIObject::_debug(void* userContext, TiObject* caller, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    // Log message with DEBUG severity-level
    Local<Value> taggedMessage = String::Concat(String::New("[DEBUG]:"), args[0]->ToString());
    TiLogger::getInstance().log(*String::Utf8Value(taggedMessage));
    return Undefined();
}

Handle<Value> TiAPIObject::_info(void* userContext, TiObject* caller, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    // Log message with INFO severity-level
    Local<Value> taggedMessage = String::Concat(String::New("[INFO]:"), args[0]->ToString());
    TiLogger::getInstance().log(*String::Utf8Value(taggedMessage));
    return Undefined();
}

Handle<Value> TiAPIObject::_warn(void* userContext, TiObject* caller, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    // Log message with WARNING severity-level
    Local<Value> taggedMessage = String::Concat(String::New("[WARNING]:"), args[0]->ToString());
    TiLogger::getInstance().log(*String::Utf8Value(taggedMessage));
    return Undefined();
}

Handle<Value> TiAPIObject::_error(void* userContext, TiObject* caller, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    // Log message with ERROR severity-level
    Local<Value> taggedMessage = String::Concat(String::New("[ERROR]:"), args[0]->ToString());
    TiLogger::getInstance().log(*String::Utf8Value(taggedMessage));
    return Undefined();
}

Handle<Value> TiAPIObject::_log(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: Implement this later
    return Undefined();
}

Handle<Value> TiAPIObject::_timestamp(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: Implement this later
    return Undefined();
}

Handle<Value> TiAPIObject::_trace(void* userContext, TiObject* caller, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    // Log message with ERROR severity-level
    Local<Value> taggedMessage = String::Concat(String::New("[TRACE]:"), args[0]->ToString());
    TiLogger::getInstance().log(*String::Utf8Value(taggedMessage));
    return Undefined();
}
