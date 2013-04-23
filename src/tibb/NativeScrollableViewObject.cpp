/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#include "NativeScrollableViewObject.h"
#include "TiEvent.h"
#include "TiEventContainerFactory.h"
#include "TiScrollableView/TiScrollableView.h"

NativeScrollableViewObject::NativeScrollableViewObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_SCROLLABLE_VIEW)
{
    scrollableView_ = NULL;
}

NativeScrollableViewObject::~NativeScrollableViewObject()
{
}

NativeScrollableViewObject* NativeScrollableViewObject::createScrollableView(TiObject* tiObject)
{
    return new NativeScrollableViewObject(tiObject);
}

NATIVE_TYPE NativeScrollableViewObject::getObjectType() const
{
    return N_TYPE_SCROLLABLE_VIEW;
}

int NativeScrollableViewObject::initialize()
{
	scrollableView_ = new TiScrollableView();
	setControl(scrollableView_);
    return NATIVE_ERROR_OK;
}

void NativeScrollableViewObject::updateLayout(QRectF rect)
{
    NativeControlObject::updateLayout(rect);
    float h = rect.height();
    float w = rect.width();
    scrollableView_->setPreferredSize(w, h);
}


int NativeScrollableViewObject::addChildNativeObject(NativeObject* obj)
{
	scrollableView_->addView((bb::cascades::Container*)obj->getNativeHandle());

	return NATIVE_ERROR_OK;
}


/*
int NativeScrollableViewObject::setImage(TiObject* obj)
{
    QString str;
    int error = NativeControlObject::getString(obj, str);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    str = getResourcePath(str);
    const bb::cascades::Image image = bb::cascades::Image(QUrl(str));
    button_->setImage(image);
    return NATIVE_ERROR_OK;
}
*/
void NativeScrollableViewObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeControlObject::setupEvents(containerFactory);


    /*
    TiEventContainer* eventClick = containerFactory->createEventContainer();
    eventClick->setDataProperty("type", tetCLICK);
    events_.insert(tetCLICK, EventPairSmartPtr(eventClick, new ScrollableViewEventHandler(eventClick)));
    QObject::connect(button_, SIGNAL(clicked()), events_[tetCLICK]->handler(), SLOT(clicked(void)));
    */
}


