/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeListItemObject.h"

#include "TiObject.h"

NativeListItemObject::NativeListItemObject(TiObject* object)
    : NativeControlObject(object) {
}

NativeListItemObject::~NativeListItemObject() {
}

int NativeListItemObject::setTitle(TiObject* obj) {
    data_["title"] = TiObject::getStringFromValue(obj->getValue());
}

