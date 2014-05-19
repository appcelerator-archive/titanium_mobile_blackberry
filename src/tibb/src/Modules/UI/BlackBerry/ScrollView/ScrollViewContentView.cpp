/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "ScrollViewContentView.h"

namespace TiUI {

ScrollViewContentView::ScrollViewContentView(Ti::TiViewProxy* proxy) :
		Ti::TiView(proxy),
		_scrollView(NULL)
{
}

ScrollViewContentView::~ScrollViewContentView() {
	// TODO Auto-generated destructor stub
}

void ScrollViewContentView::onRelayout(QRectF rect)
{
	Ti::TiView::onRelayout(rect);
	if(_viewSize != rect.size()) _viewSize = rect.size();
	_scrollView->updateContentSize(rect);
}

bool ScrollViewContentView::ingoreWidth()
{
	return false;
}
bool ScrollViewContentView::ingoreHeight()
{
	return false;
}
QString ScrollViewContentView::defaultWidth()
{
	return Ti::TiConstants::SizeFILL;
}
QString ScrollViewContentView::defaultHeight()
{
	return Ti::TiConstants::SizeFILL;
}

void ScrollViewContentView::setScrollView(TiUIScrollView* scrollView)
{
	_scrollView = scrollView;
}

} /* namespace Ti */
