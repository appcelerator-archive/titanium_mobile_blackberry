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
      : rootLayout_(rootLayout)
      , root_(new bb::cascades::Container())
      , content_(NULL) {
        setRoot(root_);
    }

    virtual ~CustomListItem() {
      // Prevent the content from being released with this list item.
      // The content will be cleaned up once the data model is released.
      releaseContent();
    }

    virtual void setData(QObject* newData) {
        AbstractListItem::setData(newData);

        ListItemData* itemData = static_cast<ListItemData*>(newData);
        NativeControlObject* control = itemData->content();

        // Skip switching the content if the data object
        // is already being displayed by this list item.
        if (control->container_ == content_) {
          return;
        }

        // Swap the old content out and replace with the new content.
        releaseContent();
        content_ = control->container_;
        root_->add(content_);

        // Add content into the layout tree for the list view.
        nodeAddChild(rootLayout_, control->layout());
        Node* root = nodeRequestLayout(control->layout());
        if (root) {
          nodeLayout(root);
        }
    }

private:
    void releaseContent() {
      if (!content_) {
        return;
      }
      root_->remove(content_);
      content_->setParent(0);
      content_ = NULL;
    }

    Node* rootLayout_;
    bb::cascades::Container* root_;
    bb::cascades::Container* content_;
};

}  // namespace titanium

#endif
