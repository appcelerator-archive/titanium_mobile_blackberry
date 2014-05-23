/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
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
