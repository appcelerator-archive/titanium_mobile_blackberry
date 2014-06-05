/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_SCROLLVIEWCONTENTVIEW_H_
#define TI_SCROLLVIEWCONTENTVIEW_H_

#include <TiCore.h>
#include "TiUIScrollView.h"

namespace TiUI {

class ScrollViewContentView : public Ti::TiView
{
	Q_OBJECT;
public:
	ScrollViewContentView(Ti::TiViewProxy* proxy);
	virtual ~ScrollViewContentView();

	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();
	virtual void onRelayout(QRectF);
	virtual void onTapEvent(bb::cascades::TapEvent*);
	void setScrollView(TiUIScrollView* scrollView);
private:
	TiUIScrollView* _scrollView;
	QSizeF _viewSize;
};

} /* namespace Ti */
#endif /* SCROLLVIEWCONTENTVIEW_H_ */
