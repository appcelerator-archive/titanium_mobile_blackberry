/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUISlider.h"

namespace TiUI {

TiUISlider::TiUISlider(Ti::TiViewProxy* proxy) : Ti::TiView(proxy)
{
	_slider = new bb::cascades::Slider();
//	QObject::connect(_slider, SIGNAL(valueChanged(float)), this, SLOT(onChange(float)));
	QObject::connect(_slider, SIGNAL(immediateValueChanged(float)), this, SLOT(onChanging(float)));

	setChildControl(_slider);
}

TiUISlider::~TiUISlider()
{
}

bool TiUISlider::ingoreWidth()
{
	return false;
}
bool TiUISlider::ingoreHeight()
{
	return true;
}
QString TiUISlider::defaultWidth()
{
	return Ti::TiConstants::SizeFILL;
}
QString TiUISlider::defaultHeight()
{
	return Ti::TiConstants::SizeSIZE;
}

bb::cascades::Slider* TiUISlider::getNative()
{
	return _slider;
}

void TiUISlider::onChange(float value)
{
	// not called for now
	Ti::TiEventParameters eventParams;
	eventParams.addParam("type", Ti::TiConstants::EventChange);
	eventParams.addParam("value", value);
	getProxy()->fireEvent(Ti::TiConstants::EventChange, eventParams);
}

void TiUISlider::onChanging(float value)
{
	Ti::TiEventParameters eventParams;
	eventParams.addParam("type", Ti::TiConstants::EventChange);
	eventParams.addParam("value", value);
	getProxy()->fireEvent(Ti::TiConstants::EventChange, eventParams);
}

}
