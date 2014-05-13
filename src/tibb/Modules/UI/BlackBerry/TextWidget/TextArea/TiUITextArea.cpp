/*
 * TiUITextArea.cpp
 *
 *  Created on: Sunday, September 15, 2013
 *      Author: penrique
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
