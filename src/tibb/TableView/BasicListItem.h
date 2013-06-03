/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_BASIC_LIST_ITEM_H
#define TI_BASIC_LIST_ITEM_H

#include <bb/cascades/StandardListItem>

#include "AbstractListItem.h"

namespace titanium {

// The visual control for "basic" table view rows.
// These provide their own layout for displaying a title, image, etc.
class BasicListItem : public AbstractListItem {
    Q_OBJECT

public:
    BasicListItem();

    virtual void setData(QObject* data);

private slots:
    void updateImage(const QUrl& url);
    void updateTitle(const QString& title);

private:
    bb::cascades::StandardListItem* item_;
};

}  // namespace titanium

#endif
