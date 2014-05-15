/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUILabelProxy.h"
#include "TiUILabel.h"
#include "../TiUIBlackberryModule.h"
#include <bb/cascades/TextAlign>
namespace TiUI {

TiUILabelProxy::TiUILabelProxy(const char* name) : Ti::TiViewProxy(name)
{
	createPropertySetterGetter("autoLink", _setAutoLink,  _getAutoLink);
	createPropertySetterGetter("backgroundPaddingBottom", _setBackgroundPaddingBottom,  _getBackgroundPaddingBottom);
	createPropertySetterGetter("backgroundPaddingLeft", _setBackgroundPaddingLeft,  _getBackgroundPaddingLeft);
	createPropertySetterGetter("backgroundPaddingRight", _setBackgroundPaddingRight,  _getBackgroundPaddingRight);
	createPropertySetterGetter("backgroundPaddingTop", _setBackgroundPaddingTop,  _getBackgroundPaddingTop);
	createPropertySetterGetter("color", _setColor,  _getColor);
	createPropertySetterGetter("ellipsize", _setEllipsize,  _getEllipsize);
	createPropertySetterGetter("font", _setFont,  _getFont);
	createPropertySetterGetter("highlightedColor", _setHighlightedColor,  _getHighlightedColor);
	createPropertySetterGetter("html", _setHtml,  _getHtml);
	createPropertySetterGetter("minimumFontSize", _setMinimumFontSize,  _getMinimumFontSize);
	createPropertySetterGetter("shadowColor", _setShadowColor,  _getShadowColor);
	createPropertySetterGetter("shadowOffset", _setShadowOffset,  _getShadowOffset);
	createPropertySetterGetter("text", _setText,  _getText);
	createPropertySetterGetter("textAlign", _setTextAlign,  _getTextAlign);
	createPropertySetterGetter("textid", _setTextid,  _getTextid);
	createPropertySetterGetter("wordWrap", _setWordWrap,  _getWordWrap);
	createPropertySetterGetter("verticalAlign", _setVerticalAlign,  _getVerticalAlign);

	_label = new TiUILabel(this);
	_native = _label->getNative();
	setView(_label);

}

TiUILabelProxy::~TiUILabelProxy()
{
	qDebug() << "[LABEL] Delete" << getProxyName();
}

void TiUILabelProxy::setAutoLink(Ti::TiValue)
{
}
void TiUILabelProxy::setBackgroundPaddingBottom(Ti::TiValue)
{
}
void TiUILabelProxy::setBackgroundPaddingLeft(Ti::TiValue)
{
}
void TiUILabelProxy::setBackgroundPaddingRight(Ti::TiValue)
{
}
void TiUILabelProxy::setBackgroundPaddingTop(Ti::TiValue)
{
}
void TiUILabelProxy::setColor(Ti::TiValue value)
{
	_native->textStyle()->setColor(value.toColor());
}
void TiUILabelProxy::setEllipsize(Ti::TiValue)
{
}
void TiUILabelProxy::setFont(Ti::TiValue value)
{
	Ti::TiHelper::applyFontToText(value, _native);
}
void TiUILabelProxy::setHighlightedColor(Ti::TiValue)
{
}
void TiUILabelProxy::setHtml(Ti::TiValue value)
{
	if(value.toBool())
		_native->setTextFormat(bb::cascades::TextFormat::Html);
	else
		_native->setTextFormat(bb::cascades::TextFormat::Auto);
}
void TiUILabelProxy::setMinimumFontSize(Ti::TiValue)
{
}
void TiUILabelProxy::setShadowColor(Ti::TiValue)
{
}
void TiUILabelProxy::setShadowOffset(Ti::TiValue)
{
}
void TiUILabelProxy::setText(Ti::TiValue value)
{
	_native->setText(value.toString());
}
void TiUILabelProxy::setTextAlign(Ti::TiValue val)
{
	bb::cascades::TextAlign::Type type = bb::cascades::TextAlign::Default;
	if(val.isString())
	{
		QString alignment = val.toString();
		if(alignment == "center")
			type = bb::cascades::TextAlign::Center;
		if(alignment == "left")
			type = bb::cascades::TextAlign::Left;
		if(alignment == "right")
			type = bb::cascades::TextAlign::Right;
	}
	else
	{
		type = (bb::cascades::TextAlign::Type)val.toNumber();
	}

	_native->textStyle()->setTextAlign(type);
}
void TiUILabelProxy::setTextid(Ti::TiValue)
{
}
void TiUILabelProxy::setWordWrap(Ti::TiValue val)
{
	_native->setMultiline(val.toBool());
}
void TiUILabelProxy::setVerticalAlign(Ti::TiValue)
{
}

Ti::TiValue TiUILabelProxy::getAutoLink()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUILabelProxy::getBackgroundPaddingBottom()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUILabelProxy::getBackgroundPaddingLeft()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUILabelProxy::getBackgroundPaddingRight()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUILabelProxy::getBackgroundPaddingTop()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUILabelProxy::getColor()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUILabelProxy::getEllipsize()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUILabelProxy::getFont()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUILabelProxy::getHighlightedColor()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUILabelProxy::getHtml()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUILabelProxy::getMinimumFontSize()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUILabelProxy::getShadowColor()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUILabelProxy::getShadowOffset()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUILabelProxy::getText()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUILabelProxy::getTextAlign()
{
	Ti::TiValue val;
	bb::cascades::TextAlign::Type type = _native->textStyle()->textAlign();
	val.setNumber((double)type);
	return val;
}
Ti::TiValue TiUILabelProxy::getTextid()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUILabelProxy::getWordWrap()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUILabelProxy::getVerticalAlign()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

}
