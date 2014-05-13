/*
 * TiUITextField.cpp
 *
 *  Created on: Friday, September 13, 2013
 *      Author: penrique
 */

#include "TiUITextField.h"
#include <bb/cascades/SubmitKey>

namespace TiUI {

TiUITextField::TiUITextField(Ti::TiViewProxy* proxy) : TiUITextWidget(proxy)
{
	_textField = new bb::cascades::TextField();
	QObject::connect(_textField->input(), SIGNAL(submitted(bb::cascades::AbstractTextControl *)), this, SLOT(onSubmitted(bb::cascades::AbstractTextControl *)));
	setTextControl(_textField);
}

TiUITextField::~TiUITextField()
{
}

bool TiUITextField::ingoreWidth()
{
	return false;
}
bool TiUITextField::ingoreHeight()
{
	return true;
}
QString TiUITextField::defaultWidth()
{
	return Ti::TiConstants::SizeFILL;
}
QString TiUITextField::defaultHeight()
{
	return Ti::TiConstants::SizeSIZE;
}

}
