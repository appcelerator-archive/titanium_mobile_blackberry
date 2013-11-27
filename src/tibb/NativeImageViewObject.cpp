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

#include "ImageLoader.h"
#include "TiBlobObject.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "V8Utils.h"

#include "TiCore.h"

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
	imageView_->resetImage();
    if (img->IsString()) {
        QString imagePath = V8ValueToQString(obj->getValue());
        if(imagePath.startsWith("http://") || imagePath.startsWith("https://"))
        {
        	ImageLoader::loadImage(imageView_, QUrl(imagePath));
            return NATIVE_ERROR_OK;
        }
        if(!QFile(imagePath).exists())
        {
        	imagePath = getResourcePath(imagePath);
        }
        imageView_->setImage(QUrl(imagePath));
    } else {
        TiObject* obj = TiObject::getTiObjectFromJsObject(img);
        // Ok, this is the old blob object, so get it, use it, and return.
        if (obj != NULL && strcmp(obj->getName(), "Blob") == 0)
        {
			TiBlobObject* blob = static_cast<TiBlobObject*>(obj);
			Image image(blob->data());
			imageView_->setImage(image);
		    return NATIVE_ERROR_OK;
        }
        // This might be the new blob object
        Handle<External> proxyObject = Handle<External>::Cast(img->ToObject()->GetHiddenValue(String::New("proxy")));

        // But return if it's not
        if(proxyObject.IsEmpty())
    		return NATIVE_ERROR_OK;

    	Ti::TiBlob* blob = static_cast<Ti::TiBlob*>(proxyObject->Value());
		Image image(blob->getData());
		imageView_->setImage(image);

    }
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
