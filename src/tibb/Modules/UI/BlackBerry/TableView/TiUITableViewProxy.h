/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUITABLEVIEWPROXY_H_
#define TI_TIUITABLEVIEWPROXY_H_

#include "TiCore.h"
#include <QList>

namespace TiUI {
class TiUITableViewRowProxy;

class TiUITableViewProxy : public Ti::TiViewProxy
{
public:
	CREATE_PROXY(TiUITableViewProxy)
	TiUITableViewProxy(const char*);

	Ti::TiValue scrollToIndex(Ti::TiValue);

	EXPOSE_METHOD(TiUITableViewProxy, scrollToIndex)
	TI_CREATE_SETTER_GETTER(TiUITableViewProxy, setData, getData)
	void addRows(QList<Ti::TiValue>);
	virtual ~TiUITableViewProxy();
	void emptyOldData();
private:
	QList<TiUITableViewRowProxy*> _tableData;
};

} /* namespace TiUI */
#endif /* TIUITABLEVIEWPROXY_H_ */
