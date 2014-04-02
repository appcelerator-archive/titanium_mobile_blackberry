/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TABLEVIEW_CUSTOM_ROW_H
#define TI_TABLEVIEW_CUSTOM_ROW_H

#include <bb/cascades/Container>

#include "AbstractTableViewRow.h"
#include "TiCore.h"

namespace titanium {

class CustomTableViewRow : public AbstractTableViewRow {
public:
    CustomTableViewRow(Ti::Layout::Node* rootLayout);
    virtual ~CustomTableViewRow();

    virtual void setData(QObject* newData);

private:
    void releaseContent();

    Ti::Layout::Node* rootLayout_;
    bb::cascades::Container* root_;
    bb::cascades::Container* content_;
};

}  // namespace titanium

#endif
