/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "HeaderTableViewRow.h"

namespace titanium {

HeaderTableViewRow::HeaderTableViewRow() {
	item_ = new bb::cascades::Header();
    setRoot(item_);
}

HeaderTableViewRow::~HeaderTableViewRow() {
	// TODO Auto-generated destructor stub
}

void HeaderTableViewRow::setData(QObject* newData)
{
    updateTitle(newData->property("header").toString());
    updateSubTitle(newData->property("subHeader").toString());

    connect(newData, SIGNAL(headerChanged(const QString&)), SLOT(updateTitle(const QString&)));
    connect(newData, SIGNAL(subHeaderChanged(const QString&)), SLOT(updateSubTitle(const QString&)));

    if (data()) {
        // Remove any signals from the previous data object.
        data()->disconnect(this);
    }

    AbstractTableViewRow::setData(newData);
}

void HeaderTableViewRow::updateTitle(const QString& title) {
    item_->setTitle(title);
}
void HeaderTableViewRow::updateSubTitle(const QString& subtitle) {
    item_->setSubtitle(subtitle);
}

}
