/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEPROGRESSBAROBJECT_H_
#define NATIVEPROGRESSBAROBJECT_H_

#include "NativeControlObject.h"
#include <bb/cascades/ProgressIndicator>

/*
 * NativeProgressBarObject
 *
 * UI: Progress bar control
 */

class NativeProgressBarObject : public NativeControlObject
{
public:
    NativeProgressBarObject();
    virtual ~NativeProgressBarObject();
    virtual int getObjectType() const;
    virtual int initialize(TiEventContainerFactory* containerFactory);
    virtual NAHANDLE getNativeHandle() const;
    virtual int setMax(TiObject* obj);
    virtual int setMin(TiObject* obj);
    virtual int setValue(TiObject* obj);

private:
    bb::cascades::ProgressIndicator* progressIndicator_;
};

#endif /* NATIVEPROGRESSBAROBJECT_H_ */
