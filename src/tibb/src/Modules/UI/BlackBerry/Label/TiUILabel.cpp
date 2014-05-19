/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUILabel.h"
#include <bb/cascades/Label>
namespace TiUI {

TiUILabel::TiUILabel(Ti::TiViewProxy* _proxy) : Ti::TiView(_proxy)
{
	_label = new bb::cascades::Label();
	_label->setMultiline(true);
	setChildControl(_label);
}

TiUILabel::~TiUILabel()
{

}
bool TiUILabel::ingoreWidth()
{
	return false;
}
bool TiUILabel::ingoreHeight()
{
	return false;
}
QString TiUILabel::defaultWidth()
{
	return Ti::TiConstants::SizeSIZE;
}
QString TiUILabel::defaultHeight()
{
	return Ti::TiConstants::SizeSIZE;
}

bb::cascades::Label* TiUILabel::getNative()
{
	return _label;
}

}
