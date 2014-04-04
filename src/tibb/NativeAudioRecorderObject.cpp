/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeAudioRecorderObject.h"

#include <bb/cascades/SystemDefaults>
#include <bb/multimedia/AudioRecorder>
#include <bb/multimedia/BufferStatus>
#include <bb/multimedia/MediaError>
#include <bb/multimedia/MediaState>

#include "NativeMessageStrings.h"
#include "TiConstants.h"
#include "TiEvent.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "V8Utils.h"

using namespace bb::multimedia;
using namespace titanium;

NativeAudioRecorderObject::NativeAudioRecorderObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_AUDIORECORDER)
{
}

NativeAudioRecorderObject::~NativeAudioRecorderObject()
{
	recorder_->reset();
}

NativeAudioRecorderObject* NativeAudioRecorderObject::createAudioRecorderObject(TiObject* tiObject)
{
    return new NativeAudioRecorderObject(tiObject);
}

NATIVE_TYPE NativeAudioRecorderObject::getObjectType() const
{
    return N_TYPE_AUDIORECORDER;
}

int NativeAudioRecorderObject::initialize()
{
	recorder_ = new AudioRecorder();

    return NATIVE_ERROR_OK;
}

int NativeAudioRecorderObject::getRecording(TiObject* obj)
{
	if (recorder_->mediaState() == bb::multimedia::MediaState::Started) {
		obj->setValue(Boolean::New(true));
	}
	else {
		obj->setValue(Boolean::New(false));
	}

	return NATIVE_ERROR_OK;
}

int NativeAudioRecorderObject::getPaused(TiObject* obj)
{
	if (recorder_->mediaState() == bb::multimedia::MediaState::Paused) {
		obj->setValue(Boolean::New(true));
	}
	else {
		obj->setValue(Boolean::New(false));
	}

	return NATIVE_ERROR_OK;
}

int NativeAudioRecorderObject::getStopped(TiObject* obj)
{
	if (recorder_->mediaState() == bb::multimedia::MediaState::Stopped) {
			obj->setValue(Boolean::New(true));
	}
	else {
		obj->setValue(Boolean::New(false));
	}

	return NATIVE_ERROR_OK;
}

int NativeAudioRecorderObject::setUrl(TiObject* obj)
{
	QString url = V8ValueToQString(obj->getValue());
	audioTarget =  "data/" + url; // local file

  recorder_->setOutputUrl(QUrl(audioTarget));

	return NATIVE_ERROR_OK;
}

// not implemented
int NativeAudioRecorderObject::setVolume(TiObject* obj)
{
	return NATIVE_ERROR_NOTSUPPORTED;
}

// not implemented
int NativeAudioRecorderObject::getVolume(TiObject* obj)
{
	return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeAudioRecorderObject::start()
{
	MediaError::Type type = recorder_->record();

	return NATIVE_ERROR_OK;
}

int NativeAudioRecorderObject::resume()
{
	recorder_->record();

	return NATIVE_ERROR_OK;
}

int NativeAudioRecorderObject::stop()
{
	recorder_->pause();

	return NATIVE_ERROR_OK;
}

int NativeAudioRecorderObject::pause()
{
	recorder_->pause();

	return NATIVE_ERROR_OK;
}

int NativeAudioRecorderObject::mediaRelease()
{
	recorder_->reset();

	return NATIVE_ERROR_OK;
}

void NativeAudioRecorderObject::setupEvents(TiEventContainerFactory* containerFactory)
{
	NativeControlObject::setupEvents(containerFactory);
}








