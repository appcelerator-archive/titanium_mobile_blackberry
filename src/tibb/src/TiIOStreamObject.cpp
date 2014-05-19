/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiIOStreamObject.h"

TiIOStreamObject::TiIOStreamObject()
{
}

TiIOStreamObject::~TiIOStreamObject()
{
}

TiIOStreamObject::TiIOStreamObject(const char* name)
    : TiProxy(name)
{
}

void TiIOStreamObject::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();
}
