/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include <bb/cascades/LayoutUpdateHandler>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/DockLayout>
#include <bb/cascades/StackLayout>
#include <bb/cascades/GestureHandler>
#include <bb/cascades/TapHandler>
#include <bb/cascades/DoubleTapHandler>
#include <bb/cascades/PinchHandler>
#include <bb/cascades/LongPressHandler>

#include <bb/cascades/TapEvent>
#include <bb/cascades/DoubleTapEvent>
#include <bb/cascades/LongPressEvent>
#include <bb/cascades/PinchEvent>
#include <bb/cascades/LongPressEvent>
#include <bb/cascades/Control>


#include "Ti_Helper.h"
#include "Ti_ViewProxy.h"
#include "Ti_Constants.h"
#include "Ti_View.h"

#include "TitaniumLayout.h"

Ti::TiView::TiView(Ti::TiViewProxy *_proxy)
: bb::cascades::Container(NULL),
proxy(_proxy),
childControl(NULL),
_width(""),
_height(""),
_top(""),
_bottom(""),
_left(""),
_right(""),
parentView(NULL),
_zIndex(-1)
{
	setLayout(bb::cascades::AbsoluteLayout::create());
	setLayoutProperties(bb::cascades::AbsoluteLayoutProperties::create());
	setChildControl(NULL);
    setImplicitLayoutAnimationsEnabled(false);
}

Ti::TiView::~TiView() {
	Ti::TiProxy *proxy = getProxy();
	if(proxy != NULL)
	{
		QString name = getProxy()->getProxyName();
		// qDebug() << "[INTERNAL] DELETING VIEW" << name.replace("Proxy", "").replace("TiUI", "Ti.UI.");
	}
	else
	{
		// qDebug() << "[INTERNAL] PROXY HAS BEEN DELETED";
	}
}

void Ti::TiView::onTapEvent(bb::cascades::TapEvent*)
{
	Ti::TiEventParameters clickEvent;
	clickEvent.addParam("type", "click");
	getProxy()->fireEvent(Ti::TiConstants::EventClick, clickEvent);
	getProxy()->fireEvent(Ti::TiConstants::EventSingleTap, clickEvent);
}
void Ti::TiView::onDoubleTapEvent(bb::cascades::DoubleTapEvent*)
{

}

void Ti::TiView::onLongPressEvent(bb::cascades::LongPressEvent*)
{

}

void Ti::TiView::onPinchStartedEvent(bb::cascades::PinchEvent*)
{

}
void Ti::TiView::onPinchUpdatedEvent(bb::cascades::PinchEvent*)
{

}
void Ti::TiView::onPinchEndedEvent(bb::cascades::PinchEvent*)
{

}
void Ti::TiView::onPinchCancelledEvent(bb::cascades::PinchEvent*)
{

}

void Ti::TiView::onEventAdded(QString eventName)
{
	bb::cascades::GestureHandler *gesture = NULL;
	if(eventName == Ti::TiConstants::EventClick || eventName == Ti::TiConstants::EventSingleTap)
	{
		gesture = new bb::cascades::TapHandler(this);
		QObject::connect(gesture, SIGNAL(tapped(bb::cascades::TapEvent*)), this, SLOT(onTapEvent(bb::cascades::TapEvent*)));
	}
	else if(eventName == Ti::TiConstants::EventDoubleClick || eventName == Ti::TiConstants::EventDoubleTap)
	{
		gesture = new bb::cascades::DoubleTapHandler(this);
		QObject::connect(gesture, SIGNAL(doubleTapped(bb::cascades::DoubleTapEvent*)), this, SLOT(onDoubleTapEvent(bb::cascades::DoubleTapEvent*)));
	}
	else if(eventName == Ti::TiConstants::EventLongClick || eventName == Ti::TiConstants::EventLongPress)
	{
		gesture = new bb::cascades::LongPressHandler(this);
		QObject::connect(gesture, SIGNAL(longPressed(bb::cascades::LongPressEvent*)), this, SLOT(onLongPressEvent(bb::cascades::LongPressEvent*)));
	}
	else if(eventName == Ti::TiConstants::EventPinch)
	{
		gesture = new bb::cascades::PinchHandler(this);

		QObject::connect(gesture, SIGNAL(pinchStarted(bb::cascades::PinchEvent*)), this, SLOT(onPinchStartedEvent(bb::cascades::PinchEvent*)));
		QObject::connect(gesture, SIGNAL(pinchUpdated(bb::cascades::PinchEvent*)), this, SLOT(onPinchUpdatedEvent(bb::cascades::PinchEvent*)));
		QObject::connect(gesture, SIGNAL(pinchEnded(bb::cascades::PinchEvent*)), this, SLOT(onPinchEndedEvent(bb::cascades::PinchEvent*)));
		QObject::connect(gesture, SIGNAL(pinchCancelled(bb::cascades::PinchEvent*)), this, SLOT(onPinchCancelledEvent(bb::cascades::PinchEvent*)));
	}
	if(gesture == NULL) return;
	if(childControl == NULL)
	{
		addGestureHandler(gesture);
	}
	else
	{
		childControl->addGestureHandler(gesture);
	}

}

