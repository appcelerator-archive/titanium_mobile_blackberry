/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiGesture.h"

#include "NativeGestureObject.h"

const static TiProperty g_tiProperties[] = {
    { "orientation", TI_PROP_PERMISSION_READ, N_GESTURE_PROP_ORIENTATION }
};

TiGesture::TiGesture()
  : TiProxy("Gesture") {
}

void TiGesture::addObjectToParent(TiObject* parent, NativeObjectFactory* factory) {
    TiGesture* gesture = new TiGesture();
    gesture->setNativeObjectFactory(factory);
    parent->addMember(gesture);
    gesture->release();
}

void TiGesture::onCreateStaticMembers() {
    TiProxy::onCreateStaticMembers();
    setTiMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));
}

void TiGesture::initializeTiObject(TiObject* parentContext) {
    if (isInitialized()) {
        return;
    }

    TiProxy::initializeTiObject(parentContext);
    NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_GESTURE, this);
    setNativeObject(obj);
    obj->release();
}

