/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_ACCELEROMETER_H
#define TI_ACCELEROMETER_H

#include "TiProxy.h"

class TiAccelerometer : public TiProxy {
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);

protected:
    virtual ~TiAccelerometer();

    virtual void onCreateStaticMembers();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiAccelerometer();
};

#endif
