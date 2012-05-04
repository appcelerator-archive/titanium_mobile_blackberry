/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEACTIVITYINDICATOROBJECT_H_
#define NATIVEACTIVITYINDICATOROBJECT_H_

#include "NativeControlObject.h"
#include <bb/cascades/ActivityIndicator>

/*
 * NativeActivityIndicatorObject
 *
 * UI: Activity Indicator
 */

class NativeActivityIndicatorObject : public NativeControlObject
{
public:
	NativeActivityIndicatorObject();
    virtual ~NativeActivityIndicatorObject();
    virtual int getObjectType() const;
    virtual int initialize(TiEventContainerFactory* containerFactory);
    virtual NAHANDLE getNativeHandle() const;
    virtual int start();
    virtual int stop();

private:
    bb::cascades::ActivityIndicator* indicator_;
};


#endif /* NATIVEACTIVITYINDICATOROBJECT_H_ */
