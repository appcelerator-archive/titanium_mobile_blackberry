/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiVideoPlayerObject.h"
#include "TiGenericFunctionObject.h"
#include "NativeVideoPlayerObject.h"

TiVideoPlayerObject::TiVideoPlayerObject()
    : TiUIBase("Player")
{
}

TiVideoPlayerObject::~TiVideoPlayerObject()
{
}

TiVideoPlayerObject* TiVideoPlayerObject::createVideoPlayerObject(NativeObjectFactory* nativeObjectFactory)
{
	TiVideoPlayerObject* obj = new TiVideoPlayerObject;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiVideoPlayerObject::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "play", this, _play);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "start", this, _start);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "stop", this, _stop);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "pause", this, _pause);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "release", this, _release);
}


void TiVideoPlayerObject::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_VIDEOPLAYER, this);
        setNativeObject(obj);
        obj->release();
    }
}

Handle<Value> TiVideoPlayerObject::_play(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiVideoPlayerObject* obj = (TiVideoPlayerObject*) userContext;
	NativeVideoPlayerObject* nativeVideoPlayerObject = (NativeVideoPlayerObject*) obj->getNativeObject();

	nativeVideoPlayerObject->play();

	return Undefined();
}

Handle<Value> TiVideoPlayerObject::_start(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiVideoPlayerObject* obj = (TiVideoPlayerObject*) userContext;
	NativeVideoPlayerObject* nativeVideoPlayerObject = (NativeVideoPlayerObject*) obj->getNativeObject();

	nativeVideoPlayerObject->play();

	return Undefined();
}

Handle<Value> TiVideoPlayerObject::_stop(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiVideoPlayerObject* obj = (TiVideoPlayerObject*) userContext;
	NativeVideoPlayerObject* nativeVideoPlayerObject = (NativeVideoPlayerObject*) obj->getNativeObject();

	nativeVideoPlayerObject->stop();

	return Undefined();
}

Handle<Value> TiVideoPlayerObject::_pause(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiVideoPlayerObject* obj = (TiVideoPlayerObject*) userContext;
	NativeVideoPlayerObject* nativeVideoPlayerObject = (NativeVideoPlayerObject*) obj->getNativeObject();

	nativeVideoPlayerObject->pause();

	return Undefined();
}

Handle<Value> TiVideoPlayerObject::_release(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiVideoPlayerObject* obj = (TiVideoPlayerObject*) userContext;
	NativeVideoPlayerObject* nativeVideoPlayerObject = (NativeVideoPlayerObject*) obj->getNativeObject();

	nativeVideoPlayerObject->mediaRelease();

	return Undefined();
}

