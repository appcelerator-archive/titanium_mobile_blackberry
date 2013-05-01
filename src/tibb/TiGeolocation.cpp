/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiGeolocation.h"

TiGeolocation::TiGeolocation()
  : TiProxy("Geolocation") {
}

void TiGeolocation::addObjectToParent(TiObject* parent, NativeObjectFactory* factory) {
    TiGeolocation* geo = new TiGeolocation();
    geo->setNativeObjectFactory(factory);
    parent->addMember(geo);
    geo->release();
}

void TiGeolocation::onCreateStaticMembers() {
    TiProxy::onCreateStaticMembers();
}

void TiGeolocation::initializeTiObject(TiObject* parentContext) {
    if (isInitialized()) {
        return;
    }

    TiProxy::initializeTiObject(parentContext);
    NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_GEOLOCATION, this);
    setNativeObject(obj);
    obj->release();
}

