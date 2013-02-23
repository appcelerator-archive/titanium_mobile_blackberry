/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeActivityIndicatorObject.h"

#include <bb/cascades/ActivityIndicator>

#include "TiEventContainerFactory.h"

using namespace bb::cascades;

NativeActivityIndicatorObject::NativeActivityIndicatorObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_ACTIVITYINDICATOR)
    , indicator_(NULL)
{
}

NativeActivityIndicatorObject::~NativeActivityIndicatorObject()
{
}

NativeActivityIndicatorObject* NativeActivityIndicatorObject::createActivityIndicator(TiObject* tiObject)
{
    return new NativeActivityIndicatorObject(tiObject);
}

NATIVE_TYPE NativeActivityIndicatorObject::getObjectType() const
{
    return N_TYPE_ACTIVITYINDICATOR;
}

int NativeActivityIndicatorObject::initialize()
{
    indicator_ = ActivityIndicator::create();
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

void NativeActivityIndicatorObject::updateLayout(QRectF rect)
{
    NativeControlObject::updateLayout(rect);

    // Request that the indicator be the same size as the container.
    // If it does not fully fill the container it will center itself.
    indicator_->setPreferredWidth(rect.width());
    indicator_->setPreferredHeight(rect.height());
}

