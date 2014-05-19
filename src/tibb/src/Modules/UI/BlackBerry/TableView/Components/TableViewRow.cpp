/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TableViewRow.h"
#include <bb/cascades/HorizontalAlignment>
#include <bb/cascades/DockLayout>
#include <bb/cascades/Color>

namespace TiUI {

TableViewRow::TableViewRow(Ti::TiView* tableView) :
		bb::cascades::CustomControl(),
		_view(NULL),
		_tableView(tableView)
{
	_container = bb::cascades::Container::create();
	setRoot(_container);
}

void TableViewRow::replaceView(Ti::TiView* view)
{
	if(_view != NULL)
	{
//		_tableView->viewLayout->removeChild(_view);
		_container->remove(_view);
	}

	_view = view;
	_container->add(view);
//	_tableView->viewLayout->addChild(_view);
}

TableViewRow::~TableViewRow() {
	// TODO Auto-generated destructor stub
}

} /* namespace TiUI */
