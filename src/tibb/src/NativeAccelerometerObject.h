/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVE_ACCELEROMETER_OBJECT_H
#define NATIVE_ACCELEROMETER_OBJECT_H

#include "NativeProxyObject.h"

class AccelerometerEventHandler;

class NativeAccelerometerObject : public NativeProxyObject {
public:
    explicit NativeAccelerometerObject(TiObject* obj);
    virtual ~NativeAccelerometerObject();

    virtual int setEventHandler(const char* eventName, TiEvent* event);
    virtual int removeEventHandler(const char* eventName, int eventId);

protected:
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    AccelerometerEventHandler* accelerometerHandler_;
    int listenerCount_;
};

#endif
