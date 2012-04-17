/*
 * NativeProgressBarObject.cpp
 *
 *  Created on: 2012-04-20
 *      Author: dcampbell
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
    return NO_TYPE_PROGRESSBAR;
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

