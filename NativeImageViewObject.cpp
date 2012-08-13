/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeImageViewObject.h"
#include "TiEventContainerFactory.h"
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/imageview>

NativeImageViewObject::NativeImageViewObject()
{
    imageView_ = NULL;
    left_ = 0;
    top_ = 0;
}

NativeImageViewObject::~NativeImageViewObject()
{
}

NativeImageViewObject* NativeImageViewObject::createImageView()
{
    return new NativeImageViewObject;
}

int NativeImageViewObject::getObjectType() const
{
    return N_TYPE_IMAGEVIEW;
}

int NativeImageViewObject::initialize()
{
    imageView_ = bb::cascades::ImageView::create();
    setControl(imageView_);
    return NATIVE_ERROR_OK;
}

int NativeImageViewObject::setImage(TiObject* obj)
{
    QString image;
    int error = NativeControlObject::getString(obj, image);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    imageView_->setImage(bb::cascades::Image(QUrl(image)));
    return NATIVE_ERROR_OK;
}

void NativeImageViewObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeControlObject::setupEvents(containerFactory);
    TiEventContainer* eventImageChanged = containerFactory->createEventContainer();
    eventImageChanged->setDataProperty("type", tetCHANGE);
    events_.insert(tetCHANGE, EventPairSmartPtr(eventImageChanged, new ImageViewEventHandler(eventImageChanged)));
    QObject::connect(imageView_, SIGNAL(imageChanged(const bb::cascades::Image)), events_[tetCHANGE]->handler, SLOT(imageChanged(const bb::cascades::Image)));
}
