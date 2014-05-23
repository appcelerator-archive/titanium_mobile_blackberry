/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITextFieldProxy.h"
#include "TiUITextField.h"

#include <bb/cascades/TextField>
#include <bb/cascades/TextFieldInputMode>

namespace TiUI {

TiUITextFieldProxy::TiUITextFieldProxy(const char* name) : TiUITextWidgetProxy(name)
{

	createPropertySetterGetter("autoLink", _setAutoLink,  _getAutoLink);
	createPropertySetterGetter("clearButtonMode", _setClearButtonMode,  _getClearButtonMode);
	createPropertySetterGetter("leftButton", _setLeftButton,  _getLeftButton);
	createPropertySetterGetter("leftButtonMode", _setLeftButtonMode,  _getLeftButtonMode);
	createPropertySetterGetter("leftButtonPadding", _setLeftButtonPadding,  _getLeftButtonPadding);
	createPropertySetterGetter("minimumFontSize", _setMinimumFontSize,  _getMinimumFontSize);
	createPropertySetterGetter("paddingLeft", _setPaddingLeft,  _getPaddingLeft);
	createPropertySetterGetter("paddingRight", _setPaddingRight,  _getPaddingRight);
	createPropertySetterGetter("passwordMask", _setPasswordMask,  _getPasswordMask);
	createPropertySetterGetter("rightButton", _setRightButton,  _getRightButton);
	createPropertySetterGetter("rightButtonMode", _setRightButtonMode,  _getRightButtonMode);
	createPropertySetterGetter("rightButtonPadding", _setRightButtonPadding,  _getRightButtonPadding);

	setView(new TiUITextField(this));
	setIsTextfield(true);

	_nativeTextField = static_cast<bb::cascades::TextField*>(getNativeTextControl());
}

TiUITextFieldProxy::~TiUITextFieldProxy()
{
}

void TiUITextFieldProxy::setBorderStyle(Ti::TiValue)
{
}
void TiUITextFieldProxy::setClearButtonMode(Ti::TiValue)
{
}
void TiUITextFieldProxy::setLeftButton(Ti::TiValue)
{
}
void TiUITextFieldProxy::setLeftButtonMode(Ti::TiValue)
{
}
void TiUITextFieldProxy::setLeftButtonPadding(Ti::TiValue)
{
}
void TiUITextFieldProxy::setMinimumFontSize(Ti::TiValue)
{
}
void TiUITextFieldProxy::setPaddingLeft(Ti::TiValue)
{
}
void TiUITextFieldProxy::setPaddingRight(Ti::TiValue)
{
}
void TiUITextFieldProxy::setPasswordMask(Ti::TiValue val)
{
	if(val.toBool())
	{
		_nativeTextField->setInputMode(bb::cascades::TextFieldInputMode::Password);
	}
	else
	{
		_nativeTextField->setInputMode(bb::cascades::TextFieldInputMode::Default);
	}
}
void TiUITextFieldProxy::setRightButton(Ti::TiValue)
{
}
void TiUITextFieldProxy::setRightButtonMode(Ti::TiValue)
{
}
void TiUITextFieldProxy::setRightButtonPadding(Ti::TiValue)
{
}

Ti::TiValue TiUITextFieldProxy::getBorderStyle()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextFieldProxy::getClearButtonMode()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

Ti::TiValue TiUITextFieldProxy::getLeftButton()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextFieldProxy::getLeftButtonMode()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextFieldProxy::getLeftButtonPadding()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextFieldProxy::getMinimumFontSize()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextFieldProxy::getPaddingLeft()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextFieldProxy::getPaddingRight()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextFieldProxy::getPasswordMask()
{
	Ti::TiValue val;
	val.setBool(_nativeTextField->inputMode() == bb::cascades::TextFieldInputMode::Password);
	return val;
}
Ti::TiValue TiUITextFieldProxy::getRightButton()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextFieldProxy::getRightButtonMode()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextFieldProxy::getRightButtonPadding()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

}
