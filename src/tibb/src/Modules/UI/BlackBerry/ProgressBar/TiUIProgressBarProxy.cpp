/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIProgressBarProxy.h"
#include "TiUIProgressBar.h"

namespace TiUI {

TiUIProgressBarProxy::TiUIProgressBarProxy(const char* name) : Ti::TiViewProxy(name)
{
	createPropertySetterGetter("color", _setColor,  _getColor);
	createPropertySetterGetter("font", _setFont,  _getFont);
	createPropertySetterGetter("max", _setMax,  _getMax);
	createPropertySetterGetter("message", _setMessage,  _getMessage);
	createPropertySetterGetter("min", _setMin,  _getMin);
	createPropertySetterGetter("style", _setStyle,  _getStyle);
	createPropertySetterGetter("value", _setValue,  _getValue);
	_progressBar = new TiUIProgressBar(this);
	setView(_progressBar);
}

TiUIProgressBarProxy::~TiUIProgressBarProxy()
{
}

void TiUIProgressBarProxy::setColor(Ti::TiValue)
{
	// Not supported
}
void TiUIProgressBarProxy::setFont(Ti::TiValue)
{
	// Not supported
}
void TiUIProgressBarProxy::setMax(Ti::TiValue val)
{
	_progressBar->setMaxValue((float)val.toNumber());
}
void TiUIProgressBarProxy::setMessage(Ti::TiValue)
{
	// Not supported
}
void TiUIProgressBarProxy::setMin(Ti::TiValue val)
{
	_progressBar->setMinValue((float)val.toNumber());
}
void TiUIProgressBarProxy::setStyle(Ti::TiValue)
{
}
void TiUIProgressBarProxy::setValue(Ti::TiValue val)
{
	_progressBar->setValue((float)val.toNumber());
}

Ti::TiValue TiUIProgressBarProxy::getColor()
{
	// Not supported
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIProgressBarProxy::getFont()
{
	// Not supported
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIProgressBarProxy::getMax()
{
	Ti::TiValue val;
	val.setNumber(_progressBar->getMaxValue());
	return val;
}
Ti::TiValue TiUIProgressBarProxy::getMessage()
{
	// Not supported
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIProgressBarProxy::getMin()
{
	// Not supported
	Ti::TiValue val;
	val.setNumber(_progressBar->getMinValue());
	return val;
}
Ti::TiValue TiUIProgressBarProxy::getStyle()
{
	// Not supported
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIProgressBarProxy::getValue()
{
	Ti::TiValue val;
	val.setNumber(_progressBar->getValue());
	return val;
}

}
