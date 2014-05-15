/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITextArea.h"

namespace TiUI {

TiUITextArea::TiUITextArea(Ti::TiViewProxy* proxy) : TiUITextWidget(proxy)
{
	_textArea = new bb::cascades::TextArea();
	QObject::connect(_textArea->input(), SIGNAL(submitted(bb::cascades::AbstractTextControl *)), this, SLOT(onSubmitted(bb::cascades::AbstractTextControl *)));
	setTextControl(_textArea);
}

TiUITextArea::~TiUITextArea()
{
}

bool TiUITextArea::ingoreWidth()
{
	return false;
}
bool TiUITextArea::ingoreHeight()
{
	return false;
}
QString TiUITextArea::defaultWidth()
{
	return Ti::TiConstants::SizeFILL;
}
QString TiUITextArea::defaultHeight()
{
	return Ti::TiConstants::SizeSIZE;
}

}
