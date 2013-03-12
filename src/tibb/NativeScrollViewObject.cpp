/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeScrollViewObject.h"
#include "TiEvent.h"
#include "TiEventContainerFactory.h"
#include "TiUIBase.h"
#include <bb/cascades/ScrollView>
#include <bb/cascades/ScrollViewProperties>
#include <bb/cascades/ScrollMode>
#include <bb/cascades/Container>
#include <bb/cascades/Button>
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/LayoutUpdateHandler>

NativeScrollViewContentObject::NativeScrollViewContentObject(TiObject* tiObject)
	: NativeControlObject(tiObject, N_TYPE_VIEW)
{
 	setContainer(bb::cascades::Container::create());
}

NativeScrollViewObject::NativeScrollViewObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_SCROLL_VIEW)
{
    scrollView_ = NULL;
}

NativeScrollViewObject::~NativeScrollViewObject()
{
}

NativeScrollViewObject* NativeScrollViewObject::createScrollView(TiObject* tiObject)
{
   return new NativeScrollViewObject(tiObject);
}

NATIVE_TYPE NativeScrollViewObject::getObjectType() const
{
    return N_TYPE_SCROLL_VIEW;
}

int NativeScrollViewObject::setLayout(TiObject *obj)
{
	int err = contentViewProxy_->setLayout(obj);
	return err;
}

int NativeScrollViewObject::initialize()
{

	contentViewProxy_ = new NativeScrollViewContentObject(tiObject_);
	contentView_ = (bb::cascades::Container*)contentViewProxy_->getNativeHandle();


	scrollView_ = bb::cascades::ScrollView::create();
	nativeContentView_ = bb::cascades::Container::create();

	setControl(scrollView_);

	addChildImpl(contentViewProxy_);

	nativeContentView_->add(contentView_);
    scrollView_->setContent(nativeContentView_);

    scrollViewProperties_ = scrollView_->scrollViewProperties();
	scrollViewProperties_->setScrollMode(bb::cascades::ScrollMode::Both);
	scrollViewProperties_->setOverScrollEffectMode(bb::cascades::OverScrollEffectMode::None);

    ScrollViewEventHandler *eventHandler_ = new ScrollViewEventHandler(this);

    bb::cascades::LayoutUpdateHandler::create(nativeContentView_).onLayoutFrameChanged(eventHandler_, SLOT(onContainerLayoutChange(QRectF)));

    contentSize_ = QSize(0,0);

    return NATIVE_ERROR_OK;
}


int NativeScrollViewObject::setContentWidth(TiObject* obj)
{
    return contentViewProxy_->setWidth(obj);
}

int NativeScrollViewObject::setContentHeight(TiObject* obj)
{
    return contentViewProxy_->setHeight(obj);
}

void NativeScrollViewObject::onContentViewSizeChange(QRectF rect)
{
	//contentView_->setBackground(bb::cascades::Color::DarkRed);
}

void NativeScrollViewObject::updateLayout(QRectF rect)
{
    NativeControlObject::updateLayout(rect);
    float h = rect.height();
    float w = rect.width();

    scrollView_->setPreferredHeight(h);
    scrollView_->setPreferredWidth(w);
    scrollView_->setMinWidth(w);
    scrollView_->setMaxWidth(w);
    scrollView_->setMinHeight(h);
    scrollView_->setMaxHeight(h);

}
/*
NAHANDLE NativeScrollViewObject::getNativeHandle() const
{
    return scrollView_;
}
 */


int NativeScrollViewObject::setBackgroundColor(TiObject* obj)
{
	NativeControlObject::setBackgroundColor(obj);
    return contentViewProxy_->setBackgroundColor(obj);
}


int NativeScrollViewObject::addChildNativeObject(NativeObject* obj)
{
	contentViewProxy_->addChildNativeObject(obj);

	return NATIVE_ERROR_OK;
}

void NativeScrollViewObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeControlObject::setupEvents(containerFactory);
    /*
    TiEventContainer* eventClick = containerFactory->createEventContainer();
    eventClick->setDataProperty("type", tetCLICK);
    events_.insert(tetCLICK, EventPairSmartPtr(eventClick, new ButtonEventHandler(eventClick)));
    QObject::connect(button_, SIGNAL(clicked()), events_[tetCLICK]->handler(), SLOT(clicked(void)));
     */
}
