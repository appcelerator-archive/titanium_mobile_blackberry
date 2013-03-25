/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiMedia.h"

#include "KeyboardType.h"
#include "Scene.h"
#include "TiCascadesApp.h"
#include "TiConstants.h"
#include "TiGenericFunctionObject.h"
#include "TiAudioPlayerObject.h"
#include "TiSoundObject.h"
#include "TiAudioRecorderObject.h"

#include <string.h>

using namespace titanium;

TiMedia::TiMedia()
    : TiProxy("Media")
{
    objectFactory_ = NULL;
    contentContainer_ = NULL;
}

TiMedia::TiMedia(NativeObjectFactory* objectFactory)
    : TiProxy("Media")
{
    objectFactory_ = objectFactory;
    contentContainer_ = NULL;
}

TiMedia::~TiMedia()
{
}

void TiMedia::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory)
{
    TiMedia* obj = new TiMedia(objectFactory);
    parent->addMember(obj);
    obj->release();
}

void TiMedia::onCreateStaticMembers()
{
    HandleScope scope;

    TiProxy::onCreateStaticMembers();

    TiGenericFunctionObject::addGenericFunctionToParent(this, "createAudioPlayer", this, _createAudioPlayer);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createAudioRecorder", this, _createAudioRecorder);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createSound", this, _createSound);

    // Todo fill in contants
    // Adding javascript constants from Ti.Media
    ADD_STATIC_TI_VALUE("AUDIO_FILEFORMAT_MP3", Number::New(Ti::Media::AUDIO_FILEFORMAT_MP3), this);
    ADD_STATIC_TI_VALUE("AUDIO_FILEFORMAT_MP4", Number::New(Ti::Media::AUDIO_FILEFORMAT_MP4), this);
    ADD_STATIC_TI_VALUE("AUDIO_FILEFORMAT_WAVE", Number::New(Ti::Media::AUDIO_FILEFORMAT_WAVE), this);
}

Handle<Value> TiMedia::_createControlHelper(void* userContext, CREATEOBJECTCALLBACK createCallback, const Arguments& args)
{
    HandleScope handleScope;
    TiMedia* obj = (TiMedia*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result;
    result = global->NewInstance();
    TiProxy* newControl = (createCallback)(obj->objectFactory_);
    newControl->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        newControl->setParametersFromObject(newControl, settingsObj);
    }
    setTiObjectToJsObject(result, newControl);
    return handleScope.Close(result);
}

Handle<Value> TiMedia::_createAudioPlayer(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiAudioPlayerObject::createAudioPlayerObject, args);
}

Handle<Value> TiMedia::_createSound(void* userContext, TiObject*, const Arguments& args)
{
	 return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiSoundObject::createSoundObject, args);
}

Handle<Value> TiMedia::_createAudioRecorder(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiAudioRecorderObject::createAudioRecorderObject, args);
}


