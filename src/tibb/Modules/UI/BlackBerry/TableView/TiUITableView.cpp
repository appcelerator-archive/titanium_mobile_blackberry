/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include <bb/cascades/DataModel>
#include <bb/cascades/ArrayDataModel>
#include <bb/cascades/ScrollAnimation>
#include "TiUITableView.h"
#include "TiUITableViewRowProxy.h"
#include "Components/TableViewRowContainer.h"
#include "Components/TableViewRow.h"
#include "Components/TableViewManager.h"

namespace TiUI {

TiUITableView::TiUITableView(Ti::TiViewProxy* proxy) : Ti::TiView(proxy)
{

	TableViewManager *manager = new TableViewManager(this);

	_listView = new bb::cascades::ListView();
	_listView->setDataModel(new bb::cascades::ArrayDataModel(this));
	_listView->setListItemProvider(manager);
	_listView->setListItemTypeMapper(manager);

	setChildControl(_listView);

    QObject::connect(_listView, SIGNAL(triggered(QVariantList)), this, SLOT(onClick(QVariantList)));

}

bool TiUITableView::ingoreWidth()
{
	return false;
}
bool TiUITableView::ingoreHeight()
{
	return false;
}
QString TiUITableView::defaultWidth()
{
	return Ti::TiConstants::SizeFILL;
}
QString TiUITableView::defaultHeight()
{
	return Ti::TiConstants::SizeFILL;
}

void TiUITableView::onEventAdded(QString)
{

}

void TiUITableView::scrollToIndex(int index, bool animated)
{
    QVariant variant(index);
    QVariantList scroll;
    scroll.append(variant);
	_listView->scrollToItem(scroll, animated ? bb::cascades::ScrollAnimation::Smooth : bb::cascades::ScrollAnimation::None);
}

bb::cascades::ListView* TiUITableView::getListView()
{
	return _listView;
}

void TiUITableView::onClick(QVariantList variantList)
{
	bool success;
	int index = variantList[0].toInt(&success);
	TiUITableViewRowProxy *rowProxy = _tableData.at(index);

	Ti::TiEventParameters tableEventParams;
	tableEventParams.addParam("index", index);
	tableEventParams.addParam("row", rowProxy);
	tableEventParams.addParam("rowData", rowProxy);
	getProxy()->fireEvent(Ti::TiConstants::EventClick, tableEventParams);

	Ti::TiEventParameters rowEventParams;
	rowEventParams.addParam("index", index);
	rowProxy->fireEvent(Ti::TiConstants::EventClick, rowEventParams);
}

TiUITableView::~TiUITableView()
{

}

void TiUITableView::onRelayout(QRectF rect)
{
	Ti::TiView::onRelayout(rect);
// Do not delete this comment, yet.
//
//	float width = rect.width();
//	for(int i = 0, len = _tableData.size(); i < len; i++)
//	{
//		Ti::TiViewProxy *proxy = _tableData.at(i);
//		Ti::TiView *view = proxy->getView();
//		view->_setWidth(QString::number(width).append("px"));
//	}
}


void TiUITableView::_setData(QList<TiUITableViewRowProxy*> data)
{
	_tableData.clear();
	_tableData.append(data);

	bb::cascades::ArrayDataModel *dataModel = (bb::cascades::ArrayDataModel*)_listView->dataModel();
	dataModel->clear();
	for(int i = 0, len = _tableData.size(); i < len; i++)
	{
		TiUITableViewRowProxy *proxy = static_cast<TiUITableViewRowProxy*>(_tableData.at(i));
		TableViewRowContainer *cell = new TableViewRowContainer(dataModel);
		cell->setRowProxy(proxy);
		dataModel->append(QVariant::fromValue(cell));
	}
}

} /* namespace TiUI */
