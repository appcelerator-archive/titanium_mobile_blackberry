/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeObject.h"
#include "TiObject.h"

#include <assert.h>

// Helpers prototypes
static TiObject* assertPointer(TiObject* ptr);


NativeObject::NativeObject(TiObject* tiObject)
    : tiObject_(assertPointer(tiObject))
    , isInitializationComplete_(false)
{
    tiObject_->addRef();
}

NativeObject::~NativeObject()
{
    assert(tiObject_ != NULL);
    tiObject_->release();
}

int NativeObject::setPropertyValue(std::size_t, TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::getPropertyValue(std::size_t, TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::addChildNativeObject(NativeObject*)
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

int NativeObject::start()
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::stop()
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::openWindowOnTab(NativeObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

void NativeObject::completeInitialization()
{
    isInitializationComplete_ = true;
}

int NativeObject::scrollToIndex(int)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::setActiveTab(NativeObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::setActiveTab(int)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::removeChildNativeObject(NativeObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

bool NativeObject::isInitializationComplete() const
{
    return isInitializationComplete_;
}

int NativeObject::setEventHandler(const char*, TiEvent*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::removeEventHandler(const char*, int)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::setVisibility(bool)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::startLayout()
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::finishLayout()
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::fireEvent(const char*, const TiObject*) const
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

void NativeObject::setupEvents(TiEventContainerFactory*)
{
    // Do nothing in the base class
}


/* ==================== Static Helpers =================== */

static TiObject* assertPointer(TiObject* ptr)
{
    assert(ptr != NULL);
    return ptr;
}