Ti::TiViewProxy* Ti::TiView::getProxy() const
{
	HandleScope scope;

	return proxy;
}

void Ti::TiView::setTiLayout()
{
	viewLayout = new Ti::TitaniumLayout(this);
}
void Ti::TiView::setParentView(Ti::TiView* view)
{
	parentView = view;
}

void Ti::TiView::_setLayout(QString layout)
{
	viewLayout->_setLayout(layout);
}
bool Ti::TiView::ingoreWidth()
{
	return false;
}
bool Ti::TiView::ingoreHeight()
{
	return false;
}
QString Ti::TiView::defaultWidth()
{
	return Ti::TiConstants::SizeSIZE;
}
QString Ti::TiView::defaultHeight()
{
	return Ti::TiConstants::SizeSIZE;
}

void Ti::TiView::onRelayout(QRectF rect)
{
	Ti::TiEventParameters eventParams;

	Ti::TiEventParameters rectParams;
	rectParams.addParam("width", rect.width());
	rectParams.addParam("height", rect.height());
	rectParams.addParam("x", rect.x());
	rectParams.addParam("y", rect.y());

	eventParams.addParam("rect", rectParams);
	getProxy()->fireEvent("postlayout", eventParams);
}

void Ti::TiView::setZIndex(int index)
{
	_zIndex = index;
	if(parentView != NULL)
	{
		parentView->add(this);
	}
}

int Ti::TiView::getZIndex()
{
	return _zIndex;
}

/*
 * TODO: Remove this crap
 */

class mNativeObject : public bb::cascades::Control
{
public:
	virtual ~mNativeObject() = 0;
	virtual bb::cascades::Control* getNativeHandle() = 0;
	struct Ti::Layout::Node layoutNode_;
};
class mTiUIBase
{
public:
	mTiUIBase() {};
	virtual ~mTiUIBase() = 0;
	virtual mNativeObject* getNativeObject() = 0;
	virtual Handle<Value> getValue() = 0;
};
#include "NativeObject.h"
#include "NativeControlObject.h"

void Ti::TiView::addOldObject(void* o)
{
	NativeObject *obj = (NativeObject*)o;
	bb::cascades::Control* control = (bb::cascades::Control*) obj->getNativeHandle();
	bb::cascades::Container::add(control);
	Ti::Layout::TiNode::nodeAddChild(&viewLayout->_layoutNode, ((NativeControlObject*) obj)->layout());
	struct Ti::Layout::Node* root = Ti::Layout::TiNode::nodeRequestLayout(&viewLayout->_layoutNode);
	if (root) {
		Ti::Layout::TiNode::nodeLayout(root);
	}
}
void Ti::TiView::add(bb::cascades::Control* control)
{
	Ti::TiView *newView = static_cast<Ti::TiView*>(control);
	if(!childViews.contains(newView))
	{
		newView->setParentView(this);
		childViews.append(newView);
		viewLayout->addChild(newView);
	}
	else
	{
		bb::cascades::Container::remove(newView);
	}
	if(newView->_zIndex != -1)
	{
		bb::cascades::Container::insert(newView->_zIndex, newView);
	}
	else
	{
		bb::cascades::Container::add(newView);
	}
}
void Ti::TiView::remove(bb::cascades::Control* control)
{
	Ti::TiView *childView = static_cast<Ti::TiView*>(control);
	if(childViews.contains(childView))
	{
		bb::cascades::Container::remove(childView);
		viewLayout->removeChild(childView);
		childViews.removeOne(childView);
	}
}

void Ti::TiView::setChildControl(bb::cascades::Control *control)
{
	if(control == NULL) return;
	bb::cascades::Container::add(control);
	childControl = control;
	childControl->setImplicitLayoutAnimationsEnabled(false);
	viewLayout->_setChildControl(childControl);
}


void Ti::TiView::_setWidth(QString v)
{
	_width = v;
	viewLayout->_setWidth(v);
}

void Ti::TiView::_setHeight(QString v)
{
	_height = v;
	viewLayout->_setHeight(v);
}

void Ti::TiView::_setTop(QString v)
{
	_top = v;
	viewLayout->_setTop(v);
}

void Ti::TiView::_setBottom(QString v)
{
	_bottom = v;
	viewLayout->_setBottom(v);
}

void Ti::TiView::_setLeft(QString v)
{
	_left = v;
	viewLayout->_setLeft(v);
}

void Ti::TiView::_setRight(QString v)
{
	_right = v;
	viewLayout->_setRight(v);
}

