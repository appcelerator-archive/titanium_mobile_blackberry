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
    N_GESTURE_PROP_ORIENTATION
};

class ShakeEventHandler;

class NativeGestureObject : public NativeProxyObject,
                            public titanium::PropertyDelegateBase<NativeGestureObject> {
public:
    static NativeGestureObject* createGesture(TiObject* object);
    NATIVE_TYPE getObjectType() const {
        return N_TYPE_GESTURE;
    }

    int setPropertyValue(size_t propertyNumber, TiObject* obj);
    int getPropertyValue(size_t propertyNumber, TiObject* obj);
    virtual int setEventHandler(const char* eventName, TiEvent* event);
    virtual int removeEventHandler(const char* eventName, int eventId);

    int getOrientation(TiObject* value);

protected:
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    NativeGestureObject(TiObject* obj);

    ShakeEventHandler* shakeHandler_;
    int shakeListenerCount_;
};

#endif
