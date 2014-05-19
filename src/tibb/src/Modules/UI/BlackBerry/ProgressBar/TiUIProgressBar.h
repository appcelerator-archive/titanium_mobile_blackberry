/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUIPROGRESSBAR_H_
#define TI_TIUIPROGRESSBAR_H_

#include <TiCore.h>
#include <bb/cascades/ProgressIndicator>

namespace TiUI {

class TiUIProgressBar : public Ti::TiView
{
	Q_OBJECT;
public:
	TiUIProgressBar(Ti::TiViewProxy*);
	virtual ~TiUIProgressBar();

	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();

	void setMaxValue(float);
	void setMinValue(float);
	void setValue(float);

	float getMaxValue();
	float getMinValue();
	float getValue();

	bb::cascades::ProgressIndicator* getNative();

private:
	bb::cascades::ProgressIndicator* _progressBar;
};
}
#endif /* TIUIPROGRESSBAR_H_ */
