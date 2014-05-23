/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITextWidget.h"

namespace TiUI {

TiUITextWidget::TiUITextWidget(Ti::TiViewProxy*proxy) :
		Ti::TiView(proxy),
		_textControl(NULL)
{

}

TiUITextWidget::~TiUITextWidget() {
	// TODO Auto-generated destructor stub
}

void TiUITextWidget::setTextControl(bb::cascades::AbstractTextControl* textControl)
{
	_textControl = textControl;
//	QObject::connect(_textControl, SIGNAL(textChanged(QString)), this, SLOT(onChange(QString)));
	QObject::connect(_textControl, SIGNAL(focusedChanged(bool)), this, SLOT(onFocusChange(bool)));
	QObject::connect(_textControl, SIGNAL(textChanging(const QString)), this, SLOT(onChanging(const QString)));
	setChildControl(_textControl);
}

bb::cascades::AbstractTextControl *TiUITextWidget::getTextControl()
{
	return _textControl;
}
void TiUITextWidget::onChanging(const QString str)
{
	Ti::TiEventParameters eventParams;
	eventParams.addParam("value", str);
	getProxy()->fireEvent(Ti::TiConstants::EventChange, eventParams);
}
// Not applicable here
void TiUITextWidget::onChange(QString str)
{
	Ti::TiEventParameters eventParams;
	eventParams.addParam("value", str);
	getProxy()->fireEvent(Ti::TiConstants::EventChange, eventParams);
}

void TiUITextWidget::onSubmitted(bb::cascades::AbstractTextControl *)
{
	Ti::TiEventParameters eventParams;
	eventParams.addParam("value", _textControl->text());
	getProxy()->fireEvent(Ti::TiConstants::EventReturn, eventParams);
}
void TiUITextWidget::onFocusChange(bool focus)
{
	Ti::TiEventParameters eventParams;
	eventParams.addParam("value", _textControl->text());
	QString event;
	if(focus)
	{
		event = Ti::TiConstants::EventFocus;
	}
	else
	{
		event = Ti::TiConstants::EventBlur;
	}
	getProxy()->fireEvent(event, eventParams);
}


} /* namespace TiUI */
