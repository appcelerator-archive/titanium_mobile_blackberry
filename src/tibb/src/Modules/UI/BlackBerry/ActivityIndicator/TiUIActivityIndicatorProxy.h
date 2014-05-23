/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUIACTIVITYINDICATORPROXY_H_
#define TI_TIUIACTIVITYINDICATORPROXY_H_

#include <TiCore.h>
#include <bb/cascades/ActivityIndicator>

namespace TiUI {
class TiUIActivityIndicator;
class TiUIActivityIndicatorProxy : public Ti::TiViewProxy
{
public:
	CREATE_PROXY(TiUIActivityIndicatorProxy)
	TiUIActivityIndicatorProxy(const char*);
	virtual ~TiUIActivityIndicatorProxy();

	TI_CREATE_SETTER_GETTER(TiUIActivityIndicatorProxy, setColor, getColor)
	TI_CREATE_SETTER_GETTER(TiUIActivityIndicatorProxy, setFont, getFont)
	TI_CREATE_SETTER_GETTER(TiUIActivityIndicatorProxy, setMessage, getMessage)
	TI_CREATE_SETTER_GETTER(TiUIActivityIndicatorProxy, setMessageid, getMessageid)
	TI_CREATE_SETTER_GETTER(TiUIActivityIndicatorProxy, setStyle, getStyle)
	TI_CREATE_SETTER_GETTER(TiUIActivityIndicatorProxy, setIndicatorColor, getIndicatorColor)
	TI_CREATE_SETTER_GETTER(TiUIActivityIndicatorProxy, setIndicatorDiameter, getIndicatorDiameter)

	virtual Ti::TiValue show(Ti::TiValue);
	virtual Ti::TiValue hide(Ti::TiValue);

private:
	bb::cascades::ActivityIndicator* _nativeIndicator;
	TiUIActivityIndicator* _activityIndicator;
};

}
#endif /* TIUIACTIVITYINDICATORPROXY_H_ */
