/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUITEXTFIELD_H_
#define TI_TIUITEXTFIELD_H_

#include <TiCore.h>
#include "../TiUITextWidget.h"
#include <bb/cascades/TextField>
#include <bb/cascades/AbstractTextControl>

namespace TiUI {
class TiUITextField : public TiUITextWidget
{
	Q_OBJECT;
public:
	TiUITextField(Ti::TiViewProxy*);
	virtual ~TiUITextField();
	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();
private:
	bb::cascades::TextField *_textField;
};
}
#endif /* TIUITEXTFIELD_H_ */
