/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITabProxy.h"
#include "../Window/TiUIWindowProxy.h"

#include <bb/cascades/Tab>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/Image>
#include <bb/cascades/Page>
namespace TiUI {

TiUITabProxy::TiUITabProxy(const char* name) : Ti::TiProxy(name),
	_rootWindow(NULL)
{
	_tab = bb::cascades::Tab::create();
	_navigationPane = new bb::cascades::NavigationPane();
	_tab->setContent(_navigationPane);

	createPropertySetter("title", _setTitle);
	createPropertySetter("icon", _setIcon);
	createPropertySetter("window", _setWindow);
	createPropertyFunction("open", _open);
	createPropertyFunction("close", _close);
	createPropertyFunction("pop", _pop);

	TiUITabProxyEventHandler *event = new TiUITabProxyEventHandler(this);
	QObject::connect(_navigationPane, SIGNAL(popTransitionEnded(bb::cascades::Page*)), event, SLOT(onPagePoped(bb::cascades::Page*)));
	QObject::connect(_navigationPane, SIGNAL(pushTransitionEnded(bb::cascades::Page*)), event, SLOT(onPagePushed(bb::cascades::Page*)));
	QObject::connect(_navigationPane, SIGNAL(topChanged(bb::cascades::Page*)), event, SLOT(onPageFocused(bb::cascades::Page*)));

}

TiUITabProxy::~TiUITabProxy()
{
	_rootWindow->makeWeak();
	delete _navigationPane;
}

void TiUITabProxy::setRootWindow(TiUIWindowProxy* windowProxy)
{
	_rootWindow = windowProxy;
}

QList<Ti::TiWindowProxy*> TiUITabProxy::getAllWindows()
{
	return _windows;
}
void TiUITabProxy::removeWindow(Ti::TiWindowProxy* w)
{
	_windows.removeOne(w);
}

bb::cascades::Tab * TiUITabProxy::getTab()
{
	return _tab;
}
bb::cascades::NavigationPane * TiUITabProxy::getNavigationPane()
{
	return _navigationPane;
}

void TiUITabProxy::setTitle(Ti::TiValue value)
{
	_tab->setTitle(value.toString());
}

void TiUITabProxy::setIcon(Ti::TiValue value)
{
	_tab->setImageSource(QUrl(Ti::TiHelper::getAssetPath(value.toString())));
}

void TiUITabProxy::setWindow(Ti::TiValue value)
{
	open(value);
	TiUIWindowProxy *windowProxy = static_cast<TiUIWindowProxy*>(value.toProxy());
	setRootWindow(windowProxy);
}

Ti::TiValue TiUITabProxy::open(Ti::TiValue value)
{
	Ti::TiValue val;
	val.setUndefined();

	Ti::TiWindowProxy* windowProxy;
	if(value.isList())
	{
		QList<Ti::TiValue> vs = value.toList();
		Ti::TiValue v = vs.at(0);
		windowProxy = static_cast<TiUIWindowProxy*>(v.toProxy());
	}
	else if(value.isProxy())
	{
		windowProxy = static_cast<TiUIWindowProxy*>(value.toProxy());
	}
	else
	{
		return val;
	}

	windowProxy->clearWeak();
	windowProxy->getPane()->setParent(NULL);
	_windows.append(windowProxy);

	Ti::TiEventParameters _params;
	windowProxy->fireEvent(Ti::TiConstants::EventOpen, _params);

	_navigationPane->push(static_cast<bb::cascades::Page*>(windowProxy->getPane()));
	return val;
}

Ti::TiValue TiUITabProxy::pop(Ti::TiValue value)
{
	_navigationPane->pop();
	_windows.removeLast();
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITabProxy::close(Ti::TiValue value)
{
	Ti::TiValue val;
	val.setUndefined();
	Ti::TiWindowProxy* windowProxy;
	bool animated = true;
	if(value.isList())
	{
		QList<Ti::TiValue> vs = value.toList();
		Ti::TiValue v = vs.at(0);
		windowProxy = static_cast<TiUIWindowProxy*>(v.toProxy());
		Ti::TiValue optionsValue = vs.at(1);
		if(optionsValue.isMap())
		{
			QMap<QString, Ti::TiValue> options = optionsValue.toMap();
			if(options.contains("animated"))
			{
				animated = options["animated"].toBool();
			}
		}
	}
	else if(value.isProxy())
	{
		windowProxy = static_cast<TiUIWindowProxy*>(value.toProxy());
	}
	else
	{
		return val;
	}
	if(_windows.last() == windowProxy && animated == true)
	{
		_navigationPane->pop();
	}
	else
	{
		_navigationPane->remove(static_cast<bb::cascades::Page*>(windowProxy->getPane()));
		Ti::TiEventParameters _params;
		windowProxy->fireEvent(Ti::TiConstants::EventClose, _params);
		windowProxy->makeWeak();
	}
	_windows.removeOne(windowProxy);

	return val;
}

TiUITabProxyEventHandler::TiUITabProxyEventHandler(TiUITabProxy *proxy) : _proxy(proxy)
{
}

Ti::TiWindowProxy* TiUITabProxyEventHandler::windowFromPage(bb::cascades::Page* page)
{
	foreach(Ti::TiWindowProxy* windowProxy, _proxy->getAllWindows())
	{
		if(windowProxy != NULL && static_cast<bb::cascades::Page*>(windowProxy->getPane()) == page)
		{
			return windowProxy;
		}
	}
	return NULL;
}
void TiUITabProxyEventHandler::onPagePoped(bb::cascades::Page* page)
{
	qDebug() << "[TiUITabProxyEventHandler] onPagePoped";
	Ti::TiWindowProxy* window = windowFromPage(page);
	if(window != NULL)
	{
		{
			Ti::TiEventParameters _params;
			window->fireEvent(Ti::TiConstants::EventBlur, _params);
		}
		{
			Ti::TiEventParameters _params;
			window->fireEvent(Ti::TiConstants::EventClose, _params);
		}
		window->makeWeak();
		_proxy->removeWindow(window);
	}
}

void TiUITabProxyEventHandler::onPagePushed(bb::cascades::Page* page)
{
	/*
	 * Moved to tab.open()
	Ti::TiWindowProxy* window = windowFromPage(page);
	if(window != NULL)
	{
		Ti::TiEventParameters _params;
		window->fireEvent(Ti::TiConstants::EventOpen, _params);
	}
	*/
}

void TiUITabProxyEventHandler::onPageFocused(bb::cascades::Page* page)
{
	Ti::TiWindowProxy* window = windowFromPage(page);
	if(window != NULL)
	{
		foreach(Ti::TiWindowProxy* proxies, _proxy->getAllWindows())
		{
			if(proxies->isFocused())
			{
				Ti::TiEventParameters _params;
				proxies->fireEvent(Ti::TiConstants::EventBlur, _params);
			}
		}
		Ti::TiEventParameters _params;
		window->fireEvent(Ti::TiConstants::EventFocus, _params);
	}
}

}
