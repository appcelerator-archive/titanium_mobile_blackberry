/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeObject.h"
#include <stdio.h>

NativeObject::NativeObject()
{
    refCount_ = 1;
    isInitializationComplete_ = 0;
}

NativeObject::~NativeObject()
{
}

void NativeObject::addRef()
{
    refCount_++;
}

void NativeObject::release()
{
    refCount_--;
    if (refCount_ == 0)
    {
        delete this;
    }
}

int NativeObject::setPropertyValue(int propertyNumber, const char* value)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::addChildNativeObject(NativeObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::initialize()
{
    return NATIVE_ERROR_OK;
}

NAHANDLE NativeObject::getNativeHandle() const
{
    return NULL;
}

int NativeObject::open()
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

void NativeObject::completeInitialization()
{
    isInitializationComplete_ = 1;
}
int NativeObject::isInitializationComplete() const
{
    return isInitializationComplete_;
}
