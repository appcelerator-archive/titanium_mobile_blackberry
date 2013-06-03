/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "BasicListItem.h"

using namespace bb::cascades;

namespace titanium {

BasicListItem::BasicListItem() {
    item_ = new StandardListItem();
    setRoot(item_);
}

void BasicListItem::setData(QObject* newData) {
    updateImage(newData->property("leftImage").value<QUrl>());
    updateTitle(newData->property("title").toString());

    connect(newData, SIGNAL(leftImageChanged(const QUrl&)), SLOT(updateImage(const QUrl&)));
    connect(newData, SIGNAL(titleChanged(const QString&)), SLOT(updateTitle(const QString&)));

    if (data()) {
        // Remove any signals from the previous data object.
        data()->disconnect(this);
    }

    AbstractListItem::setData(newData);
}

void BasicListItem::updateImage(const QUrl& url) {
    if (url.isEmpty()) {
        item_->resetImage();
        return;
    }
    item_->setImage(Image(url));
}

void BasicListItem::updateTitle(const QString& title) {
    item_->setTitle(title);
}

}  // namespace titanium

