/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TABLEVIEW_ABSTRACT_LIST_ITEM_H
#define TI_TABLEVIEW_ABSTRACT_LIST_ITEM_H

#include <bb/cascades/CustomControl>

namespace titanium {

class AbstractListItem : public bb::cascades::CustomControl {
public:
    AbstractListItem() { }

    QObject* data() const {
        return data_;
    }

    virtual void setData(QObject* newData) {
        data_ = newData;
    }

private:
    QObject* data_;
};

}  // namespace titanium

#endif
