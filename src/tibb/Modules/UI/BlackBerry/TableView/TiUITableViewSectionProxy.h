/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUITABLEVIEWSECTIONPROXY_H_
#define TI_TIUITABLEVIEWSECTIONPROXY_H_

#include "TiCore.h"
#include "Components/TableViewRowType.h"

namespace TiUI {
class TiUITableViewRowProxy;
class TiUITableViewSectionProxy : public Ti::TiProxy, public TableViewRowType
{
public:
	CREATE_PROXY(TiUITableViewSectionProxy)
	TiUITableViewSectionProxy(const char*);
	virtual ~TiUITableViewSectionProxy();


	Ti::TiValue getRowCount();
	Ti::TiValue getRows();

	Ti::TiValue add(Ti::TiValue);
	Ti::TiValue remove(Ti::TiValue);
	Ti::TiValue rowAtIndex(Ti::TiValue);

	TI_CREATE_SETTER_GETTER(TiUITableViewSectionProxy, setHeaderTitle, getHeaderTitle)
	TI_CREATE_SETTER_GETTER(TiUITableViewSectionProxy, setHeaderSubTitle, getHeaderSubTitle)
	TI_CREATE_SETTER_GETTER(TiUITableViewSectionProxy, setFooterTitle, getFooterTitle)
	TI_CREATE_SETTER_GETTER(TiUITableViewSectionProxy, setFooterView, getFooterView)
	TI_CREATE_SETTER_GETTER(TiUITableViewSectionProxy, setHeaderView, getHeaderView)

	EXPOSE_GETTER(TiUITableViewSectionProxy, getRowCount)
	EXPOSE_GETTER(TiUITableViewSectionProxy, getRows)
	EXPOSE_METHOD(TiUITableViewSectionProxy, add)
	EXPOSE_METHOD(TiUITableViewSectionProxy, remove)
	EXPOSE_METHOD(TiUITableViewSectionProxy, rowAtIndex)

	QList<TiUITableViewRowProxy*> getTableViewRows();
	virtual TableViewRowType::Type getType();

private:
	QString _headerTitle;
	QString _headerSubtitle;
	QList<TiUITableViewRowProxy*> _tableViewRows;
};
}
#endif /* TIUITABLEVIEWSECTIONPROXY_H_ */
