/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TABPROXY_H_
#define TI_TABPROXY_H_

#include "TiCore.h"
#include <QObject>
#include <v8.h>

using namespace v8;
namespace bb
{
namespace cascades
{
class Tab;
class NavigationPane;
class Page;
}
}
namespace TiUI {

class TiUIWindowProxy;

class TiUITabProxy : public Ti::TiProxy
{
public:
	TiUITabProxy(const char*);
	CREATE_PROXY(TiUITabProxy)
	bb::cascades::Tab* getTab();
	bb::cascades::NavigationPane* getNavigationPane();
	void setRootWindow(TiUIWindowProxy*);

	Ti::TiValue open(Ti::TiValue);
	Ti::TiValue close(Ti::TiValue);
	Ti::TiValue pop(Ti::TiValue);

	void setTitle(Ti::TiValue);
	void setIcon(Ti::TiValue);
	void setWindow(Ti::TiValue);

	EXPOSE_METHOD(TiUITabProxy, open)
	EXPOSE_METHOD(TiUITabProxy, close)
	EXPOSE_METHOD(TiUITabProxy, pop)

	EXPOSE_SETTER(TiUITabProxy, setTitle)
	EXPOSE_SETTER(TiUITabProxy, setIcon)
	EXPOSE_SETTER(TiUITabProxy, setWindow)

	TI_CREATE_SETTER_GETTER(TiUITabProxy, setPeekEnable, getPeekEnable)
	virtual ~TiUITabProxy();
	virtual void removeWindow(Ti::TiWindowProxy*);
	QList<Ti::TiWindowProxy*> getAllWindows();

private:
	bb::cascades::Tab* _tab;
	bb::cascades::NavigationPane *_navigationPane;
	TiUIWindowProxy* _rootWindow;
	QList<Ti::TiWindowProxy*> _windows;
};

class TiUITabProxyEventHandler : public QObject
{
	Q_OBJECT;
public:
	TiUITabProxyEventHandler(TiUITabProxy *);
	TiUITabProxy* _proxy;
	Ti::TiWindowProxy* windowFromPage(bb::cascades::Page*);
public slots:
	void onPagePoped(bb::cascades::Page*);
	void onPagePushed(bb::cascades::Page*);
	void onPageFocused(bb::cascades::Page*);
};
}
#endif /* TABPROXY_H_ */
