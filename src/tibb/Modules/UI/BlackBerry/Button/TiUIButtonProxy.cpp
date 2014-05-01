/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIButtonProxy.h"
#include "UIButton.h"

#include <bb/cascades/Image>

namespace TiUI {

TiUIButtonProxy::TiUIButtonProxy(const char* name) : Ti::TiViewProxy(name)
{
	createPropertySetterGetter("color", _setColor,  _getColor);
	createPropertySetterGetter("font", _setFont,  _getFont);
	createPropertySetterGetter("image", _setImage,  _getImage);
	createPropertySetterGetter("selectedColor", _setSelectedColor,  _getSelectedColor);
	createPropertySetterGetter("style", _setStyle,  _getStyle);
	createPropertySetterGetter("systemButton", _setSystemButton,  _getSystemButton);
	createPropertySetterGetter("textAlign", _setTextAlign,  _getTextAlign);
	createPropertySetterGetter("title", _setTitle, _getTitle);
	createPropertySetterGetter("verticalAlign", _setVerticalAlign,  _getVerticalAlign);
	_button = new TiUIButton(this);
	_native = _button->getNative();
	setView(_button);
}


TiUIButtonProxy::~TiUIButtonProxy() {
}

TI_GETTER_DEFER(TiUIButtonProxy, getColor)
void TiUIButtonProxy::setColor(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIButtonProxy, getFont)
void TiUIButtonProxy::setFont(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIButtonProxy, getImage)
void TiUIButtonProxy::setImage(Ti::TiValue val)
{
	_native->setImage(bb::cascades::Image(QUrl(Ti::TiHelper::getAssetPath(val.toString()))));
}

TI_GETTER_DEFER(TiUIButtonProxy, getSelectedColor)
void TiUIButtonProxy::setSelectedColor(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIButtonProxy, getStyle)
void TiUIButtonProxy::setStyle(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIButtonProxy, getSystemButton)
void TiUIButtonProxy::setSystemButton(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIButtonProxy, getTextAlign)
void TiUIButtonProxy::setTextAlign(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIButtonProxy, getTitle)
void TiUIButtonProxy::setTitle(Ti::TiValue value)
{
	_native->setText(value.toString());
}

TI_GETTER_DEFER(TiUIButtonProxy, getVerticalAlign)
void TiUIButtonProxy::setVerticalAlign(Ti::TiValue)
{
}

}
