/*
 * NativeSliderObject.cpp
 *
 *  Created on: 2012-04-17
 *      Author: dcampbell
 */

#include "NativeSliderObject.h"

NativeSliderObject::NativeSliderObject()
{
    slider_=NULL;
}

NativeSliderObject::~NativeSliderObject()
{
}

int NativeSliderObject::getObjectType() const
{
    return NO_TYPE_SLIDER;
}

int NativeSliderObject::initialize()
{
    slider_=bb::cascades::Slider::create();
    setControl(slider_);
    return NATIVE_ERROR_OK;
}

NAHANDLE NativeSliderObject::getNativeHandle() const
{
    return slider_;
}

int NativeSliderObject::setMax(float value)
{
    slider_->setToValue(value);
    return NATIVE_ERROR_OK;
}

int NativeSliderObject::setMin(float value)
{
    slider_->setFromValue(value);
    return NATIVE_ERROR_OK;
}

int NativeSliderObject::setValue(float value)
{
    slider_->setValue(value);
    return NATIVE_ERROR_OK;
}
