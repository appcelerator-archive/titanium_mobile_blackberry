/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVELOGGERINTERFACE_H_
#define NATIVELOGGERINTERFACE_H_

#include "NativeObject.h"


/*
 * NativeLoggerInterface
 *
 * Native Logger Interface
 */

class NativeLoggerInterface : public NativeObject
{
public:
    virtual void log(const char* msg) = 0;
    virtual void deleteInstance() = 0;

protected:
    explicit NativeLoggerInterface(TiObject* tiObject) : NativeObject(tiObject) {};
    virtual ~NativeLoggerInterface() {};

private:
    // Disable copy ctor & assignment operator
    NativeLoggerInterface(const NativeLoggerInterface& indicator);
    NativeLoggerInterface& operator=(const NativeLoggerInterface& indicator);
};

#endif /* NATIVELOGGERINTERFACE_H_ */
