/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeButtonObject.h"
#include "TiEventContainerFactory.h"
#include <bb/cascades/Button>
#include <bb/cascades/DockLayoutProperties>
#include <bb/cascades/HorizontalAlignment>
#include <bb/cascades/VerticalAlignment>

NativeButtonObject::NativeButtonObject()
{
    button_ = NULL;
}

NativeButtonObject::~NativeButtonObject()
{
}

int NativeButtonObject::getObjectType() const
{
    return N_TYPE_BUTTON;
}

int NativeButtonObject::initialize(TiEventContainerFactory* containerFactory)
{
    button_ = bb::cascades::Button::create();
    bb::cascades::DockLayoutProperties* properties = bb::cascades::DockLayoutProperties::create();
    properties->setHorizontalAlignment(bb::cascades::HorizontalAlignment::Center);
    properties->setVerticalAlignment(bb::cascades::VerticalAlignment::Top);
    button_->setLayoutProperties(properties);
    setControl(button_);
    eventClick_ = containerFactory->createEventContainer();
    eventClick_->setDataProperty("type", "click");
    eventHandler_ = new ButtonEventHandler(eventClick_);
    return NATIVE_ERROR_OK;
}

NAHANDLE NativeButtonObject::getNativeHandle() const
{
    return button_;
}

int NativeButtonObject::setTitle(TiObject* obj)
{
    QString str;

    int error = NativeControlObject::getString(obj, str);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    button_->setText(str);
    return NATIVE_ERROR_OK;
}

int NativeButtonObject::setImage(TiObject* obj)
{
    QString str;
    int error = NativeControlObject::getString(obj, str);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    const bb::cascades::Image image = bb::cascades::Image(QUrl(str));
    button_->setImage(image);
    return NATIVE_ERROR_OK;
}

int NativeButtonObject::setEventHandler(const char* eventName, TiEvent* event)
{
    if (strcmp(eventName, "click") == 0)
    {
        eventClick_->addListener(event);
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

void NativeButtonObject::completeInitialization()
{
    QObject::connect(button_, SIGNAL(clicked()), eventHandler_, SLOT(clicked(void)));
}
