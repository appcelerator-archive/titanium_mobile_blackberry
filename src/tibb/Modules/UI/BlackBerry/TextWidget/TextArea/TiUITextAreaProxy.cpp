/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITextAreaProxy.h"
#include "TiUITextArea.h"

namespace TiUI {

TiUITextAreaProxy::TiUITextAreaProxy(const char* name) : TiUITextWidgetProxy(name)
{

	createPropertySetterGetter("scrollsToTop", _setScrollsToTop,  _getScrollsToTop);
	createPropertySetterGetter("scrollable", _setScrollable,  _getScrollable);

	setView(new TiUITextArea(this));
	setIsTextArea(true);
	_nativeTextArea = static_cast<bb::cascades::TextArea*>(getNativeTextControl());
}

TiUITextAreaProxy::~TiUITextAreaProxy()
{
}
void TiUITextAreaProxy::setScrollsToTop(Ti::TiValue)
{
}
void TiUITextAreaProxy::setScrollable(Ti::TiValue)
{
}
Ti::TiValue TiUITextAreaProxy::getScrollsToTop()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITextAreaProxy::getScrollable()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

}
