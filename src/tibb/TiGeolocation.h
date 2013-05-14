/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_GEOLOCATION_H
#define TI_GEOLOCATION_H

#include "TiProxy.h"

class TiGeolocation : public TiProxy {
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* factory);

    virtual void onCreateStaticMembers();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiGeolocation();
};

#endif
