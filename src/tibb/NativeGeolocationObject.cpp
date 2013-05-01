/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeGeolocationObject.h"

static NativeGeolocationObject::PropertyInfo properties[] = {
};

static const int propertyCount = sizeof(properties) / sizeof(properties[0]);

NativeGeolocationObject::NativeGeolocationObject(TiObject* obj)
  : NativeProxyObject(obj)
  , PropertyDelegateBase<NativeGeolocationObject>(this, properties, propertyCount) {
}

int NativeGeolocationObject::setPropertyValue(size_t propertyNumber, TiObject* obj) {
    return setProperty(propertyNumber, obj);
}

int NativeGeolocationObject::getPropertyValue(size_t propertyNumber, TiObject* obj) {
    return getProperty(propertyNumber, obj);
}

