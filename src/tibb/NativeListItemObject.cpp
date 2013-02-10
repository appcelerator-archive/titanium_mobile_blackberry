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
    , data_(new ListItemData()) {
}

NativeListItemObject::~NativeListItemObject() {
}

int NativeListItemObject::setTitle(TiObject* obj) {
    data_->setProperty("title", TiObject::getStringFromValue(obj->getValue()));
}

