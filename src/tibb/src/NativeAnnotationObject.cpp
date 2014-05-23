/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeAnnotationObject.h"

#include <bb/cascades/ImageButton>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/DockLayout>
#include <bb/cascades/StackLayout>
#include <bb/cascades/Container>
#include <bb/cascades/ImageView>
#include <bb/cascades/maps/MapView>
#include <bb/cascades/Label>
#include "NativeMessageStrings.h"
#include <bb/cascades/SystemDefaults>
#include <bb/cascades/Image>
#include "TiConstants.h"
#include "TiEvent.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "V8Utils.h"
#include <TiCore.h>

using namespace bb::cascades;
using namespace titanium;

NativeAnnotationObject::NativeAnnotationObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_ANNOTATION), pinImageSource_(Ti::TiHelper::getAssetPath("map/red_pin.png")),
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
    pin->setDefaultImage(bb::cascades::Image(pinImageSource_));
    pin->setPressedImage(bb::cascades::Image(pinImageSource_));
    pin->setFocusPolicy(bb::cascades::FocusPolicy::KeyAndTouch);
    pin->setLayoutProperties(new AbsoluteLayoutProperties());
    pin->setMinHeight(30.f);
    pin->setMinWidth(30.f);
    // create the bubbles
    bubble = new Container();
    bubble->setLayoutProperties(new AbsoluteLayoutProperties());

	ImageView* bubbleBackground = new ImageView();
	QUrl u = QUrl::fromLocalFile(Ti::TiHelper::getAssetPath("map/bubble.png"));
	bubbleBackground->setImageSource(u);

	bubbleContent = new Container();
	bubbleContent->setLayoutProperties(new AbsoluteLayoutProperties());

    Container* innerBubbleContent = new Container();
    innerBubbleContent->setPreferredWidth(430);
    innerBubbleContent->setPreferredHeight(130);
    innerBubbleContent->setLayout(new bb::cascades::DockLayout());
    //innerBubbleContent->setRightPadding(10);
    //innerBubbleContent->setLeftPadding(10);

    label_ = new Label();
    TextStyle* style = new TextStyle(SystemDefaults::TextStyles::smallText());
    style->setColor(Color::White);
    label_->textStyle()->setBase(*style);
    label_->setMultiline(true);
    label_->setHorizontalAlignment(HorizontalAlignment::Center);
    label_->setVerticalAlignment(VerticalAlignment::Center);

    leftView_ = new ImageButton();
    leftView_->setHorizontalAlignment(HorizontalAlignment::Left);
    leftView_->setVerticalAlignment(VerticalAlignment::Center);

    rightView_ = new ImageButton();
	rightView_->setHorizontalAlignment(HorizontalAlignment::Right);
	rightView_->setVerticalAlignment(VerticalAlignment::Center);

	bubble->add(bubbleBackground);
	innerBubbleContent->add(leftView_);
	innerBubbleContent->add(label_);
	innerBubbleContent->add(rightView_);

	bubbleContent->add(innerBubbleContent);

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
	    	pinImageSource_ = Ti::TiHelper::getAssetPath("map/green_pin.png");
	        break;
	    case  Ti::Map::ANNOTATION_RED:
	    	pinImageSource_ = Ti::TiHelper::getAssetPath("map/red_pin.png");
	        break;
	    case  Ti::Map::ANNOTATION_PURPLE:
	    	pinImageSource_ = Ti::TiHelper::getAssetPath("map/purple_pin.png");
	        break;
	    default:
	    	Ti::TiHelper::LogInternal( QString(Native::Msg::Unknown_value_received) + ": " + QString::number(value));
	        break;
	    }

	pin->setDefaultImage(bb::cascades::Image(pinImageSource_));
	pin->setPressedImage(bb::cascades::Image(pinImageSource_));
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
  QString title = V8ValueToQString(obj->getValue());
  label_->setText(title);
  return NATIVE_ERROR_OK;
}

int NativeAnnotationObject::setSubtitle(TiObject* obj)
{
  QString subtitle = V8ValueToQString(obj->getValue());
  label_->setText(label_->text() + "\n" + subtitle);
  return NATIVE_ERROR_OK;
}

int NativeAnnotationObject::setLeftView(TiObject* obj)
{
  QString leftView = V8ValueToQString(obj->getValue());
  leftView_->setDefaultImageSource(QUrl::fromLocalFile(Ti::TiHelper::getAssetPath(leftView)));
  leftView_->setPressedImage(QUrl::fromLocalFile(Ti::TiHelper::getAssetPath(leftView)));
  return NATIVE_ERROR_OK;
}

int NativeAnnotationObject::setRightView(TiObject* obj)
{
  QString rightView = V8ValueToQString(obj->getValue());
  rightView_->setDefaultImageSource(QUrl::fromLocalFile(Ti::TiHelper::getAssetPath(rightView)));
  rightView_->setPressedImage(QUrl::fromLocalFile(Ti::TiHelper::getAssetPath(rightView)));
  return NATIVE_ERROR_OK;
}


void NativeAnnotationObject::setupEvents(TiEventContainerFactory* containerFactory)
{
	NativeControlObject::setupEvents(containerFactory);

	TiEventContainer* click = containerFactory->createEventContainer();
	click->setDataProperty("type", tetCLICK);
	events_.insert(tetCLICK, EventPairSmartPtr(click, new AnnotationObjectEventHandler(click, this)));

	QObject::connect(pin, SIGNAL(clicked()), events_[tetCLICK]->handler(), SLOT(clicked()));
	QObject::connect(leftView_, SIGNAL(clicked()), events_[tetCLICK]->handler(), SLOT(leftViewClicked()));
	QObject::connect(rightView_, SIGNAL(clicked()), events_[tetCLICK]->handler(), SLOT(rightViewClicked()));
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

void AnnotationObjectEventHandler::leftViewClicked()
{
	eventContainer_->setDataProperty("clicksource", "leftView");
	eventContainer_->fireEvent();
}

void AnnotationObjectEventHandler::rightViewClicked()
{
	eventContainer_->setDataProperty("clicksource", "rightView");
	eventContainer_->fireEvent();
}





