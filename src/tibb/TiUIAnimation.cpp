/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIAnimation.h"
#include "NativeAnimationObject.h"
#include <iostream>
#include "TiGenericFunctionObject.h"


const static TiProperty g_tiProperties[] = {
		{"anchorPoint", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_ANCHORPOINT},
		{"autoreverse", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_AUTOREVERSE},
		{"backgroundColor", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_BACKGROUNDCOLOR},
		{"bottom", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_BOTTOM},
		{"center", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_CENTER},
		{"color", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_COLOR},
		{"curve", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_CURVE},
		{"delay", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_DELAY},
		{"duration", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_DURATION},
		{"height", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_HEIGHT},
		{"left", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_LEFT},
		{"opacity", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_OPACITY},
		{"opaque", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_OPAQUE},
		{"repeat", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_REPEAT},
		{"right", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_RIGHT},
		{"top", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_TOP},
		{"transform", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_TRANSFORM},
		{"transition", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_TRANSITION},
		{"view", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_VIEW},
		{"visible", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_VISIBLE},
		{"width", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_WIDTH},
		{"zIndex", TI_PROP_PERMISSION_WRITE, N_ANIMATION_PROP_ZINDEX}
};

TiUIAnimation* TiUIAnimation::createAnimation(NativeObjectFactory* objectFactory) {
    TiUIAnimation* obj = new TiUIAnimation();
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

TiUIAnimation::TiUIAnimation()
    : TiProxy("Ti.UI.Animation") {
}

TiUIAnimation::~TiUIAnimation() {
}

void TiUIAnimation::onCreateStaticMembers() {
    TiProxy::onCreateStaticMembers();
    setTiMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));

}

void TiUIAnimation::initializeTiObject(TiObject* parentContext) {
    if (!isInitialized())
    {
        TiProxy::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_ANIMATION, this);
        setNativeObject(obj);
        obj->release();
    }
}

