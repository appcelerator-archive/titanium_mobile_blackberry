/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIAlertDialogProxy.h"
#include <bb/system/SystemDialog>

static QList<bb::system::SystemDialog*> _alertQueue;
static bool _alertShowing = false;

namespace TiUI {

TiUIAlertDialogProxy::TiUIAlertDialogProxy(const char* name) : TiProxy(name), _cancel(-1)
{
	_alert = new bb::system::SystemDialog("OK");
	_eventHandler = new TiUIAlertDialogEventHandler(this);

	QObject::connect(_alert, SIGNAL(finished(bb::system::SystemUiResult::Type)), _eventHandler, SLOT(buttonSelected(bb::system::SystemUiResult::Type)));

	createPropertySetterGetter("buttonNames", _setButtonNames,  _getButtonNames);
	createPropertySetterGetter("cancel", _setCancel,  _getCancel);
	createPropertySetterGetter("message", _setMessage,  _getMessage);
	createPropertySetterGetter("style", _setStyle,  _getStyle);
	createPropertySetterGetter("title", _setTitle,  _getTitle);
	createPropertySetterGetter("ok", _setOk,  _getOk);
	createPropertySetterGetter("persistent", _setPersistent,  _getPersistent);

	createPropertyFunction("show", _show);
	createPropertyFunction("hide", _hide);

	clearWeak();
}

TiUIAlertDialogProxy::~TiUIAlertDialogProxy()
{
	delete _alert;
	delete _eventHandler;
}

Ti::TiValue TiUIAlertDialogProxy::getButtonNames()
{
	Ti::TiValue val;
	QList<Ti::TiValue> array;
	foreach(QString name, _buttonNames)
	{
		Ti::TiValue btn;
		btn.setString(name);
		array.append(btn);
	}
	val.setList(array);
	return val;
}

void TiUIAlertDialogProxy::setButtonNames(Ti::TiValue val)
{
	if(val.isNull())
	{
		_alert->clearButtons();
		_alert->confirmButton()->setLabel("OK");
		return;
	}
	if(!val.isList())
	{
		return;
	}

	_alert->confirmButton()->setLabel(QString::null);
	_alert->cancelButton()->setLabel(QString::null);
	_alert->clearButtons();
	_buttonNames.clear();
	foreach(Ti::TiValue current, val.toList())
	{
		bb::system::SystemUiButton* button = new bb::system::SystemUiButton();
		QString title = current.toString();
		_buttonNames.append(title);
		button->setLabel(title);
		_alert->appendButton(button);
	}
}

Ti::TiValue TiUIAlertDialogProxy::getCancel()
{
	Ti::TiValue val;
	val.setNumber(_cancel);
	return val;
}

void TiUIAlertDialogProxy::setCancel(Ti::TiValue val)
{
	_cancel = val.toNumber();
}

TI_GETTER_DEFER(TiUIAlertDialogProxy, getMessage)
void TiUIAlertDialogProxy::setMessage(Ti::TiValue val)
{
	_alert->setBody(val.toString());
}

TI_GETTER_DEFER(TiUIAlertDialogProxy, getStyle)
void TiUIAlertDialogProxy::setStyle(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIAlertDialogProxy, getTitle)
void TiUIAlertDialogProxy::setTitle(Ti::TiValue val)
{
	_alert->setTitle(val.toString());
}

TI_GETTER_DEFER(TiUIAlertDialogProxy, getOk)
void TiUIAlertDialogProxy::setOk(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIAlertDialogProxy, getPersistent)
void TiUIAlertDialogProxy::setPersistent(Ti::TiValue)
{
}


Ti::TiValue TiUIAlertDialogProxy::show(Ti::TiValue)
{
	clearWeak();
	_alertQueue.append(_alert);
	if(!_alertShowing) {
		_alert->show();
		_alertShowing = true;
	}

	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIAlertDialogProxy::hide(Ti::TiValue)
{
	_alert->cancel();
	_alertQueue.removeOne(_alert);
	if(_alertQueue.isEmpty())
	{
		_alertShowing = false;
	}
	else
	{
		_alertQueue.last()->show();
	}
	makeWeak();
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

TiUIAlertDialogEventHandler::TiUIAlertDialogEventHandler(TiUIAlertDialogProxy* proxy) : _proxy(proxy)
{

}

void TiUIAlertDialogEventHandler::buttonSelected(bb::system::SystemUiResult::Type type)
{
	bb::system::SystemDialog* dialog = static_cast<bb::system::SystemDialog*>(sender());
	bb::system::SystemUiButton* selectedButton = dialog->buttonSelection();

	_alertQueue.removeOne(dialog);
	int index = -1;

	for(int i = 0, len = dialog->buttonCount(); i < len; i++) {
		if(dialog->buttonAt(i) == selectedButton) {
			index = i;
			break;
		}
	}
	bool cancel = index == (int)_proxy->getCancel().toNumber();

	Ti::TiEventParameters eventParams;
	eventParams.addParam("index", index);
	eventParams.addParam("cancel", cancel);
	_proxy->fireEvent(Ti::TiConstants::EventClick, eventParams);

	if(_alertQueue.isEmpty())
	{
		_alertShowing = false;
	}
	else
	{
		_alertQueue.last()->show();
	}
	_proxy->makeWeak();
}
}
