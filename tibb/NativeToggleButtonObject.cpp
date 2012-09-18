/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeToggleButtonObject.h"

#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include <bb/cascades/ToggleButton>

NativeToggleButtonObject::NativeToggleButtonObject(TiObject* tiObject)
    : NativeControlObject(tiObject)
{
    toggleButton_ = NULL;
}

NativeToggleButtonObject::~NativeToggleButtonObject()
{
}

NativeToggleButtonObject* NativeToggleButtonObject::createToggleButton(TiObject* tiObject)
{
    return new NativeToggleButtonObject(tiObject);
}

int NativeToggleButtonObject::getObjectType() const
{
    return N_TYPE_TOGGLEBUTTON;
}

int NativeToggleButtonObject::initialize()
{
    toggleButton_ = bb::cascades::ToggleButton::create();
    setControl(toggleButton_);
    return NATIVE_ERROR_OK;
}

int NativeToggleButtonObject::setValue(TiObject* value)
{
    bool checked;
    int error = NativeControlObject::getBoolean(value, &checked);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    toggleButton_->setChecked(checked);
    return NATIVE_ERROR_OK;
}

void NativeToggleButtonObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeControlObject::setupEvents(containerFactory);
    TiEventContainer* eventStateChanged = containerFactory->createEventContainer();
    events_.insert(tetCHANGE, EventPairSmartPtr(eventStateChanged,
                   new ToggleButtonEventHandler(eventStateChanged, this)));
    QObject::connect(toggleButton_, SIGNAL(checkedChanged(bool)),
                     events_[tetCHANGE]->handler, SLOT(checkedChanged(bool)));
}

void NativeToggleButtonObject::updateValue(bool value)
{
    tiObject_->forceSetProp("value", Local<Boolean>::New(Boolean::New(value)));
}
