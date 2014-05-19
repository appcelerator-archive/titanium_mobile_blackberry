/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUISCROLLABLEVIEW_H_
#define TI_TIUISCROLLABLEVIEW_H_

#include <TiCore.h>

namespace TiUI {
class ScrollableView;
class TiUIScrollableView : public Ti::TiView
{
	Q_OBJECT;
public:
	TiUIScrollableView(Ti::TiViewProxy*);
	virtual ~TiUIScrollableView();
	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();
	virtual void onRelayout(QRectF);
	void onPageChange(int);
	ScrollableView* getNative();
private:
	ScrollableView* _scrollableView;
public slots:
};
}
#endif /* TIUISCROLLABLEVIEW_H_ */
