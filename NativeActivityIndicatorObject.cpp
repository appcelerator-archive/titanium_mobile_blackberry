/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeActivityIndicatorObject.h"
#include "TiEventContainerFactory.h"
#include <bb/cascades/ActivityIndicator>

NativeActivityIndicatorObject::NativeActivityIndicatorObject()
{
    indicator_ = NULL;
}

NativeActivityIndicatorObject::~NativeActivityIndicatorObject()
{
}

NativeActivityIndicatorObject* NativeActivityIndicatorObject::createActivityIndicator()
{
    return new NativeActivityIndicatorObject();
}

int NativeActivityIndicatorObject::getObjectType() const
{
    return N_TYPE_ACTIVITYINDICATOR;
}

int NativeActivityIndicatorObject::initialize(TiEventContainerFactory* containerFactory)
{
    indicator_ = bb::cascades::ActivityIndicator::create();
    setControl(indicator_);
    return NATIVE_ERROR_OK;
}

int NativeActivityIndicatorObject::start()
{
    indicator_->start();
    return NATIVE_ERROR_OK;
}

int NativeActivityIndicatorObject::stop()
{
    indicator_->stop();
    return NATIVE_ERROR_OK;
}

NAHANDLE NativeActivityIndicatorObject::getNativeHandle() const
{
    return indicator_;
}
