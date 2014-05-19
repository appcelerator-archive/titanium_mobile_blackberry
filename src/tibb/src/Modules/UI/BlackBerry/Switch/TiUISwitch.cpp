/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUISwitch.h"

namespace TiUI {

TiUISwitch::TiUISwitch(Ti::TiViewProxy* proxy) : Ti::TiView(proxy)
{
	_switch = new bb::cascades::ToggleButton();
	setChildControl(_switch);
	QObject::connect(_switch, SIGNAL(checkedChanged(bool)), this, SLOT(onChange(bool)));
}

TiUISwitch::~TiUISwitch()
{

}
bool TiUISwitch::ingoreWidth()
{
	return false;
}
bool TiUISwitch::ingoreHeight()
{
	return true;
}
QString TiUISwitch::defaultWidth()
{
	return Ti::TiConstants::SizeSIZE;
}
QString TiUISwitch::defaultHeight()
{
	return Ti::TiConstants::SizeSIZE;
}

void TiUISwitch::onChange(bool state)
{
	Ti::TiEventParameters eventParams;
	eventParams.addParam("value", state);
	getProxy()->fireEvent(Ti::TiConstants::EventChange, eventParams);
}

void TiUISwitch::setChecked(bool checked)
{
	_switch->setChecked(checked);
}

void TiUISwitch::setEnabled(bool enabled)
{
	_switch->setEnabled(enabled);
}

bool TiUISwitch::isChecked()
{
	return _switch->isChecked();
}
bool TiUISwitch::isEnabled()
{
	return _switch->isEnabled();
}

} /* namespace TiUI */
