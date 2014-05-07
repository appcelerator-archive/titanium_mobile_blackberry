/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIScrollableView.h"
#include <bb/cascades/Container>
#include "ScrollableView.h"

namespace TiUI {

TiUIScrollableView::TiUIScrollableView(Ti::TiViewProxy* proxy) : Ti::TiView(proxy)
{
	_scrollableView = new ScrollableView();
	_scrollableView->setTiView(this);
	setChildControl(_scrollableView);
}

TiUIScrollableView::~TiUIScrollableView()
{
}

bool TiUIScrollableView::ingoreWidth()
{
	return false;
}
bool TiUIScrollableView::ingoreHeight()
{
	return false;
}
QString TiUIScrollableView::defaultWidth()
{
	return Ti::TiConstants::SizeFILL;
}
QString TiUIScrollableView::defaultHeight()
{
	return Ti::TiConstants::SizeFILL;
}
ScrollableView* TiUIScrollableView::getNative()
{
	return _scrollableView;
}
void TiUIScrollableView::onPageChange(int index)
{
	Ti::TiEventParameters eventParams;
	eventParams.addParam("index", index);
	getProxy()->fireEvent(Ti::TiConstants::EventChange, eventParams);
}
void TiUIScrollableView::onRelayout(QRectF rect)
{
	Ti::TiView::onRelayout(rect);
}

}
