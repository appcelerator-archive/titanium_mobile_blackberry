/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiAudioRecorderObject.h"
#include "TiGenericFunctionObject.h"
#include "NativeAudioRecorderObject.h"

TiAudioRecorderObject::TiAudioRecorderObject()
    : TiUIBase("Recorder")
{
}

TiAudioRecorderObject::~TiAudioRecorderObject()
{
}

TiAudioRecorderObject* TiAudioRecorderObject::createAudioRecorderObject(NativeObjectFactory* nativeObjectFactory)
{
	TiAudioRecorderObject* obj = new TiAudioRecorderObject;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiAudioRecorderObject::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "start", this, _start);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "stop", this, _stop);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "pause", this, _pause);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "resume", this, _resume);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "release", this, _release);
}


void TiAudioRecorderObject::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_AUDIORECORDER, this);
        setNativeObject(obj);
        obj->release();
    }
}

Handle<Value> TiAudioRecorderObject::_start(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiAudioRecorderObject* obj = (TiAudioRecorderObject*) userContext;
	NativeAudioRecorderObject* nativeAudioRecorderObject = (NativeAudioRecorderObject*) obj->getNativeObject();

	nativeAudioRecorderObject->start();

	return Undefined();
}

Handle<Value> TiAudioRecorderObject::_stop(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiAudioRecorderObject* obj = (TiAudioRecorderObject*) userContext;
	NativeAudioRecorderObject* nativeAudioRecorderObject = (NativeAudioRecorderObject*) obj->getNativeObject();

	nativeAudioRecorderObject->stop();

	return Undefined();
}

Handle<Value> TiAudioRecorderObject::_resume(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiAudioRecorderObject* obj = (TiAudioRecorderObject*) userContext;
	NativeAudioRecorderObject* nativeAudioRecorderObject = (NativeAudioRecorderObject*) obj->getNativeObject();

	nativeAudioRecorderObject->stop();

	return Undefined();
}

Handle<Value> TiAudioRecorderObject::_pause(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiAudioRecorderObject* obj = (TiAudioRecorderObject*) userContext;
	NativeAudioRecorderObject* nativeAudioRecorderObject = (NativeAudioRecorderObject*) obj->getNativeObject();

	nativeAudioRecorderObject->pause();

	return Undefined();
}

Handle<Value> TiAudioRecorderObject::_release(void* userContext, TiObject*, const Arguments& args) {
	HandleScope handleScope;
	TiAudioRecorderObject* obj = (TiAudioRecorderObject*) userContext;
	NativeAudioRecorderObject* nativeAudioRecorderObject = (NativeAudioRecorderObject*) obj->getNativeObject();

	nativeAudioRecorderObject->mediaRelease();

	return Undefined();
}

