/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeToggleButtonObject.h"
#include "TiEventContainerFactory.h"
#include <bb/cascades/ToggleButton>

NativeToggleButtonObject::NativeToggleButtonObject()
{
    toggleButton_ = NULL;
}

NativeToggleButtonObject::~NativeToggleButtonObject()
{
}

NativeToggleButtonObject* NativeToggleButtonObject::createToggleButton()
{
    return new NativeToggleButtonObject();
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
    events_.insert(tetCHANGE, EventPairSmartPtr(eventStateChanged, new ToggleButtonEventHandler(eventStateChanged)));
    //TODO: commented below line, because checkedChanged signal is not implemented for the toggleButton
    //QObject::connect(toggleButton_, SIGNAL(checkedChanged(bool checked)), events_[tetCHANGE]->handler, SLOT(checkedChanged(bool checked)));
}
