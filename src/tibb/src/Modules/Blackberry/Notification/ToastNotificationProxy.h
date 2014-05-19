/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUINOTIFICATIONPROXY_H_
#define TIUINOTIFICATIONPROXY_H_

#include <TiCore.h>
#include <QObject>
#include <bb/system/SystemToast>

namespace TiBlackberry {
class ToastNotificationEventHandler;
class ToastNotificationProxy : public Ti::TiProxy
{
public:
	CREATE_PROXY(ToastNotificationProxy)
	ToastNotificationProxy(const char*);
	virtual ~ToastNotificationProxy();

	void setButtonTitle(Ti::TiValue);
	void setIcon(Ti::TiValue);
	void setMessage(Ti::TiValue);
	void setPosition(Ti::TiValue);
	void setModality(Ti::TiValue);

	Ti::TiValue show(Ti::TiValue);
	Ti::TiValue cancel(Ti::TiValue);

	EXPOSE_SETTER(ToastNotificationProxy, setMessage)
	EXPOSE_SETTER(ToastNotificationProxy, setIcon)
	EXPOSE_SETTER(ToastNotificationProxy, setButtonTitle)
	EXPOSE_SETTER(ToastNotificationProxy, setPosition)
	EXPOSE_SETTER(ToastNotificationProxy, setModality)

	EXPOSE_METHOD(ToastNotificationProxy, show)
	EXPOSE_METHOD(ToastNotificationProxy, cancel)
private:
	bb::system::SystemToast *_toast;
};

class ToastNotificationEventHandler : public QObject
{
	Q_OBJECT;
public:
	ToastNotificationEventHandler(ToastNotificationProxy*);
	virtual ~ToastNotificationEventHandler();
private:
	ToastNotificationProxy* _proxy;
public slots:
	void onFinish(bb::system::SystemUiResult::Type);
};

}
#endif /* TIUINOTIFICATIONPROXY_H_ */
