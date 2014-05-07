/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TABLEVIEWCELL_H_
#define TI_TABLEVIEWCELL_H_

#include <QObject>
#include "TiCore.h"

namespace TiUI {
class TiUITableViewRowProxy;

class TableViewRowContainer : public QObject
{
	Q_OBJECT;

public:
	TableViewRowContainer(QObject*);
	void setRowProxy(TiUITableViewRowProxy*);
	QString getType() const;
	QString getHeader() const;
	QString getTitle() const;
	QString getLeftImage() const;
	QString getSubHeader() const;
	Ti::TiView* getView() const;
	virtual ~TableViewRowContainer();
private:
	TiUITableViewRowProxy* _proxy;
	QString _type;
};

} /* namespace TiUI */
Q_DECLARE_METATYPE( TiUI::TableViewRowContainer *);
#endif /* TABLEVIEWCELL_H_ */
