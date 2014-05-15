/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIActivityIndicatorProxy.h"
#include "TiUIActivityIndicator.h"

namespace TiUI {

TiUIActivityIndicatorProxy::TiUIActivityIndicatorProxy(const char* name) : Ti::TiViewProxy(name)
{

	createPropertySetterGetter("color", _setColor,  _getColor);
	createPropertySetterGetter("font", _setFont,  _getFont);
	createPropertySetterGetter("message", _setMessage,  _getMessage);
	createPropertySetterGetter("messageid", _setMessageid,  _getMessageid);
	createPropertySetterGetter("style", _setStyle,  _getStyle);
	createPropertySetterGetter("indicatorColor", _setIndicatorColor,  _getIndicatorColor);
	createPropertySetterGetter("indicatorDiameter", _setIndicatorDiameter,  _getIndicatorDiameter);

	_activityIndicator = new TiUIActivityIndicator(this);
	_nativeIndicator = _activityIndicator->getNativeIndicator();
	setView(_activityIndicator);
}

TiUIActivityIndicatorProxy::~TiUIActivityIndicatorProxy()
{
}

TI_GETTER_DEFER(TiUIActivityIndicatorProxy, getColor)
void TiUIActivityIndicatorProxy::setColor(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIActivityIndicatorProxy, getFont)
void TiUIActivityIndicatorProxy::setFont(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIActivityIndicatorProxy, getMessage)
void TiUIActivityIndicatorProxy::setMessage(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIActivityIndicatorProxy, getMessageid)
void TiUIActivityIndicatorProxy::setMessageid(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIActivityIndicatorProxy, getStyle)
void TiUIActivityIndicatorProxy::setStyle(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIActivityIndicatorProxy, getIndicatorColor)
void TiUIActivityIndicatorProxy::setIndicatorColor(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIActivityIndicatorProxy, getIndicatorDiameter)
void TiUIActivityIndicatorProxy::setIndicatorDiameter(Ti::TiValue)
{
}

Ti::TiValue TiUIActivityIndicatorProxy::show(Ti::TiValue value)
{
	_nativeIndicator->start();
	return Ti::TiViewProxy::show(value);
}

Ti::TiValue TiUIActivityIndicatorProxy::hide(Ti::TiValue value)
{
	_nativeIndicator->stop();
	return Ti::TiViewProxy::hide(value);
}

}
