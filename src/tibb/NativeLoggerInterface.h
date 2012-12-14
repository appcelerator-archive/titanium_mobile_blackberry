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
 * Native Logger Interface to be used from the Native* classes.  This class 
 * should not need to be used directly; instead the N_* macros defined in 
 * NativeLoggerObject.h such as N_DEBUG should be used.  The macros accept
 * string concatenation in the parameter using the '<<' operator.
 *
 * See TiLogger.h for logging from the Ti* classes.
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
