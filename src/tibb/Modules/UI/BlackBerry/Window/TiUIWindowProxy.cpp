/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIWindowProxy.h"
#include "TiUIWindow.h"

#include "../NavButton/NavButtonProxy.h"
#include "../TiUIBlackberryModule.h"

#include <bb/cascades/Page>
#include <bb/cascades/Container>
#include <bb/cascades/Application>
#include <bb/cascades/ActionItem>
#include <bb/cascades/TitleBar>
#include <bb/cascades/OrientationSupport>
#include <bb/cascades/ActionBarPlacement>

namespace TiUI {


TiUIWindowProxy::TiUIWindowProxy(const char* name)
	: Ti::TiWindowProxy(name)
{
	createPropertyFunction("addAction", _addAction);
	createPropertySetterGetter("title", _setTitle, _getTitle);
	createPropertySetterGetter("rightNavButton", _setRightNavButton, _getRightNavButton);
	createPropertySetterGetter("leftNavButton", _setLeftNavButton, _getLeftNavButton);

	bb::cascades::Page *page = new bb::cascades::Page();
	setPane(page);
	setView(new TiUIWindow(this));
	page->setContent(view);
}

TiUIWindowProxy::~TiUIWindowProxy()
{
	if(!actionItemEvents.isEmpty())
		qDeleteAll(actionItemEvents);
}


TI_GETTER_DEFER(TiUIWindowProxy, getRightNavButton);
void TiUIWindowProxy::setRightNavButton(Ti::TiValue val)
{
	if(!val.isProxy()) return;

	NavButtonProxy *button = static_cast<NavButtonProxy*>(val.toProxy());
	bb::cascades::Page* page = static_cast<bb::cascades::Page*>(getPane());
	bb::cascades::TitleBar * titleBar = page->titleBar();
	if(titleBar == NULL)
	{
		titleBar = new bb::cascades::TitleBar();
		page->setTitleBar(titleBar);
	}
	titleBar->setAcceptAction(button->getNativeItem());
}

TI_GETTER_DEFER(TiUIWindowProxy, getLeftNavButton);
void TiUIWindowProxy::setLeftNavButton(Ti::TiValue val)
{
	if(!val.isProxy()) return;

	NavButtonProxy *button = static_cast<NavButtonProxy*>(val.toProxy());
	bb::cascades::Page* page = static_cast<bb::cascades::Page*>(getPane());
	bb::cascades::TitleBar * titleBar = page->titleBar();
	if(titleBar == NULL)
	{
		titleBar = new bb::cascades::TitleBar();
		page->setTitleBar(titleBar);
	}
	titleBar->setDismissAction(button->getNativeItem());
}

void TiUIWindowProxy::setTitle(Ti::TiValue val)
{
	bb::cascades::Page* page = static_cast<bb::cascades::Page*>(getPane());
	bb::cascades::TitleBar * titleBar = page->titleBar();
	if(titleBar == NULL)
	{
		titleBar = new bb::cascades::TitleBar();
		page->setTitleBar(titleBar);
	}
	titleBar->setTitle(val.toString());
}


Ti::TiValue TiUIWindowProxy::getTitle()
{
	bb::cascades::Page* page = static_cast<bb::cascades::Page*>(getPane());
	bb::cascades::TitleBar * titleBar = page->titleBar();
	if(titleBar == NULL)
	{
		return Ti::TiValue();
	}
	Ti::TiValue r;
	r.setString(titleBar->title());
	return r;
}

Ti::TiValue TiUIWindowProxy::addAction(Ti::TiValue value)
{
	if(!value.isMap()) return Ti::TiValue();

	QMap<QString, Ti::TiValue> args = value.toMap();


	bb::cascades::ActionItem *actionItem = new bb::cascades::ActionItem();
	if(args.contains("title"))
	{
		Ti::TiValue title = args["title"];
		actionItem->setTitle(title.toString());
	}
	if(args.contains("image"))
	{
		Ti::TiValue image = args["image"];
		actionItem->setImageSource(QUrl(Ti::TiHelper::getAssetPath(image.toString())));
	}
	if(args.contains("callback"))
	{
		Ti::TiValue callback = args["callback"];
		TiUIWindowActionEvent* eventHandler = new TiUIWindowActionEvent(this, new Ti::TiCallback(this, callback));
		actionItemEvents.append(eventHandler);
		QObject::connect(actionItem, SIGNAL(triggered()), eventHandler, SLOT(onActionTriggered()));
	}

	bb::cascades::Page* page = static_cast<bb::cascades::Page*>(getPane());
	if(args.contains("placement"))
	{
		Ti::TiValue placement = args["placement"];
		page->addAction(actionItem, (bb::cascades::ActionBarPlacement::Type)placement.toNumber());
	}
	else
	{
		page->addAction(actionItem);
	}
	Ti::TiValue val;
	val.setUndefined();
	return val;
}


TiUIWindowActionEvent::TiUIWindowActionEvent(TiUIWindowProxy* proxy, Ti::TiCallback* callback) :
		_proxy(proxy),
		_callback(callback)
{
}

TiUIWindowActionEvent::~TiUIWindowActionEvent()
{
	qDebug() << "[TiUIWindowActionEvent] deleted";
    delete _callback;
}

void TiUIWindowActionEvent::onActionTriggered()
{
	_callback->fire(Ti::TiEventParameters());
}

}
