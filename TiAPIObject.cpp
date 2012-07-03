/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiAPIObject.h"
#include "TiGenericFunctionObject.h"
#include "TiLogger.h"

typedef enum TiSeverityLevel_
{
    Ti_DEBUG,
    Ti_INFO,
    Ti_ERROR,
    Ti_WARN,
    Ti_TRACE
} TiSeverityLevel;

// Helper method
static void toSystemLog(Local<Value> message, const TiSeverityLevel sLevel);

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
        return Undefined();
    }

    // Log message with DEBUG severity-level
    toSystemLog(args[0], Ti_DEBUG);
    return Undefined();
}

Handle<Value> TiAPIObject::_info(void* userContext, TiObject* caller, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return Undefined();
    }

    // Log message with INFO severity-level
    toSystemLog(args[0], Ti_INFO);
    return Undefined();
}

Handle<Value> TiAPIObject::_warn(void* userContext, TiObject* caller, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return Undefined();
    }

    // Log message with WARNING severity-level
    toSystemLog(args[0], Ti_WARN);
    return Undefined();
}

Handle<Value> TiAPIObject::_error(void* userContext, TiObject* caller, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return Undefined();
    }

    // Log message with ERROR severity-level
    toSystemLog(args[0], Ti_ERROR);
    return Undefined();
}

Handle<Value> TiAPIObject::_log(void* userContext, TiObject* caller, const Arguments& args)
{
    if (args.Length() < 2)
    {
        return Undefined();
    }

    Local<Value> sLevel = args[0];
    if (!sLevel->IsString())
    {
        sLevel = sLevel->ToString();
    }

    // Check the log level
    String::Utf8Value v8UtfLevel(sLevel);
    const char* cLevel = *v8UtfLevel;
    Local<Value> message = args[1];
    if (strcmp(cLevel, "debug") == 0)
    {
        toSystemLog(message, Ti_DEBUG);
    }
    else if (strcmp(cLevel, "error") == 0)
    {
        toSystemLog(message, Ti_ERROR);
    }
    else if (strcmp(cLevel, "info") == 0)
    {
        toSystemLog(message, Ti_INFO);
    }
    else if (strcmp(cLevel, "warn") == 0)
    {
        toSystemLog(message, Ti_WARN);
    }
    else if (strcmp(cLevel, "trace") == 0)
    {
        toSystemLog(message, Ti_TRACE);
    }
    else
    {
        toSystemLog(message, Ti_INFO);
    }

    return Undefined();
}

Handle<Value> TiAPIObject::_timestamp(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: Implement this later
    return Undefined();
}

Handle<Value> TiAPIObject::_trace(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: Implement this later
    return Undefined();
}

static void toSystemLog(Local<Value> message, const TiSeverityLevel sLevel)
{
    if (!message->IsString())
    {
        message = message->ToString();
    }

    switch (sLevel)
    {
    case Ti_DEBUG:
        TI_DEBUG(*String::Utf8Value(message));
        break;
    case Ti_INFO:
        TI_INFO(*String::Utf8Value(message));
        break;
    case Ti_WARN:
        TI_WARNING(*String::Utf8Value(message));
        break;
    case Ti_ERROR:
        TI_ERROR(*String::Utf8Value(message));
        break;
    case Ti_TRACE:
        // TODO: Implement this
        break;
    default:
        TI_INFO(*String::Utf8Value(message));
        break;
    }
}
