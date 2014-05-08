/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUISCROLLVIEW_H_
#define TI_TIUISCROLLVIEW_H_

#include "TiCore.h"
#include "ScrollViewContentViewProxy.h"

namespace bb
{
namespace cascades
{
class ScrollView;
}
}
namespace TiUI {

class TiUIScrollView : public Ti::TiView
{
	Q_OBJECT;
public:
	TiUIScrollView(Ti::TiViewProxy*);
	virtual ~TiUIScrollView();

	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();

	virtual void onRelayout(QRectF);
	void setLayout(QString);
	void setContentSize(QSizeF);
	bb::cascades::ScrollView* getScrollView();
	Ti::TiView * getInnerView();
	Ti::TiViewProxy *getInnerViewProxy();
	void updateContentSize(QRectF);
	void setScrollEvent();
private:
	Ti::TiView *_innerView;
	Ti::TiViewProxy *_innerViewProxy;
	bb::cascades::ScrollView* _scrollView;
	QSizeF _contentSize;
	QSizeF _viewSize;
	bool _hasScrollEvent;
public slots:
	void onScroll(const QRectF&, float);
};
}
#endif /* TIUISCROLLVIEW_H_ */
