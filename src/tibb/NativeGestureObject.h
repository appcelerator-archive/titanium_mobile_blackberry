/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVE_GESTURE_OBJECT_H
#define NATIVE_GESTURE_OBJECT_H

#include "NativeProxyObject.h"
#include "PropertyDelegate.h"

enum N_GESTURE_PROPS {
};

class NativeGestureObject : public NativeProxyObject,
                            public titanium::PropertyDelegateBase<NativeGestureObject> {
public:
    static NativeGestureObject* createGesture(TiObject* object);
    NATIVE_TYPE getObjectType() const {
        return N_TYPE_GESTURE;
    }

private:
    NativeGestureObject(TiObject* obj);
};

#endif
