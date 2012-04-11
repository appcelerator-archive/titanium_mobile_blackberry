/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiAPIObject.h"
#include "TiGenericFunctionObject.h"

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
    TiGenericFunctionObject::addGenericFunctionToParent(this, "debug", this, debug_);
}

Handle<Value> TiAPIObject::debug_(void* userContext, TiObject* caller, const Arguments& args)
{
    int i;
    for (i = 0; i < args.Length(); i++)
    {
        if (args[i]->IsArray())
        {
            // TODO: complete
        }
        else
        {
            Local < String > log = args[i]->ToString();
            String::Utf8Value logString(log);
            printf("%s", (const char*) (*logString));
        }
    }
    printf("\n");
    return Undefined();
}
