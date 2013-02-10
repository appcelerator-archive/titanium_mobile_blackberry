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
    : NativeControlObject(object)
    , data_(new ListItemData(object)) {
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

