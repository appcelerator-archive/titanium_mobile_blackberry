/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeButtonObject.h"

#include <bb/cascades/Button>

#include "TiEvent.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "V8Utils.h"

using namespace titanium;

NativeButtonObject::NativeButtonObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_BUTTON)
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

NATIVE_TYPE NativeButtonObject::getObjectType() const
{
    return N_TYPE_BUTTON;
}

int NativeButtonObject::initialize()
{
    button_ = bb::cascades::Button::create();
    setControl(button_);
    return NATIVE_ERROR_OK;
}

int NativeButtonObject::setTitle(TiObject* obj)
{
    QString title = V8ValueToQString(obj->getValue());
    button_->setText(title);
    return NATIVE_ERROR_OK;
}

int NativeButtonObject::setImage(TiObject* obj)
{
    QString path = getResourcePath(V8ValueToQString(obj->getValue()));
    const bb::cascades::Image image = bb::cascades::Image(QUrl(path));
    button_->setImage(image);
    return NATIVE_ERROR_OK;
}

void NativeButtonObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeControlObject::setupEvents(containerFactory);
    TiEventContainer* eventClick = containerFactory->createEventContainer();
    eventClick->setDataProperty("type", tetCLICK);
    events_.insert(tetCLICK, EventPairSmartPtr(eventClick, new ButtonEventHandler(eventClick)));
    QObject::connect(button_, SIGNAL(clicked()), events_[tetCLICK]->handler(), SLOT(clicked(void)));
}

