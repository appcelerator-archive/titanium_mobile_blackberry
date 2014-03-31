/*
 * TiUIButton.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: penrique
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
