/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef APPLICATIONMENUPROXY_H_
#define APPLICATIONMENUPROXY_H_
#include "TiCore.h"

namespace TiUI
{
class ApplicationMenuEventHandler;
class ApplicationMenuProxy : public Ti::TiProxy
{
public:
	CREATE_PROXY(ApplicationMenuProxy);
	ApplicationMenuProxy(const char*);
	virtual ~ApplicationMenuProxy();

	void setItems(Ti::TiValue);
	Ti::TiValue getItems();

	Ti::TiValue addItem(Ti::TiValue);
	Ti::TiValue removeItem(Ti::TiValue);
	Ti::TiValue removeAllItems(Ti::TiValue);

	EXPOSE_SETTER(ApplicationMenuProxy, setItems);
	EXPOSE_GETTER(ApplicationMenuProxy, getItems);

	EXPOSE_METHOD(ApplicationMenuProxy, addItem);
	EXPOSE_METHOD(ApplicationMenuProxy, removeItem);
	EXPOSE_METHOD(ApplicationMenuProxy, removeAllItems);
};

class ApplicationMenuEventHandler : public QObject
{
	Q_OBJECT;
public:
	ApplicationMenuEventHandler();
	virtual ~ApplicationMenuEventHandler();
	void addProxy(ApplicationMenuProxy*);
	void removeProxy(ApplicationMenuProxy*);
private:
	QList<ApplicationMenuProxy*> _proxies;
public slots:
	void onClick();
};
} /* namespace TiUI */
#endif /* APPLICATIONMENUPROXY_H_ */
