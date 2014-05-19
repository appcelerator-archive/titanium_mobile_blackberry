/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include <bb/cascades/Button>
#include <bb/cascades/TapEvent>

#include "UIButton.h"
namespace TiUI {

TiUIButton::TiUIButton(Ti::TiViewProxy* _proxy)
	: Ti::TiView(_proxy)
{
	_button = new bb::cascades::Button();
	QObject::connect(_button, SIGNAL(clicked()), this, SLOT(onClick()));
	setChildControl(_button);
}
bool TiUIButton::ingoreWidth()
{
	return false;
}
bool TiUIButton::ingoreHeight()
{
	return true;
}
QString TiUIButton::defaultWidth()
{
	return Ti::TiConstants::SizeSIZE;
}
QString TiUIButton::defaultHeight()
{
	return Ti::TiConstants::SizeSIZE;
}

void TiUIButton::onTapEvent(bb::cascades::TapEvent*)
{
	// 	disable second click
}

bb::cascades::Button* TiUIButton::getNative()
{
	return _button;
}

void TiUIButton::onClick()
{
	Ti::TiEventParameters params;
	params.addParam("type", "click");
	getProxy()->fireEvent(Ti::TiConstants::EventClick, params);
}

TiUIButton::~TiUIButton()
{
}

}
