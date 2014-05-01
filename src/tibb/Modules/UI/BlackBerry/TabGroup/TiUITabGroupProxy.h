/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TABGROUPPROXY_H_
#define TI_TABGROUPPROXY_H_

#include "TiCore.h"
#include <v8.h>

namespace bb
{
namespace cascades
{
class TabbedPane;
class Tab;
}
}
namespace TiUI {
class TiUITabProxy;
class TiUITabGroupEventHandler;
class TiUITabGroupProxy : public Ti::TiWindowProxy
{
public:
	CREATE_PROXY(TiUITabGroupProxy)
	TiUITabGroupProxy(const char*);
	bb::cascades::TabbedPane* getTabbedPane();

	Ti::TiValue addTab(Ti::TiValue);
	Ti::TiValue setActiveTab(Ti::TiValue);

	virtual void setActiveTab(TiUITabProxy*);
	virtual void fireEvent(QString name, Ti::TiEventParameters params);

	EXPOSE_METHOD(TiUITabGroupProxy, addTab)
	EXPOSE_METHOD(TiUITabGroupProxy, setActiveTab)

	TI_CREATE_SETTER_GETTER(TiUITabGroupProxy, setShowTabsOnActionBar, getShowTabsOnActionBar)

	virtual ~TiUITabGroupProxy();

	QList<TiUITabProxy*> getTabs();
private:
	TiUITabProxy* _activeTab;
	QList<TiUITabProxy*> _allTabs;
	TiUITabGroupEventHandler* _eventHandler;
};

class TiUITabGroupEventHandler : public QObject
{
Q_OBJECT
public:
	TiUITabGroupEventHandler(TiUITabGroupProxy* proxy);
public slots:
	void activeTabChanged(bb::cascades::Tab* activeTab);
private:
	TiUITabGroupProxy* _proxy;
};

}
#endif /* TABGROUPPROXY_H_ */
