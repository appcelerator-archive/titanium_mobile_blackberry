/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIView.h"

namespace TiUI {

TiUIView::TiUIView(Ti::TiViewProxy* _proxy) : Ti::TiView(_proxy)
{
}

TiUIView::~TiUIView()
{

}
bool TiUIView::ingoreWidth()
{
	return false;
}
bool TiUIView::ingoreHeight()
{
	return false;
}
QString TiUIView::defaultWidth()
{
	return Ti::TiConstants::SizeFILL;
}
QString TiUIView::defaultHeight()
{
	return Ti::TiConstants::SizeFILL;
}

}
