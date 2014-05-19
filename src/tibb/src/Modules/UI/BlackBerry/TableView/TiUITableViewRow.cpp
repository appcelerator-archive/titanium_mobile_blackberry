/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITableViewRow.h"

namespace TiUI {

TiUITableViewRow::TiUITableViewRow(Ti::TiViewProxy* proxy) : Ti::TiView(proxy)
{
}

TiUITableViewRow::~TiUITableViewRow() {

}

bool TiUITableViewRow::ingoreWidth()
{
	return false;
}
bool TiUITableViewRow::ingoreHeight()
{
	return false;
}
QString TiUITableViewRow::defaultWidth()
{
	return Ti::TiConstants::SizeFILL;
}
QString TiUITableViewRow::defaultHeight()
{
	return Ti::TiConstants::SizeSIZE;
}

void TiUITableViewRow::onEventAdded(QString)
{
}

} /* namespace TiUI */
