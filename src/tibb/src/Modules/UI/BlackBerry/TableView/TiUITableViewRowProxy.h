/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUITABLEVIEWROWPROXY_H_
#define TI_TIUITABLEVIEWROWPROXY_H_

#include <TiCore.h>
#include "Components/TableViewRowType.h"

namespace TiUI {

class TiUITableViewRowProxy : public Ti::TiViewProxy, public TableViewRowType
{
public:
	CREATE_PROXY(TiUITableViewRowProxy)
	TiUITableViewRowProxy(const char*);
	virtual ~TiUITableViewRowProxy();

	virtual void setWidth(Ti::TiValue);
	virtual void setTop(Ti::TiValue);
	virtual void setBottom(Ti::TiValue);
	virtual void setLeft(Ti::TiValue);
	virtual void setRight(Ti::TiValue);
	virtual Ti::TiValue add(Ti::TiValue);

	TI_CREATE_SETTER_GETTER(TiUITableViewRowProxy, setTitle, getTitle)
	TI_CREATE_SETTER_GETTER(TiUITableViewRowProxy, setHeader, getHeader)
	TI_CREATE_SETTER_GETTER(TiUITableViewRowProxy, setLeftImage, getLeftImage)
	TI_CREATE_SETTER_GETTER(TiUITableViewRowProxy, setSubHeader, getSubHeader)

	QString getRowTitle();
	QString getRowHeader();
	QString getRowLeftImage();
	QString getRowSubHeader();
	void setRowHeader(QString);
	void setRowSubHeader(QString);
	bool hasChildren();
	virtual TableViewRowType::Type getType();
private:
	QString _title;
	QString _header;
	QString _leftImage;
	QString _subHeader;
	bool _hasChildren;

};


} /* namespace TiUI */
#endif /* TIUITABLEVIEWROWPROXY_H_ */
