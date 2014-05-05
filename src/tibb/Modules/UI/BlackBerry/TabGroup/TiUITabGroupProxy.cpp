/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITabGroupProxy.h"
#include "TiUITabProxy.h"
#include <bb/cascades/TabbedPane>
#include <bb/cascades/Application>

namespace TiUI {

TiUITabGroupProxy::TiUITabGroupProxy(const char* name) : Ti::TiWindowProxy(name), _activeTab(NULL)
{
	createPropertyFunction("addTab", _addTab);
	createPropertyFunction("setActiveTab", _setActiveTab);
	createPropertySetterGetter("showTabsOnActionBar", _setShowTabsOnActionBar, _getShowTabsOnActionBar);
	bb::cascades::TabbedPane* tabbedPane = new bb::cascades::TabbedPane();
	tabbedPane->setShowTabsOnActionBar(true);
	tabbedPane->setParent(NULL);
	setPane(tabbedPane);
	_eventHandler = new TiUITabGroupEventHandler(this);
	QObject::connect(tabbedPane, SIGNAL(activeTabChanged(bb::cascades::Tab*)), _eventHandler , SLOT(activeTabChanged(bb::cascades::Tab*)));
}

TiUITabGroupProxy::~TiUITabGroupProxy()
{
	delete _eventHandler;
}

void TiUITabGroupProxy::fireEvent(QString name, Ti::TiEventParameters params)
{
	Ti::TiWindowProxy::fireEvent(name, params);
	if(_activeTab == NULL) return;
	foreach(TiWindowProxy* window, _activeTab->getAllWindows())
	{
		if(window->isFocused())
		{
			window->fireEvent(name, params);
		}
	}
}

bb::cascades::TabbedPane* TiUITabGroupProxy::getTabbedPane()
{
	return static_cast<bb::cascades::TabbedPane*>(getPane());
}

void TiUITabGroupProxy::setShowTabsOnActionBar(Ti::TiValue value)
{
	getTabbedPane()->setShowTabsOnActionBar(value.toBool());
}
Ti::TiValue TiUITabGroupProxy::getShowTabsOnActionBar()
{
	Ti::TiValue value;
	value.setBool(getTabbedPane()->showTabsOnActionBar());
	return value;
}

Ti::TiValue TiUITabGroupProxy::setActiveTab(Ti::TiValue value)
{
	getTabbedPane()->setActiveTab(getTabbedPane()->at((int)value.toNumber()));
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

void TiUITabGroupProxy::setActiveTab(TiUITabProxy* tab)
{
	_activeTab = tab;
}

Ti::TiValue TiUITabGroupProxy::addTab(Ti::TiValue value)
{
	Ti::TiValue val;
	val.setUndefined();
	if(!value.isProxy())
	{
		return val;
	}

	TiUITabProxy *tabProxy = static_cast<TiUITabProxy*>(value.toProxy());
	tabProxy->clearWeak();
	getTabbedPane()->add(tabProxy->getTab());
	_allTabs.append(tabProxy);
	return val;
}

QList<TiUITabProxy*> TiUITabGroupProxy::getTabs()
{
	return _allTabs;
}

TiUITabGroupEventHandler::TiUITabGroupEventHandler(TiUITabGroupProxy* proxy)
{
	_proxy = proxy;
}

void TiUITabGroupEventHandler::activeTabChanged(bb::cascades::Tab* activeTab)
{
	foreach(TiUITabProxy* tab, _proxy->getTabs())
	{
		if(tab->getTab() == activeTab)
		{
			Ti::TiEventParameters eventParams;
			tab->fireEvent(Ti::TiConstants::EventBlur, eventParams);
			_proxy->setActiveTab(tab);
			return;
		}
	}
}

}
