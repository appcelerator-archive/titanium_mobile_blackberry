/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUIIMAGEBUTTON_H_
#define TI_TIUIIMAGEBUTTON_H_

#include <TiCore.h>
#include <bb/cascades/ImageButton>
#include <bb/cascades/TapEvent>

namespace TiUI {

class TiUIImageButton : public Ti::TiView
{
Q_OBJECT;
public:
	TiUIImageButton(Ti::TiViewProxy*);
	virtual ~TiUIImageButton();
	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();

	virtual void onTapEvent(bb::cascades::TapEvent*);
	bb::cascades::ImageButton * getNative();
private:
	bb::cascades::ImageButton *_button;
public slots:
	void onClick();
};
} /* namespace TiUI */
#endif /* TIUIIMAGEBUTTON_H_ */
