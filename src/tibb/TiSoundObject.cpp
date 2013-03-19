/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiSoundObject.h"
#include "TiGenericFunctionObject.h"
#include "NativeAudioPlayerObject.h"

TiSoundObject::TiSoundObject(const char* name)
    : TiUIBase(name)
{
}

TiSoundObject::TiSoundObject()
    : TiUIBase("")
{
}

TiSoundObject::~TiSoundObject()
{
}

TiSoundObject* TiSoundObject::createSoundObject(NativeObjectFactory* nativeObjectFactory)
{
	TiSoundObject* obj = new TiSoundObject;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiSoundObject::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "play", this, _play);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "stop", this, _stop);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "pause", this, _pause);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "release", this, _release);
}


void TiSoundObject::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_AUDIOPLAYER, this);
        setNativeObject(obj);
        obj->release();
    }
}

Handle<Value> TiSoundObject::_play(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiSoundObject* obj = (TiSoundObject*) userContext;
	NativeAudioPlayerObject* nativeAudioPlayerObject = (NativeAudioPlayerObject*) obj->getNativeObject();

	nativeAudioPlayerObject->play();

	return Undefined();
}

Handle<Value> TiSoundObject::_stop(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiSoundObject* obj = (TiSoundObject*) userContext;
	NativeAudioPlayerObject* nativeAudioPlayerObject = (NativeAudioPlayerObject*) obj->getNativeObject();

	nativeAudioPlayerObject->stop();


	return Undefined();
}

Handle<Value> TiSoundObject::_pause(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiSoundObject* obj = (TiSoundObject*) userContext;
	NativeAudioPlayerObject* nativeAudioPlayerObject = (NativeAudioPlayerObject*) obj->getNativeObject();

	nativeAudioPlayerObject->pause();

	return Undefined();
}

Handle<Value> TiSoundObject::_release(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiSoundObject* obj = (TiSoundObject*) userContext;
	NativeAudioPlayerObject* nativeAudioPlayerObject = (NativeAudioPlayerObject*) obj->getNativeObject();

	nativeAudioPlayerObject->mediaRelease();

	return Undefined();
}

