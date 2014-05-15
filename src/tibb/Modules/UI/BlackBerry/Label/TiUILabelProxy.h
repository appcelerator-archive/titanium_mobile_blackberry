/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUILABELPROXY_H_
#define TI_TIUILABELPROXY_H_

#include "TiCore.h"
#include <bb/cascades/Label>

namespace TiUI
{
class TiUILabel;
class TiUILabelProxy: public Ti::TiViewProxy
{
public:
	CREATE_PROXY(TiUILabelProxy)
	TiUILabelProxy(const char*);
	virtual ~TiUILabelProxy();

	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setAutoLink, getAutoLink)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setBackgroundPaddingBottom, getBackgroundPaddingBottom)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setBackgroundPaddingLeft, getBackgroundPaddingLeft)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setBackgroundPaddingRight, getBackgroundPaddingRight)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setBackgroundPaddingTop, getBackgroundPaddingTop)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setColor, getColor)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setEllipsize, getEllipsize)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setFont, getFont)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setHighlightedColor, getHighlightedColor)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setHtml, getHtml)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setMinimumFontSize, getMinimumFontSize)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setShadowColor, getShadowColor)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setShadowOffset, getShadowOffset)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setText, getText)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setTextAlign, getTextAlign)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setTextid, getTextid)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setWordWrap, getWordWrap)
	TI_CREATE_SETTER_GETTER(TiUILabelProxy, setVerticalAlign, getVerticalAlign)

private:
	TiUILabel* _label;
	bb::cascades::Label* _native;
};
}
#endif /* TIUILABELPROXY_H_ */
