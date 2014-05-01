/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIWindow.h"
#include "TiUIWindowProxy.h"
#include <bb/cascades/ActionItem>
#include <bb/cascades/Page>

namespace TiUI {

TiUIWindow::TiUIWindow(Ti::TiViewProxy* proxy) : Ti::TiView(proxy)
{
}

TiUIWindow::~TiUIWindow()
{
}

bool TiUIWindow::ingoreWidth()
{
	return true;
}
bool TiUIWindow::ingoreHeight()
{
	return true;
}
QString TiUIWindow::defaultWidth()
{
	return Ti::TiConstants::SizeFILL;
}
QString TiUIWindow::defaultHeight()
{
	return Ti::TiConstants::SizeFILL;
}

} /* namespace TiUI */
