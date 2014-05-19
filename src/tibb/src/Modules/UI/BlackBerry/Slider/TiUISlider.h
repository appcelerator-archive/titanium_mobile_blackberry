/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUISLIDER_H_
#define TI_TIUISLIDER_H_

#include <TiCore.h>
#include <bb/cascades/Slider>

namespace TiUI {

class TiUISlider : public Ti::TiView
{
	Q_OBJECT;
public:
	TiUISlider(Ti::TiViewProxy*);
	virtual ~TiUISlider();

	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();

	bb::cascades::Slider* getNative();
private:
	bb::cascades::Slider *_slider;
public slots:
	void onChange(float);
	void onChanging(float);
};
}
#endif /* TIUISLIDER_H_ */
