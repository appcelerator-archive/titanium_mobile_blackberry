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

int NativeImageViewObject::initialize(TiEventContainerFactory* containerFactory)
{
    imageView_ = bb::cascades::ImageView::create();
    setControl(imageView_);
    TiEventContainer* eventImageChanged = containerFactory->createEventContainer();
    eventImageChanged->setDataProperty("type", tetCHANGE);
    events_.insert(tetCHANGE, new EventPair(eventImageChanged, new ImageViewEventHandler(eventImageChanged)));
    QObject::connect(imageView_, SIGNAL(imageChanged(const bb::cascades::Image)), events_[tetCHANGE]->handler, SLOT(imageChanged(const bb::cascades::Image)));
    return NATIVE_ERROR_OK;
}

int NativeImageViewObject::setImage(const char* /*image*/)
{
    // FIXME: following call fails to compile on R4
    //imageView_->setImage(bb::cascades::Image(image));
    return NATIVE_ERROR_OK;
}
