/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVE_GEOLOCATION_OBJECT_H
#define NATIVE_GEOLOCATION_OBJECT_H

#include "NativeProxyObject.h"
#include "PropertyDelegate.h"

class NativeGeolocationObject
  : public NativeProxyObject
  , public titanium::PropertyDelegateBase<NativeGeolocationObject> {

public:
    explicit NativeGeolocationObject(TiObject* obj);

    NATIVE_TYPE getObjectType() const {
        return N_TYPE_GEOLOCATION;
    }

    int setPropertyValue(size_t propertyNumber, TiObject* obj);
    int getPropertyValue(size_t propertyNumber, TiObject* obj);
};

#endif
