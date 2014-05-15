/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUIACTIVITYINDICATOR_H_
#define TI_TIUIACTIVITYINDICATOR_H_

#include "TiCore.h"

#include <bb/cascades/ActivityIndicator>

namespace TiUI {

class TiUIActivityIndicator : public Ti::TiView
{
	Q_OBJECT;
public:
	TiUIActivityIndicator(Ti::TiViewProxy*);
	virtual ~TiUIActivityIndicator();

	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();

	bb::cascades::ActivityIndicator* getNativeIndicator();
private:
	bb::cascades::ActivityIndicator* _indicator;
public slots:
};
}
#endif /* TIUIACTIVITYINDICATOR_H_ */
