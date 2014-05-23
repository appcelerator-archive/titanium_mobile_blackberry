/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUITEXTAREA_H_
#define TI_TIUITEXTAREA_H_

#include <TiCore.h>
#include "../TiUITextWidget.h"
#include <bb/cascades/TextArea>
#include <bb/cascades/AbstractTextControl>

namespace TiUI {

class TiUITextArea : public TiUITextWidget
{
	Q_OBJECT;
public:
	TiUITextArea(Ti::TiViewProxy*);
	virtual ~TiUITextArea();

	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();
private:
	bb::cascades::TextArea *_textArea;

};
}
#endif /* TIUITEXTAREA_H_ */
