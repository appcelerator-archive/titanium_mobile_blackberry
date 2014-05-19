/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_UIWINDOWPROXY_H_
#define TI_UIWINDOWPROXY_H_

#include <TiCore.h>
#include <bb/cascades/SupportedDisplayOrientation>

namespace bb{
namespace cascades{
class Page;
}
}
namespace TiUI {
class TiUIWindowActionEvent;
class TiUIWindowProxy: public Ti::TiWindowProxy {
public:
	CREATE_PROXY(TiUIWindowProxy)
	TiUIWindowProxy(const char*);
	virtual ~TiUIWindowProxy();

	virtual Ti::TiValue addAction(Ti::TiValue);

	EXPOSE_METHOD(TiUIWindowProxy, addAction)

	TI_CREATE_SETTER_GETTER(TiUIWindowProxy, setTitle, getTitle)
	TI_CREATE_SETTER_GETTER(TiUIWindowProxy, setRightNavButton, getRightNavButton)
	TI_CREATE_SETTER_GETTER(TiUIWindowProxy, setLeftNavButton, getLeftNavButton)

private:
	QList<TiUIWindowActionEvent*> actionItemEvents;
	QList<bb::cascades::SupportedDisplayOrientation::Type> _orientationModes;
	void updateOrientation();
};

class TiUIWindowActionEvent : public QObject
{
	Q_OBJECT;
public:
	TiUIWindowActionEvent(TiUIWindowProxy *proxy, Ti::TiCallback* _callback);
	virtual ~TiUIWindowActionEvent();
public slots:
	void onActionTriggered();
private:
	TiUIWindowProxy* _proxy;
	Ti::TiCallback* _callback;
};
}
#endif /* TIUIWINDOWPROXY_H_ */
