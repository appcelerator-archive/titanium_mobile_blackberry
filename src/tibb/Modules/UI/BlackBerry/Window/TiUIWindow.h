/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_UIWINDOW_H_
#define TI_UIWINDOW_H_

#include "TiCore.h"

namespace TiUI {

class TiUIWindow : public Ti::TiView
{
Q_OBJECT;
public:
	TiUIWindow(Ti::TiViewProxy*);
	virtual ~TiUIWindow();
	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();

};

} /* namespace TiUI */
#endif /* TIUIWINDOW_H_ */
