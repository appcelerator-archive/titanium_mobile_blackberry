/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeAnnotationObject.h"
#include "TiEvent.h"
#include "TiConstants.h"
#include "TiEventContainerFactory.h"
#include <bb/cascades/ImageButton>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/DockLayout>
#include <bb/cascades/Container>
#include <bb/cascades/ImageView>
#include <bb/cascades/maps/MapView>
#include <bb/cascades/Label>
#include "NativeLoggerObject.h"
#include "NativeMessageStrings.h"
#include <bb/cascades/SystemDefaults>

using namespace bb::cascades;

NativeAnnotationObject::NativeAnnotationObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_ANNOTATION), pinImageSource_("assets/blackberry/map/red_pin.png"),
      showBubble(false)
{
	pin = NULL;
}

NativeAnnotationObject::~NativeAnnotationObject()
{
}

NativeAnnotationObject* NativeAnnotationObject::createAnnotationObject(TiObject* tiObject)
{
    return new NativeAnnotationObject(tiObject);
}

NATIVE_TYPE NativeAnnotationObject::getObjectType() const
{
    return N_TYPE_ANNOTATION;
}

int NativeAnnotationObject::initialize()
{
    pin = new ImageButton();
    pin->setDefaultImageSource(QUrl(pinImageSource_));
    pin->setPressedImage(QUrl(pinImageSource_));
    pin->setFocusPolicy(bb::cascades::FocusPolicy::KeyAndTouch);
    pin->setLayoutProperties(new AbsoluteLayoutProperties());

    // create the bubbles
    bubble = new Container();
    bubble->setLayoutProperties(new AbsoluteLayoutProperties());
	//bubble->setFocusPolicy(bb::cascades::FocusPolicy::KeyAndTouch);

	ImageView* bubbleBackground = new ImageView();
	bubbleBackground->setImageSource(QUrl("assets/blackberry/map/bubble.png"));

    Container* bubbleContent = new Container();
    bubbleContent->setLayout(new bb::cascades::DockLayout());

    label_ = new Label();
    TextStyle* style = new TextStyle(SystemDefaults::TextStyles::smallText());
    style->setColor(Color::White);
    label_->textStyle()->setBase(*style);
    label_->setMultiline(true);
    label_->setHorizontalAlignment(HorizontalAlignment::Center);
    label_->setVerticalAlignment(VerticalAlignment::Center);

    leftView_ = new ImageButton();
    //leftView->setFocusPolicy(bb::cascades::FocusPolicy::KeyAndTouch);
    leftView_->setHorizontalAlignment(HorizontalAlignment::Left);
    leftView_->setVerticalAlignment(VerticalAlignment::Center);

    rightView_ = new ImageButton();
	//rightView_->setFocusPolicy(bb::cascades::FocusPolicy::KeyAndTouch);
	rightView_->setHorizontalAlignment(HorizontalAlignment::Right);
	rightView_->setVerticalAlignment(VerticalAlignment::Center);

	bubbleContent->add(bubbleBackground);
	bubbleContent->add(leftView_);
    bubbleContent->add(label_);
    bubbleContent->add(rightView_);
	bubble->add(bubbleContent);

    return NATIVE_ERROR_OK;
}

int NativeAnnotationObject::setPincolor(TiObject* obj)
{
	int value;
	int error = NativeControlObject::getInteger(obj, &value);
	if (error != NATIVE_ERROR_OK)
	{
		return error;
	}

	 switch (value)
	    {
	    case Ti::Map::ANNOTATION_GREEN:
	    	pinImageSource_ = "assets/blackberry/map/green_pin.png";
	        break;
	    case  Ti::Map::ANNOTATION_RED:
	    	pinImageSource_ = "assets/blackberry/map/red_pin.png";
	        break;
	    case  Ti::Map::ANNOTATION_PURPLE:
	    	pinImageSource_ = "assets/blackberry/map/purple_pin.png";
	        break;
	    default:
	        N_DEBUG(Native::Msg::Unknown_value_received << ": " << value);
	        break;
	    }

	pin->setDefaultImageSource(QUrl(pinImageSource_));
	pin->setPressedImage(QUrl(pinImageSource_));
	return NATIVE_ERROR_OK;
}

