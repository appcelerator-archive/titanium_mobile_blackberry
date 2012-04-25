/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeSliderObject.h"
#include "TiEventContainerFactory.h"

NativeSliderObject::NativeSliderObject()
{
    slider_ = NULL;
    eventChange_ = NULL;
}

NativeSliderObject::~NativeSliderObject()
{
    if (eventChange_ != NULL)
    {
        delete eventChange_;
        eventChange_ = NULL;
    }
}

int NativeSliderObject::getObjectType() const
{
    return N_TYPE_SLIDER;
}

int NativeSliderObject::initialize(TiEventContainerFactory* containerFactory)
{
    slider_ = bb::cascades::Slider::create();
    setControl(slider_);
    eventChange_ = containerFactory->createEventContainer();
    eventChangeHandler_ = new TiCascadesEventHandler(eventChange_);
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

int NativeSliderObject::setEventHandler(const char* eventName, TiEvent* event)
{
    if (strcmp(eventName, "change") == 0)
    {
        eventChange_->addListener(event);
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

void NativeSliderObject::completeInitialization()
{
    QObject::connect(slider_, SIGNAL(valueChanging(float)), eventChangeHandler_, SLOT(valueChanging(float)));
}
