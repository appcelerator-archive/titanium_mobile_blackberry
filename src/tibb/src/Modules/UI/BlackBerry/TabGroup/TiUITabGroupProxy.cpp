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
	createPropertyGetter("tabs", _getTiTabs);
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
	if(value.isNumber())
	{
		setActiveTab(_allTabs.at((int)value.toNumber()));
	} else
	if(value.isProxy())
	{
		setActiveTab(static_cast<TiUITabProxy*>(value.toProxy()));
	}
	return Ti::TiValue();
}

void TiUITabGroupProxy::setActiveTab(TiUITabProxy* tab)
{
	Ti::TiEventParameters eventParams;
	eventParams.addParam("previousTab", _activeTab);
	eventParams.addParam("previousIndex", getTabbedPane()->indexOf(_activeTab->getTab()));
	getTabbedPane()->setActiveTab(tab->getTab());
	_activeTab = tab;
	eventParams.addParam("index", getTabbedPane()-> indexOf(_activeTab->getTab()));
	eventParams.addParam("tab", tab);
	changeIsFocus(false);
	fireEvent(Ti::TiConstants::EventFocus, eventParams);
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
	_activeTab = _allTabs.at(0);
	return val;
}

QList<TiUITabProxy*> TiUITabGroupProxy::getTabs()
{
	return _allTabs;
}

Ti::TiValue TiUITabGroupProxy::getTiTabs()
{
	Ti::TiValue rValue;
	QList<Ti::TiValue> array;
	foreach(TiUITabProxy *proxy, _allTabs)
	{
		Ti::TiValue current;
		current.setProxy(proxy);
		array.append(current);
	}
	rValue.setList(array);
	return rValue;
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
