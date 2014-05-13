/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIProgressBar.h"

namespace TiUI {

TiUIProgressBar::TiUIProgressBar(Ti::TiViewProxy* proxy) : Ti::TiView(proxy)
{
	_progressBar = new bb::cascades::ProgressIndicator();
	_progressBar->setFromValue(0);
	_progressBar->setToValue(1);
	setChildControl(_progressBar);
}

TiUIProgressBar::~TiUIProgressBar()
{
}

bool TiUIProgressBar::ingoreWidth()
{
	return false;
}
bool TiUIProgressBar::ingoreHeight()
{
	return true;
}
QString TiUIProgressBar::defaultWidth()
{
	return Ti::TiConstants::SizeFILL;
}
QString TiUIProgressBar::defaultHeight()
{
	return Ti::TiConstants::SizeSIZE;
}

bb::cascades::ProgressIndicator* TiUIProgressBar::getNative()
{
	return _progressBar;
}

void TiUIProgressBar::setMinValue(float val)
{
	_progressBar->setFromValue(val);
}

void TiUIProgressBar::setMaxValue(float val)
{
	_progressBar->setToValue(val);
}

void TiUIProgressBar::setValue(float val)
{
	_progressBar->setValue(val);
}

float TiUIProgressBar::getMinValue()
{
	return _progressBar->fromValue();
}

float TiUIProgressBar::getMaxValue()
{
	return _progressBar->toValue();
}

float TiUIProgressBar::getValue()
{
	return _progressBar->value();
}

}
