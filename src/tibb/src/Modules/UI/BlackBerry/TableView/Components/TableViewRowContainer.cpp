/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TableViewRowContainer.h"
#include "../TiUITableViewRowProxy.h"

static QString const LIST_ITEM_HEADER = "header";
static QString const LIST_ITEM_SIMPLE = "simple";
static QString const LIST_ITEM_CUSTOM = "custom";

namespace TiUI {

TableViewRowContainer::TableViewRowContainer(QObject* parent) :
		QObject(parent),
		_type(LIST_ITEM_SIMPLE)
{

}

TableViewRowContainer::~TableViewRowContainer()
{
}

QString TableViewRowContainer::getType() const
{
	return _type;
}

QString TableViewRowContainer::getTitle() const
{
	return _proxy->getRowTitle();
}

QString TableViewRowContainer::getHeader() const
{
	return _proxy->getRowHeader();
}

QString TableViewRowContainer::getLeftImage() const
{
	return _proxy->getRowLeftImage();
}
QString TableViewRowContainer::getSubHeader() const
{
	return _proxy->getRowSubHeader();
}

Ti::TiView* TableViewRowContainer::getView() const
{
	return _proxy->getView();
}

void TableViewRowContainer::setRowProxy(TiUITableViewRowProxy* proxy)
{
	_proxy = proxy;
	if(_proxy->hasChildren())
	{
		_type = LIST_ITEM_CUSTOM;
	}
	else if(!_proxy->getRowHeader().isEmpty() || _proxy->getRowHeader().length() > 0)
	{
		_type = LIST_ITEM_HEADER;
	}
}

} /* namespace TiUI */
