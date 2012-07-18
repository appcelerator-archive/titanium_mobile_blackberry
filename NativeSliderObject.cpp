/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeSliderObject.h"
#include "TiEventContainerFactory.h"
#include "bb/cascades/slider"

NativeSliderObject::NativeSliderObject()
{
    slider_ = NULL;
}

NativeSliderObject::~NativeSliderObject()
{
}

int NativeSliderObject::getObjectType() const
{
    return N_TYPE_SLIDER;
}

int NativeSliderObject::initialize(TiEventContainerFactory* containerFactory)
{
    slider_ = bb::cascades::Slider::create();
    setControl(slider_);
    TiEventContainer* eventChange = containerFactory->createEventContainer();
    events_.insert(tetCHANGE, new EventPair(eventChange, new SliderEventHandler(eventChange)));
    QObject::connect(slider_, SIGNAL(valueChanging(float)), events_[tetCHANGE]->handler, SLOT(valueChanging(float)));
    return NATIVE_ERROR_OK;
}

int NativeSliderObject::setMax(TiObject* obj)
{
    float value;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    slider_->setToValue(value);
    return NATIVE_ERROR_OK;
}

int NativeSliderObject::setMin(TiObject* obj)
{
    float value;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    slider_->setFromValue(value);
    return NATIVE_ERROR_OK;
}

int NativeSliderObject::setValue(TiObject* obj)
{
    float value;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    slider_->setValue(value);
    return NATIVE_ERROR_OK;
}
