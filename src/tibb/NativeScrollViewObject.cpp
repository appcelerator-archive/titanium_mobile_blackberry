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

NativeScrollViewContentObject::NativeScrollViewContentObject(TiObject* tiObject, NativeScrollViewObject* scrollView)
	: NativeControlObject(tiObject, N_TYPE_VIEW)
{
 	setContainer(bb::cascades::Container::create());
 	scrollView_ = scrollView;

 	TiObject height;
	height.setValue(String::New("UI.SIZE"));
 	setHeight(&height);

	TiObject width;
	width.setValue(String::New("UI.SIZE"));
 	setWidth(&width);
}

void NativeScrollViewContentObject::updateLayout(QRectF rect)
{
    NativeControlObject::updateLayout(rect);
    scrollView_->setContentWidthAndHeight(rect.width(), rect.height());
}

NativeScrollViewObject::NativeScrollViewObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_SCROLL_VIEW)
    , contentWidthSet_(false)
    , contentHeightSet_(false)
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
	std::string str = *String::Utf8Value(obj->getValue());

	int err;
	if (str == "vertical" && !contentHeightSet_)
	{
		TiObject height;
		height.setValue(String::New("UI.SIZE"));
		err = contentViewProxy_->setHeight(&height);

		TiObject width;
		width.setValue(String::New("UI.FILL"));
		err = contentViewProxy_->setWidth(&width);
	}

	if (str == "horizontal" && !contentWidthSet_)
	{
		TiObject height;
		height.setValue(String::New("UI.FILL"));
		err = contentViewProxy_->setHeight(&height);

		TiObject width;
		width.setValue(String::New("UI.SIZE"));
		err = contentViewProxy_->setWidth(&width);
	}
	err = contentViewProxy_->setLayout(obj);

	return err;
}
void NativeScrollViewObject::setContentWidthAndHeight(float width, float height)
{
    contentSize_.setHeight(height);
    contentSize_.setWidth(width);

    if(contentSize_.width() > scrollViewSize_.width() && contentSize_.height() <= scrollViewSize_.height())
    {
    	scrollViewProperties_->setScrollMode(bb::cascades::ScrollMode::Horizontal);
    }
    else if(contentSize_.height() > scrollViewSize_.height() && contentSize_.width() <= scrollViewSize_.width())
    {
       	scrollViewProperties_->setScrollMode(bb::cascades::ScrollMode::Vertical);
    }
    else if(contentSize_.width() <= scrollViewSize_.width() && contentSize_.height() <= scrollViewSize_.height())
    {
    	scrollViewProperties_->setScrollMode(bb::cascades::ScrollMode::None);
    }
    else
    {
      	scrollViewProperties_->setScrollMode(bb::cascades::ScrollMode::Both);
   	}
}

int NativeScrollViewObject::initialize()
{

	contentViewProxy_ = new NativeScrollViewContentObject(tiObject_, this);
	contentView_ = (bb::cascades::Container*)contentViewProxy_->getNativeHandle();


	scrollView_ = bb::cascades::ScrollView::create();
	nativeContentView_ = bb::cascades::Container::create();

	setControl(scrollView_);

	addChildImpl(contentViewProxy_);

	nativeContentView_->add(contentView_);
    scrollView_->setContent(nativeContentView_);

    scrollViewProperties_ = scrollView_->scrollViewProperties();

    ScrollViewEventHandler *eventHandler_ = new ScrollViewEventHandler(this);

    bb::cascades::LayoutUpdateHandler::create(nativeContentView_).onLayoutFrameChanged(eventHandler_, SLOT(onContainerLayoutChange(QRectF)));

    contentSize_ = QSize(0,0);
    scrollViewSize_ = QSize(0,0);
    return NATIVE_ERROR_OK;
}
/*
	Not implemented yet
int NariveScrollViewObject::setDisableBounce(TiObject* obj)
{
    bool bounces;
    getBoolean(obj, &bounces);
    if(bounces) {
    	scrollViewProperties_->setOverScrollEffectMode(bb::cascades::OverScrollEffectMode::None);
    }
    return NATIVE_ERROR_OK;
}
*/

int NativeScrollViewObject::setContentWidth(TiObject* obj)
{
	string str = *String::Utf8Value(obj->getValue());

	if (str == "UI.SIZE") {
		return NATIVE_ERROR_OK;
	}

	contentWidthSet_ = true;
    return contentViewProxy_->setWidth(obj);
}

int NativeScrollViewObject::setContentHeight(TiObject* obj)
{
	string str = *String::Utf8Value(obj->getValue());

	if (str == "UI.SIZE") {
		return NATIVE_ERROR_OK;
	}

	contentHeightSet_ = true;
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
    scrollViewSize_.setHeight(h);
    scrollViewSize_.setWidth(w);
}

int NativeScrollViewObject::setBackgroundColor(TiObject* obj)
{
	NativeControlObject::setBackgroundColor(obj);
    return contentViewProxy_->setBackgroundColor(obj);
}

int NativeScrollViewObject::setHeight(TiObject *obj)
{
	std::string str = *String::Utf8Value(obj->getValue());
	if(str == "UI.FILL") return NATIVE_ERROR_OK;
	return NativeControlObject::setHeight(obj);
}
int NativeScrollViewObject::setWidth(TiObject *obj)
{
	std::string str = *String::Utf8Value(obj->getValue());
	if(str == "UI.FILL") return NATIVE_ERROR_OK;
	return NativeControlObject::setWidth(obj);
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

