/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITableViewRowProxy.h"
#include "TiUITableViewRow.h"
#include <bb/cascades/AbsoluteLayoutProperties>

namespace TiUI {

TiUITableViewRowProxy::TiUITableViewRowProxy(const char* name) :
		Ti::TiViewProxy(name),
		_hasChildren(false)
{
	createPropertySetterGetter("title", _setTitle, _getTitle);
	createPropertySetterGetter("header", _setHeader, _getHeader);
	createPropertySetterGetter("leftImage", _setLeftImage, _getLeftImage);
	createPropertySetterGetter("subHeader", _setSubHeader, _getSubHeader);

	setView(new TiUITableViewRow(this));
	view->_setHeight("44dp");

}

TiUITableViewRowProxy::~TiUITableViewRowProxy()
{

}
TableViewRowType::Type TiUITableViewRowProxy::getType()
{
	return TableViewRowType::Row;
}


Ti::TiValue TiUITableViewRowProxy::add(Ti::TiValue val) {
	_hasChildren = true;
	return Ti::TiViewProxy::add(val);
}

bool TiUITableViewRowProxy::hasChildren()
{
	return _hasChildren;
}

QString TiUITableViewRowProxy::getRowTitle()
{
	return _title;
}

QString TiUITableViewRowProxy::getRowHeader()
{
	return _header;
}

QString TiUITableViewRowProxy::getRowLeftImage()
{
	return _leftImage;
}

QString TiUITableViewRowProxy::getRowSubHeader()
{
	return _subHeader;
}

void TiUITableViewRowProxy::setRowHeader(QString header)
{
	_header = QString(header);
}

void TiUITableViewRowProxy::setTitle(Ti::TiValue str)
{
	_title = str.toString();
}

void TiUITableViewRowProxy::setRowSubHeader(QString str)
{
	_subHeader = QString(str);
}

void TiUITableViewRowProxy::setHeader(Ti::TiValue str)
{
	_header = str.toString();
}

TI_GETTER_DEFER(TiUITableViewRowProxy, getLeftImage)
void TiUITableViewRowProxy::setLeftImage(Ti::TiValue str)
{
	_leftImage = str.toString();
}

TI_GETTER_DEFER(TiUITableViewRowProxy, getSubHeader)
void TiUITableViewRowProxy::setSubHeader(Ti::TiValue str)
{
	_subHeader = str.toString();
}

// Disable width, top, bottom, left, and right properties
void TiUITableViewRowProxy::setWidth(Ti::TiValue)
{

}
void TiUITableViewRowProxy::setTop(Ti::TiValue)
{

}
void TiUITableViewRowProxy::setBottom(Ti::TiValue)
{

}
void TiUITableViewRowProxy::setLeft(Ti::TiValue)
{

}
void TiUITableViewRowProxy::setRight(Ti::TiValue)
{

}

Ti::TiValue TiUITableViewRowProxy::getTitle()
{
	Ti::TiValue val;
	val.setString(_title);
	return val;
}

Ti::TiValue TiUITableViewRowProxy::getHeader()
{
	Ti::TiValue val;
	val.setString(_header);
	return val;
}
} /* namespace TiUI */
