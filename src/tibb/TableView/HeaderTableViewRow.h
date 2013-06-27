/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef HEADERTABLEVIEWROW_H_
#define HEADERTABLEVIEWROW_H_

#include "AbstractTableViewRow.h"
#include <bb/cascades/Header>

namespace titanium {

class HeaderTableViewRow: public titanium::AbstractTableViewRow {
    Q_OBJECT

public:
	HeaderTableViewRow();
	virtual ~HeaderTableViewRow();
    virtual void setData(QObject* data);
    bb::cascades::Header* item_;

private slots:
void updateTitle(const QString& title);
void updateSubTitle(const QString& subtitle);

};

#endif /* HEADERTABLEVIEWROW_H_ */
}
