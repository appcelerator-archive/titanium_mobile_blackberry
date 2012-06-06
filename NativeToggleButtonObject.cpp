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

int NativeToggleButtonObject::initialize(TiEventContainerFactory* containerFactory)
{
    toggleButton_ = bb::cascades::ToggleButton::create();
    setControl(toggleButton_);
    eventStateChanged_ = containerFactory->createEventContainer();
    eventHandler_ = new ToggleButtonEventHandler(eventStateChanged_);
    return NATIVE_ERROR_OK;
}

NAHANDLE NativeToggleButtonObject::getNativeHandle() const
{
    return toggleButton_;
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

int NativeToggleButtonObject::setEventHandler(const char* eventName, TiEvent* event)
{
    if (strcmp(eventName, "change") == 0)
    {
        eventStateChanged_->addListener(event);
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

void NativeToggleButtonObject::completeInitialization()
{
    NativeControlObject::completeInitialization();
    //TODO: commented below line, because checkedChanged signal is not implemented for the toggleButton
    //QObject::connect(toggleButton_, SIGNAL(checkedChanged(bool checked)), eventHandler_, SLOT(checkedChanged(bool checked)));
}
