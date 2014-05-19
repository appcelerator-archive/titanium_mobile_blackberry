/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#ifndef TIUIALERTDIALOGPROXY_H_
#define TIUIALERTDIALOGPROXY_H_

#include <TiCore.h>
#include <bb/system/SystemUiResult>


namespace bb {
namespace system {
class SystemDialog;
}
}
namespace TiUI {

class TiUIAlertDialogEventHandler;

class TiUIAlertDialogProxy : public Ti::TiProxy
{
public:
	CREATE_PROXY(TiUIAlertDialogProxy)
	TiUIAlertDialogProxy(const char*);
	virtual ~TiUIAlertDialogProxy();

	Ti::TiValue show(Ti::TiValue);
	Ti::TiValue hide(Ti::TiValue);

	TI_CREATE_SETTER_GETTER(TiUIAlertDialogProxy, setButtonNames, getButtonNames)
	TI_CREATE_SETTER_GETTER(TiUIAlertDialogProxy, setCancel, getCancel)
	TI_CREATE_SETTER_GETTER(TiUIAlertDialogProxy, setMessage, getMessage)
	TI_CREATE_SETTER_GETTER(TiUIAlertDialogProxy, setStyle, getStyle)
	TI_CREATE_SETTER_GETTER(TiUIAlertDialogProxy, setTitle, getTitle)
	TI_CREATE_SETTER_GETTER(TiUIAlertDialogProxy, setOk, getOk)
	TI_CREATE_SETTER_GETTER(TiUIAlertDialogProxy, setPersistent, getPersistent)

	EXPOSE_METHOD(TiUIAlertDialogProxy, show)
	EXPOSE_METHOD(TiUIAlertDialogProxy, hide)

private:
	bb::system::SystemDialog *_alert;
	TiUIAlertDialogEventHandler* _eventHandler;
};

class TiUIAlertDialogEventHandler : public QObject
{
	Q_OBJECT;
public:
	TiUIAlertDialogEventHandler(TiUIAlertDialogProxy*);
private:
	TiUIAlertDialogProxy* _proxy;
public slots:
    void buttonSelected(bb::system::SystemUiResult::Type);
};
}
#endif /* TIUIALERTDIALOGPROXY_H_ */
