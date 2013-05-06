/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */ #include "TiAccelerometer.h"

TiAccelerometer::TiAccelerometer()
  : TiProxy("Accelerometer") {
}

TiAccelerometer::~TiAccelerometer() {
}

void TiAccelerometer::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory) {
    TiAccelerometer* module = new TiAccelerometer();
    module->setNativeObjectFactory(objectFactory);
    parent->addMember(module);
    module->release();
}

void TiAccelerometer::onCreateStaticMembers() {
    TiProxy::onCreateStaticMembers();
}

void TiAccelerometer::initializeTiObject(TiObject* parentContext) {
    if (isInitialized()) {
        return;
    }

    TiProxy::initializeTiObject(parentContext);
    NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_ACCELEROMETER, this);
    setNativeObject(obj);
    obj->release();
}

