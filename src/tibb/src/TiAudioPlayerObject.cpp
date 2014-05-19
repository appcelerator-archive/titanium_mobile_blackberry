/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiAudioPlayerObject.h"
#include "TiGenericFunctionObject.h"
#include "NativeAudioPlayerObject.h"

TiAudioPlayerObject::TiAudioPlayerObject()
    : TiUIBase("Player")
{
}

TiAudioPlayerObject::~TiAudioPlayerObject()
{
}

TiAudioPlayerObject* TiAudioPlayerObject::createAudioPlayerObject(NativeObjectFactory* nativeObjectFactory)
{
	TiAudioPlayerObject* obj = new TiAudioPlayerObject;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiAudioPlayerObject::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "play", this, _play);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "start", this, _start);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "stop", this, _stop);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "pause", this, _pause);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "release", this, _release);
}


void TiAudioPlayerObject::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_AUDIOPLAYER, this);
        setNativeObject(obj);
        obj->release();
    }
}

Handle<Value> TiAudioPlayerObject::_play(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiAudioPlayerObject* obj = (TiAudioPlayerObject*) userContext;
	NativeAudioPlayerObject* nativeAudioPlayerObject = (NativeAudioPlayerObject*) obj->getNativeObject();

	nativeAudioPlayerObject->play();

	return Undefined();
}

Handle<Value> TiAudioPlayerObject::_start(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiAudioPlayerObject* obj = (TiAudioPlayerObject*) userContext;
	NativeAudioPlayerObject* nativeAudioPlayerObject = (NativeAudioPlayerObject*) obj->getNativeObject();

	nativeAudioPlayerObject->play();

	return Undefined();
}

Handle<Value> TiAudioPlayerObject::_stop(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiAudioPlayerObject* obj = (TiAudioPlayerObject*) userContext;
	NativeAudioPlayerObject* nativeAudioPlayerObject = (NativeAudioPlayerObject*) obj->getNativeObject();

	nativeAudioPlayerObject->stop();

	return Undefined();
}

Handle<Value> TiAudioPlayerObject::_pause(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiAudioPlayerObject* obj = (TiAudioPlayerObject*) userContext;
	NativeAudioPlayerObject* nativeAudioPlayerObject = (NativeAudioPlayerObject*) obj->getNativeObject();

	nativeAudioPlayerObject->pause();

	return Undefined();
}

Handle<Value> TiAudioPlayerObject::_release(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiAudioPlayerObject* obj = (TiAudioPlayerObject*) userContext;
	NativeAudioPlayerObject* nativeAudioPlayerObject = (NativeAudioPlayerObject*) obj->getNativeObject();

	nativeAudioPlayerObject->mediaRelease();

	return Undefined();
}

