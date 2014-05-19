/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TABLEVIEWROW_H_
#define TI_TABLEVIEWROW_H_

#include <TiCore.h>
#include <bb/cascades/CustomControl>
#include <bb/cascades/Container>

namespace TiUI {

class TableViewRow : public bb::cascades::CustomControl
{
	Q_OBJECT;
public:
	TableViewRow(Ti::TiView*);
	void replaceView(Ti::TiView*);
	virtual ~TableViewRow();
private:
	bb::cascades::Container* _container;
	Ti::TiView* _view;
	Ti::TiView* _tableView;
};

} /* namespace TiUI */
#endif /* TABLEVIEWROW_H_ */
