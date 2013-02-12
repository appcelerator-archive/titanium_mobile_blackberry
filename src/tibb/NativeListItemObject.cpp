/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeListItemObject.h"

#include "TableView/ListItemData.h"
#include "TiObject.h"

NativeListItemObject::NativeListItemObject(TiObject* object)
    : NativeControlObject(object, N_TYPE_LIST_ITEM)
    , data_(new ListItemData(object)) {
    // Prevent the data object from getting destroyed
    // when it is removed from the data model. It should live
    // until this native object is deleted.
    data_->setParent(data_.data());
}

NativeListItemObject::~NativeListItemObject() {
}

int NativeListItemObject::setLeftImage(TiObject* obj) {
    QString imagePath = TiObject::getStringFromValue(obj->getValue());
    data_->setProperty("leftImage", QUrl(getResourcePath(imagePath)));
    return NATIVE_ERROR_OK;
}

int NativeListItemObject::setTitle(TiObject* obj) {
    data_->setProperty("title", TiObject::getStringFromValue(obj->getValue()));
    return NATIVE_ERROR_OK;
}

QVariant NativeListItemObject::data() const {
    return QVariant::fromValue(static_cast<QObject*>(data_.data()));
}

