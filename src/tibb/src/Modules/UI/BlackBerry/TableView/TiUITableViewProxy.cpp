/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITableViewProxy.h"
#include "TiUITableView.h"
#include "TiUITableViewRowProxy.h"
#include "TiUITableViewSectionProxy.h"
#include "Components/TableViewRowType.h"

namespace TiUI {

TiUITableViewProxy::TiUITableViewProxy(const char* name) : Ti::TiViewProxy(name)
{
	createPropertySetterGetter("data", _setData, _getData);
	createPropertyFunction("scrollToIndex", _scrollToIndex);
	setView(new TiUITableView(this));
}

TiUITableViewProxy::~TiUITableViewProxy()
{
	foreach(TiUITableViewRowProxy* row, _tableData)
	{
		row->makeWeak();
	}
}

Ti::TiValue TiUITableViewProxy::scrollToIndex(Ti::TiValue val)
{
	int index = 0;
	bool animated = true;
	if(val.isNumber())
	{
		index = (int)val.toNumber();
	}
	if(val.isList()){
		QList<Ti::TiValue> args = val.toList();
		if(args.length() > 0) {
			Ti::TiValue indexValue = args.at(0);
			index = (int)indexValue.toNumber();
		}
		if(args.length() > 1) {
			Ti::TiValue options = args.at(1);
			if(options.isMap()) {
				QMap<QString, Ti::TiValue> optionsValue = options.toMap();
				if(optionsValue.contains("animated"))
				{
					Ti::TiValue ani = optionsValue["animated"];
					animated = ani.toBool();
				}
			}
		}
	}

	TiUITableView* tableView = static_cast<TiUITableView*>(getView());
	tableView->scrollToIndex(index, animated);
	return Ti::TiValue();
}

void TiUITableViewProxy::addRows(QList<Ti::TiValue> rowData)
{
	for(int i = 0, len = rowData.size(); i < len; i++)
	{
		Ti::TiValue val = rowData.at(i);
		TiUITableViewRowProxy* newRow = NULL;
		TiUITableViewSectionProxy* newSection = NULL;
		TableViewRowType *rowType = NULL;
		if(!val.isProxy() && val.isMap())
		{
			newRow = TiUITableViewRowProxy::CreateProxy();
			newRow->initWithObject(val.toJSValue()->ToObject());
		}
		else if(val.isProxy())
		{
			Ti::TiProxy *r = val.toProxy();
			rowType = dynamic_cast<TableViewRowType*>(r);
			if(rowType->getType() == TableViewRowType::Section)
			{
				newSection = static_cast<TiUITableViewSectionProxy*>(r);
			}
			else
			{
				newRow = static_cast<TiUITableViewRowProxy*>(r);
			}
		}
		if(newSection != NULL)
		{
			QList<Ti::TiValue> data;
			QList<TiUITableViewRowProxy*> rows = newSection->getTableViewRows();
			foreach(TiUITableViewRowProxy* row, rows)
			{
				Ti::TiValue val;
				val.setProxy(row);
				data.append(val);
			}
			addRows(data);
			continue;
		}
		if(newRow != NULL)
		{
			if(!newRow->getRowHeader().isEmpty() || newRow->getRowHeader().length() > 0) {
				TiUITableViewRowProxy *nextRow = TiUITableViewRowProxy::CreateProxy();
				nextRow->setRowHeader(newRow->getRowHeader());
				nextRow->setRowSubHeader(newRow->getRowSubHeader());
				nextRow->clearWeak();
				_tableData.append(nextRow);
				newRow->setRowHeader("");
				newRow->setRowSubHeader("");
			}
			newRow->clearWeak();
			view->viewLayout->addChild(newRow->view);
			_tableData.append(newRow);
		}
	}
	TiUITableView* tableView = static_cast<TiUITableView*>(getView());
	tableView->_setData(_tableData);
}

TI_GETTER_DEFER(TiUITableViewProxy, getData)
void TiUITableViewProxy::setData(Ti::TiValue data)
{
	if(!data.isList()) return;
	emptyOldData();
	QList<Ti::TiValue> rowData = data.toList();
	addRows(rowData);
}

void TiUITableViewProxy::emptyOldData()
{
	for(int i = 0, len = _tableData.size(); i < len; i++)
	{
		TiUITableViewRowProxy *row = static_cast<TiUITableViewRowProxy*>(_tableData.at(i));
		view->viewLayout->removeChild(row->view);
		row->makeWeak();
	}
	_tableData.clear();
}
} /* namespace TiUI */
