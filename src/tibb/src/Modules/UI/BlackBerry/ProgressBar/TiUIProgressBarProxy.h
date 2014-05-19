/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUIPROGRESSBARPROXY_H_
#define TI_TIUIPROGRESSBARPROXY_H_

#include <TiCore.h>

namespace TiUI {
class TiUIProgressBar;
class TiUIProgressBarProxy : public Ti::TiViewProxy
{
public:
	CREATE_PROXY(TiUIProgressBarProxy)
	TiUIProgressBarProxy(const char*);
	virtual ~TiUIProgressBarProxy();

	TI_CREATE_SETTER_GETTER(TiUIProgressBarProxy, setColor, getColor)
	TI_CREATE_SETTER_GETTER(TiUIProgressBarProxy, setFont, getFont)
	TI_CREATE_SETTER_GETTER(TiUIProgressBarProxy, setMax, getMax)
	TI_CREATE_SETTER_GETTER(TiUIProgressBarProxy, setMessage, getMessage)
	TI_CREATE_SETTER_GETTER(TiUIProgressBarProxy, setMin, getMin)
	TI_CREATE_SETTER_GETTER(TiUIProgressBarProxy, setStyle, getStyle)
	TI_CREATE_SETTER_GETTER(TiUIProgressBarProxy, setValue, getValue)

private:
	TiUIProgressBar* _progressBar;
};
}
#endif /* TIUIPROGRESSBARPROXY_H_ */
