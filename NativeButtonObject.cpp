/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeButtonObject.h"
#include "TiEvent.h"
#include "TiEventContainerFactory.h"
#include <bb/cascades/Button>
#include <bb/cascades/DockLayoutProperties>
#include <bb/cascades/HorizontalAlignment>
#include <bb/cascades/VerticalAlignment>

NativeButtonObject::NativeButtonObject(TiObject* tiObject)
    : NativeControlObject(tiObject)
{
    button_ = NULL;
}

NativeButtonObject::~NativeButtonObject()
{
}

NativeButtonObject* NativeButtonObject::createButton(TiObject* tiObject)
{
    return new NativeButtonObject(tiObject);
}

int NativeButtonObject::getObjectType() const
{
    return N_TYPE_BUTTON;
}

int NativeButtonObject::initialize()
{
    button_ = bb::cascades::Button::create();
    bb::cascades::DockLayoutProperties* properties = bb::cascades::DockLayoutProperties::create();
    properties->setHorizontalAlignment(bb::cascades::HorizontalAlignment::Center);
    properties->setVerticalAlignment(bb::cascades::VerticalAlignment::Top);
    button_->setLayoutProperties(properties);
    setControl(button_);
    return NATIVE_ERROR_OK;
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

void NativeButtonObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeControlObject::setupEvents(containerFactory);
    TiEventContainer* eventClick = containerFactory->createEventContainer();
    eventClick->setDataProperty("type", tetCLICK);
    events_.insert(tetCLICK, EventPairSmartPtr(eventClick, new ButtonEventHandler(eventClick)));
    QObject::connect(button_, SIGNAL(clicked()), events_[tetCLICK]->handler, SLOT(clicked(void)));
}
