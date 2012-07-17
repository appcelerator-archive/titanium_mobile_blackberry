/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEACTIVITYINDICATOROBJECT_H_
#define NATIVEACTIVITYINDICATOROBJECT_H_

#include "NativeProxyObject.h"

//forward declaration
namespace bb
{
namespace cascades
{
class ActivityIndicator;
}
}

/*
 * NativeActivityIndicatorObject
 *
 * UI: Activity Indicator
 */

class NativeActivityIndicatorObject : public NativeProxyObject
{
public:
    static NativeActivityIndicatorObject* createActivityIndicator();
    virtual int getObjectType() const;
    virtual int initialize();
    virtual NAHANDLE getNativeHandle() const;
    virtual int start();
    virtual int stop();

protected:
    virtual ~NativeActivityIndicatorObject();

private:
    explicit NativeActivityIndicatorObject();
    // Disable copy ctor & assignment operator
    NativeActivityIndicatorObject(const NativeActivityIndicatorObject& indicator);
    NativeActivityIndicatorObject& operator=(const NativeActivityIndicatorObject& indicator);
    bb::cascades::ActivityIndicator* indicator_;
};


#endif /* NATIVEACTIVITYINDICATOROBJECT_H_ */
