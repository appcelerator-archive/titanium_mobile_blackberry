/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "ScrollableViewPage.h"
#include <bb/cascades/DockLayout>
namespace TiUI
{

ScrollableViewPage::ScrollableViewPage() : bb::cascades::CustomControl(), _view(NULL)
{
	_container = new bb::cascades::Container();
	_container->setLayout(new bb::cascades::DockLayout());
	setRoot(_container);
}

ScrollableViewPage::~ScrollableViewPage() {
	// TODO Auto-generated destructor stub
}

void ScrollableViewPage::replaceView(Ti::TiView* view)
{
	if(_view != NULL)
	{
		_container->remove(_view);
	}

	_view = view;
	_container->add(view);
}

PageContainer::PageContainer(Ti::TiView* _view) : view(_view)
{
}

}
