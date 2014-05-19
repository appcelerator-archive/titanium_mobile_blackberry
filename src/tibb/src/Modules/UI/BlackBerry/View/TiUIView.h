/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIVIEW_H_
#define TIUIVIEW_H_

#include <TiCore.h>
namespace TiUI {

class TiUIView : public Ti::TiView
{
Q_OBJECT;
public:
	TiUIView(Ti::TiViewProxy*);
	virtual ~TiUIView();
	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();
};
}
#endif /* TIUIVIEW_H_ */
