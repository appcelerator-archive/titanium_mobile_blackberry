/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_SCROLLABLEVIEWPAGE_H_
#define TI_SCROLLABLEVIEWPAGE_H_

#include <bb/cascades/CustomControl>
#include "TiCore.h"

namespace TiUI
{

class ScrollableViewPage: public bb::cascades::CustomControl {
public:
	ScrollableViewPage();
	virtual ~ScrollableViewPage();
	void replaceView(Ti::TiView*);
	bb::cascades::Container* _container;
	Ti::TiView* _view;
};

class PageContainer : public QObject
{
	Q_OBJECT;
public:
	PageContainer(Ti::TiView*);
	Ti::TiView* view;
};

}
Q_DECLARE_METATYPE( TiUI::PageContainer *);

#endif /* SCROLLABLEVIEWPAGE_H_ */
