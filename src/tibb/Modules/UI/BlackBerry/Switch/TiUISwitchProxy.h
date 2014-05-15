/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUISWITCHPROXY_H_
#define TI_TIUISWITCHPROXY_H_

#include "TiCore.h"
#include "TiUISwitch.h"

namespace TiUI {

class TiUISwitchProxy : public Ti::TiViewProxy
{
public:
	CREATE_PROXY(TiUISwitchProxy);
	TiUISwitchProxy(const char*);
	virtual ~TiUISwitchProxy();
	virtual void setWidth(Ti::TiValue);
	virtual void setHeight(Ti::TiValue);

	void setEnabled(Ti::TiValue);
	void setColor(Ti::TiValue);
	void setFont(Ti::TiValue);
	void setStyle(Ti::TiValue);
	void setTextAlign(Ti::TiValue);
	void setTitle(Ti::TiValue);
	void setTitleOff(Ti::TiValue);
	void setTitleOn(Ti::TiValue);
	void setValue(Ti::TiValue);
	void setVerticalAlign(Ti::TiValue);

	Ti::TiValue getEnabled();
	Ti::TiValue getColor();
	Ti::TiValue getFont();
	Ti::TiValue getStyle();
	Ti::TiValue getTextAlign();
	Ti::TiValue getTitle();
	Ti::TiValue getTitleOff();
	Ti::TiValue getTitleOn();
	Ti::TiValue getValue();
	Ti::TiValue getVerticalAlign();


	EXPOSE_SETTER(TiUISwitchProxy, setStyle)
	EXPOSE_SETTER(TiUISwitchProxy, setTextAlign)
	EXPOSE_SETTER(TiUISwitchProxy, setTitle)
	EXPOSE_SETTER(TiUISwitchProxy, setTitleOff)
	EXPOSE_SETTER(TiUISwitchProxy, setTitleOn)
	EXPOSE_SETTER(TiUISwitchProxy, setValue)
	EXPOSE_SETTER(TiUISwitchProxy, setVerticalAlign)
	EXPOSE_SETTER(TiUISwitchProxy, setEnabled)
	EXPOSE_SETTER(TiUISwitchProxy, setColor)
	EXPOSE_SETTER(TiUISwitchProxy, setFont)

	EXPOSE_GETTER(TiUISwitchProxy, getStyle)
	EXPOSE_GETTER(TiUISwitchProxy, getTextAlign)
	EXPOSE_GETTER(TiUISwitchProxy, getTitle)
	EXPOSE_GETTER(TiUISwitchProxy, getTitleOff)
	EXPOSE_GETTER(TiUISwitchProxy, getTitleOn)
	EXPOSE_GETTER(TiUISwitchProxy, getValue)
	EXPOSE_GETTER(TiUISwitchProxy, getVerticalAlign)
	EXPOSE_GETTER(TiUISwitchProxy, getEnabled)
	EXPOSE_GETTER(TiUISwitchProxy, getColor)
	EXPOSE_GETTER(TiUISwitchProxy, getFont)

private:
	TiUISwitch *_switch;
};

} /* namespace TiUI */
#endif /* TIUISWITCHPROXY_H_ */
