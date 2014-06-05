/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITableViewSectionProxy.h"
#include "TiUITableViewRowProxy.h"
namespace TiUI {

TiUITableViewSectionProxy::TiUITableViewSectionProxy(const char* name) : Ti::TiProxy(name)
{

	createPropertyGetter("rowCount", _getRowCount);
	createPropertyGetter("rows", _getRows);

	createPropertySetterGetter("footerTitle", _setFooterTitle,  _getFooterTitle);
	createPropertySetterGetter("footerView", _setFooterView,  _getFooterView);
	createPropertySetterGetter("headerTitle", _setHeaderTitle,  _getHeaderTitle);
	createPropertySetterGetter("headerSubTitle", _setHeaderSubTitle,  _getHeaderSubTitle);
	createPropertySetterGetter("headerView", _setHeaderView,  _getHeaderView);
	createPropertySetterGetter("title", _setHeaderTitle,  _getHeaderTitle);
	createPropertySetterGetter("subTitle", _setHeaderSubTitle,  _getHeaderSubTitle);

	createPropertyFunction("add", _add);
	createPropertyFunction("remove", _remove);
	createPropertyFunction("rowAtIndex", _rowAtIndex);

}

TiUITableViewSectionProxy::~TiUITableViewSectionProxy()
{
}

QList<TiUITableViewRowProxy*> TiUITableViewSectionProxy::getTableViewRows()
{
	foreach(TiUITableViewRowProxy* r, _tableViewRows)
	{
		r->setRowHeader("");
		r->setRowSubHeader("");
	}
	if(_tableViewRows.size() > 0)
	{
		TiUITableViewRowProxy* firstRow = _tableViewRows[0];
		firstRow->setRowHeader(_headerTitle);
		firstRow->setRowSubHeader(_headerSubtitle);
	}
	return _tableViewRows;
}

TableViewRowType::Type TiUITableViewSectionProxy::getType()
{
	return TableViewRowType::Section;
}

void TiUITableViewSectionProxy::setFooterTitle(Ti::TiValue)
{
}
void TiUITableViewSectionProxy::setFooterView(Ti::TiValue)
{
}
void TiUITableViewSectionProxy::setHeaderTitle(Ti::TiValue val)
{
	_headerTitle = val.toString();
}
void TiUITableViewSectionProxy::setHeaderSubTitle(Ti::TiValue val)
{
	_headerSubtitle = val.toString();
}
void TiUITableViewSectionProxy::setHeaderView(Ti::TiValue)
{
}

Ti::TiValue TiUITableViewSectionProxy::getFooterTitle()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITableViewSectionProxy::getFooterView()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITableViewSectionProxy::getHeaderTitle()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITableViewSectionProxy::getHeaderView()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITableViewSectionProxy::getHeaderSubTitle()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

Ti::TiValue TiUITableViewSectionProxy::getRowCount()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITableViewSectionProxy::getRows()
{
	Ti::TiValue val;
	foreach(TiUITableViewRowProxy* rows, _tableViewRows)
	{

	}
	val.setUndefined();
	return val;
}

Ti::TiValue TiUITableViewSectionProxy::add(Ti::TiValue value)
{
	TiUITableViewRowProxy* row = NULL;
	if(value.isMap())
	{
		row = TiUITableViewRowProxy::CreateProxy();
		row->initWithObject(value.toJSValue()->ToObject());
	}
	else
	if(value.isProxy())
	{
		row = static_cast<TiUITableViewRowProxy*>(value.toProxy());
	}
	row->setRowHeader("");
	row->clearWeak();

	_tableViewRows.append(row);

	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITableViewSectionProxy::remove(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUITableViewSectionProxy::rowAtIndex(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

}
