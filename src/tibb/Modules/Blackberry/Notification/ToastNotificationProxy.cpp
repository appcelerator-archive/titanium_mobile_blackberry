/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "ToastNotificationProxy.h"

namespace TiBlackberry {

ToastNotificationProxy::ToastNotificationProxy(const char* name) : Ti::TiProxy(name)
{

	createPropertySetter("buttonTitle", _setButtonTitle);
	createPropertySetter("icon", _setIcon);
	createPropertySetter("message", _setMessage);
	createPropertySetter("position", _setPosition);
	createPropertySetter("modality", _setModality);

	createPropertyFunction("show", _show);
	createPropertyFunction("cancel", _cancel);

	_toast = new bb::system::SystemToast();
	_toast->setPosition(bb::system::SystemUiPosition::BottomCenter);

	ToastNotificationEventHandler* eventHandler = new ToastNotificationEventHandler(this);
	eventHandler->setParent(_toast);
	QObject::connect(
			_toast,
			SIGNAL(finished(bb::system::SystemUiResult::Type)),
			eventHandler,
			SLOT(onFinish(bb::system::SystemUiResult::Type))
	);

}

ToastNotificationProxy::~ToastNotificationProxy()
{
	delete _toast;
}
void ToastNotificationProxy::setButtonTitle(Ti::TiValue value)
{
	_toast->button()->setLabel(value.toString());
}
void ToastNotificationProxy::setIcon(Ti::TiValue value)
{
	QString res = Ti::TiConstants::ResourcesDir;
	res.append("/").append(value.toString());
	res.replace("//", "/");
	_toast->setIcon(QUrl(res));
}
void ToastNotificationProxy::setMessage(Ti::TiValue value)
{
	_toast->setBody(value.toString());
}

void ToastNotificationProxy::setPosition(Ti::TiValue value)
{
	if(value.isNumber()) {
		_toast->setPosition(static_cast<bb::system::SystemUiPosition::Type>(value.toNumber()));
	}
}

void ToastNotificationProxy::setModality(Ti::TiValue value)
{
	if(value.isNumber()) {
		_toast->setModality(static_cast<bb::system::SystemUiModality::Type>(value.toNumber()));
	}
}

Ti::TiValue ToastNotificationProxy::show(Ti::TiValue)
{
	_toast->show();
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

Ti::TiValue ToastNotificationProxy::cancel(Ti::TiValue)
{
	_toast->cancel();
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

ToastNotificationEventHandler::ToastNotificationEventHandler(ToastNotificationProxy* proxy) : _proxy(proxy)
{
//	setParent(_proxy->_toast);
}
ToastNotificationEventHandler::~ToastNotificationEventHandler()
{

}

void ToastNotificationEventHandler::onFinish(bb::system::SystemUiResult::Type type)
{
	Ti::TiEventParameters eventParams;

	QString result = "";
	switch(type) {
	case bb::system::SystemUiResult::None: result = "none"; break;
	case bb::system::SystemUiResult::ButtonSelection: result = "buttonSelection";break;
	case bb::system::SystemUiResult::ConfirmButtonSelection: result = "confirmButtonSelection";break;
	case bb::system::SystemUiResult::CancelButtonSelection: result = "cancelButtonSelection";break;
	case bb::system::SystemUiResult::TimeOut: result = "timeOut";break;
	case bb::system::SystemUiResult::CustomButtonSelection: result = "customButtonSelection";break;
	}
	eventParams.addParam("result", result);
	eventParams.addParam("type", "finish");
	_proxy->fireEvent("finish", eventParams);
}

}
