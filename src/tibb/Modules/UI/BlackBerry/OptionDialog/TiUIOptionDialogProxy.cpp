/*
 * TiUIOptionDialogProxy.cpp
 *
 *  Created on: Sunday, September 15, 2013
 *      Author: penrique
 */

#include "TiUIOptionDialogProxy.h"

namespace TiUI {

TiUIOptionDialogProxy::TiUIOptionDialogProxy(const char* name) :
		Ti::TiProxy(name),
		_selectedIndex(-1)
{
	createPropertySetterGetter("androidView", _setAndroidView,  _getAndroidView);
	createPropertySetterGetter("tizenView", _setTizenView,  _getTizenView);
	createPropertySetterGetter("cancel", _setCancel,  _getCancel);
	createPropertySetterGetter("destructive", _setDestructive,  _getDestructive);
	createPropertySetterGetter("options", _setOptions,  _getOptions);
	createPropertySetterGetter("persistent", _setPersistent,  _getPersistent);
	createPropertySetterGetter("selectedIndex", _setSelectedIndex,  _getSelectedIndex);
	createPropertySetterGetter("title", _setTitle,  _getTitle);
	createPropertySetterGetter("titleid", _setTitleid,  _getTitleid);

	createPropertyFunction("show", _show);
	createPropertyFunction("hide", _hide);

	_dialog = new bb::system::SystemListDialog();
    QObject::connect(
    		_dialog,
    		SIGNAL(finished(bb::system::SystemUiResult::Type)),
    		new TiUIOptionDialogEventHandler(this),
    		SLOT(clicked(bb::system::SystemUiResult::Type))
    );

}

TiUIOptionDialogProxy::~TiUIOptionDialogProxy()
{
	delete _dialog;
}
void TiUIOptionDialogProxy::setAndroidView(Ti::TiValue)
{
}
void TiUIOptionDialogProxy::setTizenView(Ti::TiValue)
{
}
void TiUIOptionDialogProxy::setCancel(Ti::TiValue)
{
}
void TiUIOptionDialogProxy::setDestructive(Ti::TiValue)
{
}
void TiUIOptionDialogProxy::setOptionNames()
{
	_dialog->clearList();
	for(int i = 0, len = _buttonNames.length(); i < len; i++)
	{
		_dialog->appendItem(_buttonNames.at(i), true, _selectedIndex == i);
	}
}
void TiUIOptionDialogProxy::setOptions(Ti::TiValue value)
{
	if(!value.isList()) return;
	QList<Ti::TiValue> values = value.toList();
	_buttonNames.clear();
	foreach(Ti::TiValue current, values)
	{
		_buttonNames.append(current.toString());
	}
	setOptionNames();
}
void TiUIOptionDialogProxy::setPersistent(Ti::TiValue)
{
}
void TiUIOptionDialogProxy::setSelectedIndex(Ti::TiValue value)
{
	_selectedIndex = (int)value.toNumber();
	setOptionNames();

}
void TiUIOptionDialogProxy::setTitle(Ti::TiValue value)
{
	_dialog->setTitle(value.toString());
}
void TiUIOptionDialogProxy::setTitleid(Ti::TiValue)
{
}

Ti::TiValue TiUIOptionDialogProxy::getAndroidView()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIOptionDialogProxy::getTizenView()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIOptionDialogProxy::getCancel()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIOptionDialogProxy::getDestructive()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIOptionDialogProxy::getOptions()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIOptionDialogProxy::getPersistent()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIOptionDialogProxy::getSelectedIndex()
{
	Ti::TiValue val;
	val.setNumber(_selectedIndex);
	return val;
}
Ti::TiValue TiUIOptionDialogProxy::getTitle()
{
	Ti::TiValue val;
	val.setString(_dialog->title());
	return val;
}
Ti::TiValue TiUIOptionDialogProxy::getTitleid()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

Ti::TiValue TiUIOptionDialogProxy::show(Ti::TiValue)
{
	clearWeak();
	_dialog->show();
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIOptionDialogProxy::hide(Ti::TiValue)
{
	makeWeak();
	_dialog->cancel();
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

TiUIOptionDialogEventHandler::TiUIOptionDialogEventHandler(TiUIOptionDialogProxy* proxy) :
		_proxy(proxy)
{
}
TiUIOptionDialogEventHandler::~TiUIOptionDialogEventHandler()
{
}
void TiUIOptionDialogEventHandler::clicked(bb::system::SystemUiResult::Type)
{
	bb::system::SystemListDialog* dialog = static_cast<bb::system::SystemListDialog*>(sender());
	bb::system::SystemUiButton* selectedButton = dialog->buttonSelection();
	if (selectedButton == NULL)
	{
		return;
	}
	int index = -1;
	if(dialog->selectedIndices().length() > 0)
	{
		index = dialog->selectedIndices().at(0);
	}
	Ti::TiEventParameters eventParams;
	eventParams.addParam("index", index);
	eventParams.addParam("cancel", selectedButton == dialog->cancelButton());
	_proxy->fireEvent(Ti::TiConstants::EventClick, eventParams);
	_proxy->makeWeak();
}

}
