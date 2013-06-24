/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeImageViewObject.h"

#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/Image>
#include <bb/cascades/ImageView>
#include <bb/cascades/ScalingMethod>

#include "TiBlobObject.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "V8Utils.h"

using namespace bb::cascades;
using namespace titanium;

NativeImageViewObject::NativeImageViewObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_IMAGEVIEW)
{
    imageView_ = NULL;
}

NativeImageViewObject::~NativeImageViewObject()
{
}

NativeImageViewObject* NativeImageViewObject::createImageView(TiObject* tiObject)
{
    return new NativeImageViewObject(tiObject);
}

NATIVE_TYPE NativeImageViewObject::getObjectType() const
{
    return N_TYPE_IMAGEVIEW;
}

int NativeImageViewObject::initialize()
{
    imageView_ = bb::cascades::ImageView::create();
    setControl(imageView_);
    imageView_->setScalingMethod(bb::cascades::ScalingMethod::Fill); //AspectFit);
    return NATIVE_ERROR_OK;
}

int NativeImageViewObject::setImage(TiObject* obj)
{
	Handle<Value> img = obj->getValue();
    if (img->IsString()) {
        QString imagePath = V8ValueToQString(obj->getValue());
        imagePath = getResourcePath(imagePath);
        imageView_->setImage(QUrl(imagePath));
    } else {
        TiObject* obj = TiObject::getTiObjectFromJsObject(img);
        if (obj == NULL) return NATIVE_ERROR_INVALID_ARG;
        if (strcmp(obj->getName(), "Blob") == 0) {
            TiBlobObject* blob = static_cast<TiBlobObject*>(obj);
            Image image(blob->data());
            imageView_->setImage(image);
        }
    }
    QString imagePath = V8ValueToQString(obj->getValue());
    imagePath = getResourcePath(imagePath);
    imageView_->setImage(QUrl(imagePath));
    return NATIVE_ERROR_OK;
}

void NativeImageViewObject::updateLayout(QRectF rect)
{
	NativeControlObject::updateLayout(rect);
	imageView_->setPreferredSize(rect.width(), rect.height());
}

void NativeImageViewObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeControlObject::setupEvents(containerFactory);
    TiEventContainer* eventImageChanged = containerFactory->createEventContainer();
    eventImageChanged->setDataProperty("type", tetCHANGE);
    events_.insert(tetCHANGE, EventPairSmartPtr(eventImageChanged, new ImageViewEventHandler(eventImageChanged)));
    QObject::connect(imageView_, SIGNAL(imageChanged(const bb::cascades::Image)), events_[tetCHANGE]->handler(), SLOT(imageChanged(const bb::cascades::Image)));
}
