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
#include <v8.h>

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

void NativeScrollableViewObject::moveNext() {
	if(scrollableView_->currentIndex == scrollableView_->indexCount - 1) return;
	scrollableView_->scrollToIndex(scrollableView_->currentIndex + 1, true);
}
void NativeScrollableViewObject::movePrevious() {
	if(scrollableView_->currentIndex == 0) return;
	scrollableView_->scrollToIndex(scrollableView_->currentIndex - 1, true);
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
	addChildImpl(obj);
	scrollableView_->addView((bb::cascades::Container*)obj->getNativeHandle());
	allViews_.append(obj);
	return NATIVE_ERROR_OK;
}

int NativeScrollableViewObject::setViews(TiObject* obj)
{
    QVector<NativeObject*> views_;
    int error = NativeControlObject::getObjectArray(obj, views_);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }

    if (views_.size() > 0) {
        for (int i = 0; i < views_.size(); i++) {
            NativeObject* view = (NativeObject*)views_[i];
            addChildNativeObject(view);
        }
    }
    return NATIVE_ERROR_OK;
}

void NativeScrollableViewObject::scrollToView(NativeObject *view, bool animated) {
/*
	for(int i = 0, len = allViews_.size(); i < len; ++i) {
		NativeObject* a = allViews_.at(i);
		NativeObject& myView = *view;
		NativeObject& myA = *a;
		if(myView == myA) {
			scrollToIndex(i, animated);
			return;
		}
	}
	*/
}

void NativeScrollableViewObject::scrollToIndex(int index, bool animated) {
    scrollableView_->scrollToIndex(index, animated);
}

int NativeScrollableViewObject::setCurrentPage(TiObject* obj)
{
	int index;
    int error = NativeControlObject::getInteger(obj, &index);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    scrollableView_->startAt(index);
    scrollToIndex(index, false);

    return NATIVE_ERROR_OK;
}

int NativeScrollableViewObject::setDisableBounce(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeScrollableViewObject::setOverScrollMode(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeScrollableViewObject::setOverlayEnabled(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeScrollableViewObject::setPagingControlAlpha(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeScrollableViewObject::setPagingControlColor(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeScrollableViewObject::setPagingControlHeight(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeScrollableViewObject::setPagingControlOnTop(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeScrollableViewObject::setPagingControlTimeout(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeScrollableViewObject::setScrollingEnabled(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeScrollableViewObject::setShowPagingControl(TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
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


