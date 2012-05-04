/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeProgressBarObject.h"
#include <bb/cascades/DockLayoutProperties>
#include <bb/cascades/VerticalAlignment>
#include <bb/cascades/HorizontalAlignment>

NativeProgressBarObject::NativeProgressBarObject()
{
    progressIndicator_ = NULL;

}

NativeProgressBarObject::~NativeProgressBarObject()
{
}

int NativeProgressBarObject::getObjectType() const
{
    return N_TYPE_PROGRESSBAR;
}

int NativeProgressBarObject::initialize(TiEventContainerFactory* containerFactory)
{
    progressIndicator_ = bb::cascades::ProgressIndicator::create();
    bb::cascades::DockLayoutProperties* properties = bb::cascades::DockLayoutProperties::create();
    properties->setHorizontalAlignment(bb::cascades::HorizontalAlignment::Center);
    properties->setVerticalAlignment(bb::cascades::VerticalAlignment::Top);
    progressIndicator_->setLayoutProperties(properties);
    setControl(progressIndicator_);
    return NATIVE_ERROR_OK;
}

NAHANDLE NativeProgressBarObject::getNativeHandle() const
{
    return progressIndicator_;
}

int NativeProgressBarObject::setMax(TiObject* obj)
{
    float value;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    progressIndicator_->setToValue(value);
    return NATIVE_ERROR_OK;
}

int NativeProgressBarObject::setMin(TiObject* obj)
{
    float value;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    progressIndicator_->setFromValue(value);
    return NATIVE_ERROR_OK;
}

int NativeProgressBarObject::setValue(TiObject* obj)
{
    float value;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    progressIndicator_->setValue(value);
    return NATIVE_ERROR_OK;
}

