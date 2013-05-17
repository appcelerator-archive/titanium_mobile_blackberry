/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TABLEVIEW_CUSTOM_LIST_ITEM_H
#define TI_TABLEVIEW_CUSTOM_LIST_ITEM_H

#include <bb/cascades/Container>

#include "AbstractListItem.h"
#include "ListItemData.h"

namespace titanium {

class CustomListItem : public AbstractListItem {
public:
    CustomListItem(Node* rootLayout)
      : rootLayout_(rootLayout) {
    }

    virtual void setData(QObject* newData) {
        AbstractListItem::setData(newData);

        ListItemData* itemData = static_cast<ListItemData*>(newData);
        NativeControlObject* control = itemData->content();

        setRoot(control->container_);
        nodeAddChild(rootLayout_, control->layout());
    }

private:
    Node* rootLayout_;
};

}  // namespace titanium

#endif
