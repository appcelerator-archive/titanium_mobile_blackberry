/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include <bb/device/DeviceInfo>
#include <bb/device/DeviceOrientation>

#include "TiGesture.h"
#include "TiGenericFunctionObject.h"
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
    TiGenericFunctionObject::addGenericFunctionToParent(this, "isLandscape", this, _isLandscape);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "isPortrait", this, _isPortrait);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "isFaceUp", this, _isFaceUp);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "isFaceDown", this, _isFaceDown);
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

Handle<Value> TiGesture::_isLandscape(void* userContext, TiObject* caller, const Arguments& args)
{
	bb::device::DeviceInfo info;
    bb::device::DeviceOrientation::Type orientation = info.orientation();

    if(orientation == bb::device::DeviceOrientation::LeftUp || orientation == bb::device::DeviceOrientation::RightUp)
    {
    	return Boolean::New(true);
    }
    return Boolean::New(false);
}

Handle<Value> TiGesture::_isPortrait(void* userContext, TiObject* caller, const Arguments& args)
{
	bb::device::DeviceInfo info;
    bb::device::DeviceOrientation::Type orientation = info.orientation();
    if(orientation == bb::device::DeviceOrientation::TopUp || orientation == bb::device::DeviceOrientation::BottomUp)
    {
    	return Boolean::New(true);
    }
    return Boolean::New(false);
}

Handle<Value> TiGesture::_isFaceDown(void* userContext, TiObject* caller, const Arguments& args)
{
	bb::device::DeviceInfo info;
    bb::device::DeviceOrientation::Type orientation = info.orientation();

    if(orientation == bb::device::DeviceOrientation::FaceDown)
    {
    	return Boolean::New(true);
    }
    return Boolean::New(false);
}


Handle<Value> TiGesture::_isFaceUp(void* userContext, TiObject* caller, const Arguments& args)
{
	bb::device::DeviceInfo info;
    bb::device::DeviceOrientation::Type orientation = info.orientation();

    if(orientation == bb::device::DeviceOrientation::FaceUp)
    {
    	return Boolean::New(true);
    }
    return Boolean::New(false);
}
