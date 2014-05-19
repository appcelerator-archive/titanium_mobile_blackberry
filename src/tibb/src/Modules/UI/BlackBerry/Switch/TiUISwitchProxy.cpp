/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUISwitchProxy.h"

namespace TiUI {

TiUISwitchProxy::TiUISwitchProxy(const char* name) : Ti::TiViewProxy(name)
{
	_switch = new TiUISwitch(this);
	setView(_switch);

	createPropertySetterGetter("enabled", _setEnabled, _getEnabled);
	createPropertySetterGetter("color", _setColor, _getColor);
	createPropertySetterGetter("font", _setFont, _getFont);
	createPropertySetterGetter("style", _setStyle, _getStyle);
	createPropertySetterGetter("textAlign", _setTextAlign, _getTextAlign);
	createPropertySetterGetter("title", _setTitle, _getTitle);
	createPropertySetterGetter("titleOff", _setTitleOff, _getTitleOff);
	createPropertySetterGetter("titleOn", _setTitleOn, _getTitleOn);
	createPropertySetterGetter("value", _setValue, _getValue);
	createPropertySetterGetter("verticalAlign", _setVerticalAlign, _getVerticalAlign);

}

TiUISwitchProxy::~TiUISwitchProxy() {
	// TODO Auto-generated destructor stub
}

// Disable width and height, they're internally hard coded
void TiUISwitchProxy::setWidth(Ti::TiValue)
{
}
void TiUISwitchProxy::setHeight(Ti::TiValue)
{
}

void TiUISwitchProxy::setEnabled(Ti::TiValue val)
{
	_switch->setEnabled(val.toBool());
}
void TiUISwitchProxy::setColor(Ti::TiValue)
{

}
void TiUISwitchProxy::setFont(Ti::TiValue)
{

}
void TiUISwitchProxy::setStyle(Ti::TiValue)
{

}
void TiUISwitchProxy::setTextAlign(Ti::TiValue)
{

}
void TiUISwitchProxy::setTitle(Ti::TiValue)
{

}
void TiUISwitchProxy::setTitleOff(Ti::TiValue)
{

}
void TiUISwitchProxy::setTitleOn(Ti::TiValue)
{

}
void TiUISwitchProxy::setValue(Ti::TiValue value)
{
	_switch->setChecked(value.toBool());
}
void TiUISwitchProxy::setVerticalAlign(Ti::TiValue value)
{

}

Ti::TiValue TiUISwitchProxy::getEnabled()
{
	Ti::TiValue val;
	val.setBool(_switch->isEnabled());
	return val;
}
Ti::TiValue TiUISwitchProxy::getColor()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISwitchProxy::getFont()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISwitchProxy::getStyle()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISwitchProxy::getTextAlign()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISwitchProxy::getTitle()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISwitchProxy::getTitleOff()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISwitchProxy::getTitleOn()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISwitchProxy::getValue()
{
	Ti::TiValue val;
	val.setBool(_switch->isChecked());
	return val;
}
Ti::TiValue TiUISwitchProxy::getVerticalAlign()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

} /* namespace TiUI */