int NativeAnnotationObject::setLatitude(TiObject* obj)
{
	int error = NativeControlObject::getFloat(obj, &latitude);

	if (error != NATIVE_ERROR_OK)
	{
		return error;
	}

	return NATIVE_ERROR_OK;
}

int NativeAnnotationObject::setLongitude(TiObject* obj)
{
	int error = NativeControlObject::getFloat(obj, &longitude);

	if (error != NATIVE_ERROR_OK)
	{
		return error;
	}

	return NATIVE_ERROR_OK;
}

int NativeAnnotationObject::setTitle(TiObject* obj)
{
	QString title;
	int error = NativeControlObject::getString(obj, title);

	if (error != NATIVE_ERROR_OK)
	{
		return error;
	}

	label_->setText(title);
	return NATIVE_ERROR_OK;
}

int NativeAnnotationObject::setSubtitle(TiObject* obj)
{
	QString subtitle;
	int error = NativeControlObject::getString(obj, subtitle);

	if (error != NATIVE_ERROR_OK)
	{
		return error;
	}

	label_->setText(label_->text() + "\n" + subtitle);
	return NATIVE_ERROR_OK;
}

int NativeAnnotationObject::setLeftView(TiObject* obj)
{
	QString leftView;
	int error = NativeControlObject::getString(obj, leftView);

	if (error != NATIVE_ERROR_OK)
	{
		return error;
	}

	leftView_->setDefaultImageSource(QUrl("assets/" + leftView));
	leftView_->setPressedImage(QUrl("assets/" + leftView));

	return NATIVE_ERROR_OK;
}

int NativeAnnotationObject::setRightView(TiObject* obj)
{
	QString rightView;
	int error = NativeControlObject::getString(obj, rightView);

	if (error != NATIVE_ERROR_OK)
	{
		return error;
	}

	rightView_->setDefaultImageSource(QUrl("assets/" + rightView));
	rightView_->setPressedImage(QUrl("assets/" + rightView));

	return NATIVE_ERROR_OK;
}


void NativeAnnotationObject::setupEvents(TiEventContainerFactory* containerFactory)
{
	NativeControlObject::setupEvents(containerFactory);

	eventHandler_ = new AnnotationObjectEventHandler(NULL, this);

	TiEventContainer* click = containerFactory->createEventContainer();
	click->setDataProperty("type", tetCLICK);
	events_.insert(tetCLICK, EventPairSmartPtr(click, new AnnotationObjectEventHandler(click, this)));

	QObject::connect(pin, SIGNAL(clicked()), events_[tetCLICK]->handler(), SLOT(clicked()));
	QObject::connect(leftView_, SIGNAL(clicked()), events_[tetCLICK]->handler(), SLOT(viewClicked()));
	QObject::connect(rightView_, SIGNAL(clicked()), events_[tetCLICK]->handler(), SLOT(viewClicked()));
}


AnnotationObjectEventHandler::AnnotationObjectEventHandler(TiEventContainer* eventContainer, NativeAnnotationObject* annotationObject)
{
    eventContainer_ = eventContainer;
    annotationObject_ = annotationObject;
}

AnnotationObjectEventHandler::~AnnotationObjectEventHandler() {
}


void AnnotationObjectEventHandler::clicked()
{
	if (annotationObject_->showBubble == false) {
		annotationObject_->showBubble = true;
	} else {
		annotationObject_->showBubble = false;
	}

	annotationObject_->mapViewObj->updateMap();

	eventContainer_->fireEvent();
}

void AnnotationObjectEventHandler::viewClicked()
{
	eventContainer_->fireEvent();
}

