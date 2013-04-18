/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TABLEVIEW_CUSTOM_LIST_ITEM_H
#define TI_TABLEVIEW_CUSTOM_LIST_ITEM_H

#include "AbstractListItem.h"

namespace titanium {

class CustomListItem : public AbstractListItem {
public:
    CustomListItem() { }

    virtual void setData(QObject* newData) {
        AbstractListItem::setData(newData);

        QVariant content = newData->property("content");
        Q_ASSERT(content.canConvert<bb::cascades::VisualNode*>());
        setRoot(content.value<bb::cascades::VisualNode*>());
    }
};

}  // namespace titanium

#endif
