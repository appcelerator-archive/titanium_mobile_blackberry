/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIImageButton.h"

namespace TiUI {

TiUIImageButton::TiUIImageButton(Ti::TiViewProxy* _proxy)
	: Ti::TiView(_proxy)
{
	_button = new bb::cascades::ImageButton();
	QObject::connect(_button, SIGNAL(clicked()), this, SLOT(onClick()));
	setChildControl(_button);
}
bool TiUIImageButton::ingoreWidth()
{
	return false;
}
bool TiUIImageButton::ingoreHeight()
{
	return false;
}
QString TiUIImageButton::defaultWidth()
{
	return Ti::TiConstants::SizeSIZE;
}
QString TiUIImageButton::defaultHeight()
{
	return Ti::TiConstants::SizeSIZE;
}

void TiUIImageButton::onTapEvent(bb::cascades::TapEvent*)
{
	// 	disable second click
}

bb::cascades::ImageButton* TiUIImageButton::getNative()
{
	return _button;
}

void TiUIImageButton::onClick()
{
	Ti::TiEventParameters params;
	params.addParam("type", Ti::TiConstants::EventClick);
	getProxy()->fireEvent(Ti::TiConstants::EventClick, params);
}

TiUIImageButton::~TiUIImageButton()
{
}
} /* namespace TiUI */
