/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIActivityIndicator.h"
#include <bb/cascades/Container>

namespace TiUI {

TiUIActivityIndicator::TiUIActivityIndicator(Ti::TiViewProxy* proxy) : Ti::TiView(proxy)
{
	_indicator = new bb::cascades::ActivityIndicator(this);
	setChildControl(_indicator);
}

TiUIActivityIndicator::~TiUIActivityIndicator()
{
}

bool TiUIActivityIndicator::ingoreWidth()
{
	return false;
}
bool TiUIActivityIndicator::ingoreHeight()
{
	return false;
}
QString TiUIActivityIndicator::defaultWidth()
{
	return Ti::TiConstants::SizeSIZE;
}
QString TiUIActivityIndicator::defaultHeight()
{
	return Ti::TiConstants::SizeSIZE;
}
bb::cascades::ActivityIndicator* TiUIActivityIndicator::getNativeIndicator()
{
	return _indicator;
}

}
