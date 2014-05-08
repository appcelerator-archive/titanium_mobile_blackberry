/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUITABLEVIEW_H_
#define TI_TIUITABLEVIEW_H_

#include "TiCore.h"
#include <bb/cascades/ListView>

namespace TiUI {
class TiUITableViewRowProxy;
class TiUITableView : public Ti::TiView
{
	Q_OBJECT;
public:
	TiUITableView(Ti::TiViewProxy*);
	virtual ~TiUITableView();

	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();

	void _setData(QList<TiUITableViewRowProxy*>);
	virtual void onRelayout(QRectF);

	virtual void onEventAdded(QString);
	void scrollToIndex(int, bool animated = true);
	bb::cascades::ListView* getListView();
private:
	bb::cascades::ListView* _listView;
	QList<TiUITableViewRowProxy*> _tableData;
public slots:
	void onClick(QVariantList);
};

}
/* namespace TiUI */

#endif /* TIUITABLEVIEW_H_ */
