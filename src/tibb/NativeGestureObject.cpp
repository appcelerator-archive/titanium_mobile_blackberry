/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeGestureObject.h"

using namespace titanium;

static NativeGestureObject::PropertyInfo properties[] = {
};
static const int propertyCount = sizeof(properties) / sizeof(properties[0]);

NativeGestureObject::NativeGestureObject(TiObject* obj)
  : NativeProxyObject(obj)
  , PropertyDelegateBase<NativeGestureObject>(this, properties, propertyCount) {
}

NativeGestureObject* NativeGestureObject::createGesture(TiObject* obj) {
    return new NativeGestureObject(obj);
}

