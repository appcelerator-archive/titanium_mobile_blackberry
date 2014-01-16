/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NAVBUTTONPROXY_H_
#define NAVBUTTONPROXY_H_

#include "TiCore.h"
#include <bb/cascades/ActionItem>

namespace TiUI
{
class NavButtonProxy  : public Ti::TiProxy{
public:
	CREATE_PROXY(NavButtonProxy);
	NavButtonProxy(const char*);

	Ti::TiValue getTitle();
	void setTitle(Ti::TiValue);
	EXPOSE_SETTER(NavButtonProxy, setTitle);
	EXPOSE_GETTER(NavButtonProxy, getTitle);
	bb::cascades::ActionItem *getNativeItem();
	virtual ~NavButtonProxy();
private:
	bb::cascades::ActionItem *_item;
};


class NavButtonEventHandler : public QObject
{
	Q_OBJECT;
public:
	NavButtonEventHandler(NavButtonProxy*);
	virtual ~NavButtonEventHandler();
public slots:
	void triggered();
private:
	NavButtonProxy* _proxy;
};

}
#endif /* NAVBUTTONPROXY_H_ */
