/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeImageButtonObject.h"

#include <bb/cascades/ImageButton>

#include "TiEvent.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "V8Utils.h"
#include "TiCore.h"

using namespace titanium;

NativeImageButtonObject::NativeImageButtonObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_IMAGE_BUTTON)
{
    button_ = NULL;
}

NativeImageButtonObject::~NativeImageButtonObject()
{
}

NativeImageButtonObject* NativeImageButtonObject::createButton(TiObject* tiObject)
{
    return new NativeImageButtonObject(tiObject);
}

NATIVE_TYPE NativeImageButtonObject::getObjectType() const
{
    return N_TYPE_IMAGE_BUTTON;
}

int NativeImageButtonObject::initialize()
{
    button_ = bb::cascades::ImageButton::create();
    setControl(button_);
    return NATIVE_ERROR_OK;
}

void NativeImageButtonObject::updateLayout(QRectF rect)
{
	NativeControlObject::updateLayout(rect);
	button_->setPreferredSize(rect.width(), rect.height());
}

int NativeImageButtonObject::setTitle(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}


int NativeImageButtonObject::setEnabled(TiObject* obj)
{
	NativeControlObject::setEnabled(obj);
    bool enabled;
    int error = getBoolean(obj, &enabled);

    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
	button_->setEnabled(enabled);
	return NATIVE_ERROR_OK;
}

int NativeImageButtonObject::setImageDisabled(TiObject* obj)
{
    QString path = Ti::TiHelper::getAssetPath(V8ValueToQString(obj->getValue()));
    const bb::cascades::Image image = bb::cascades::Image(QUrl(path));
    button_->setDisabledImage(image);
    return NATIVE_ERROR_OK;
}

int NativeImageButtonObject::setImagePressed(TiObject* obj)
{
    QString path = Ti::TiHelper::getAssetPath(V8ValueToQString(obj->getValue()));
    const bb::cascades::Image image = bb::cascades::Image(QUrl(path));
    button_->setPressedImage(image);
    return NATIVE_ERROR_OK;
}

int NativeImageButtonObject::setImage(TiObject* obj)
{
    QString path = Ti::TiHelper::getAssetPath(V8ValueToQString(obj->getValue()));
    const bb::cascades::Image image = bb::cascades::Image(QUrl(path));
    button_->setDefaultImage(image);
    return NATIVE_ERROR_OK;
}

void NativeImageButtonObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeControlObject::setupEvents(containerFactory);
    TiEventContainer* eventClick = containerFactory->createEventContainer();
    eventClick->setDataProperty("type", tetCLICK);
    events_.insert(tetCLICK, EventPairSmartPtr(eventClick, new ImageButtonEventHandler(eventClick)));
    QObject::connect(button_, SIGNAL(clicked()), events_[tetCLICK]->handler(), SLOT(clicked(void)));
}

