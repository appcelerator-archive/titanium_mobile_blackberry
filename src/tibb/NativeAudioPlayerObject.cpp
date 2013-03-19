/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeAudioPlayerObject.h"
#include "TiEvent.h"
#include "TiConstants.h"
#include "TiEventContainerFactory.h"
#include "NativeLoggerObject.h"
#include "NativeMessageStrings.h"
#include <bb/cascades/SystemDefaults>
#include <bb/multimedia/MediaPlayer>
#include <bb/multimedia/MediaState>
#include <bb/multimedia/BufferStatus>
#include "TiObject.h"

using namespace bb::multimedia;


NativeAudioPlayerObject::NativeAudioPlayerObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_AUDIOPLAYER)
{
}

NativeAudioPlayerObject::~NativeAudioPlayerObject()
{
	player_->reset();
}

NativeAudioPlayerObject* NativeAudioPlayerObject::createAudioPlayerObject(TiObject* tiObject)
{
    return new NativeAudioPlayerObject(tiObject);
}

NATIVE_TYPE NativeAudioPlayerObject::getObjectType() const
{
    return N_TYPE_ANNOTATION;
}

int NativeAudioPlayerObject::initialize()
{
	player_ = new MediaPlayer();

    return NATIVE_ERROR_OK;
}

int NativeAudioPlayerObject::getPlaying(TiObject* obj)
{
	if (player_->bufferStatus() == bb::multimedia::BufferStatus::Playing) {
		obj->setValue(Boolean::New(true));
	}
	else {
		obj->setValue(Boolean::New(false));
	}

	return NATIVE_ERROR_OK;
}

int NativeAudioPlayerObject::getPaused(TiObject* obj)
{
	if (player_->mediaState() == bb::multimedia::MediaState::Paused) {
		obj->setValue(Boolean::New(true));
	}
	else {
		obj->setValue(Boolean::New(false));
	}

	return NATIVE_ERROR_OK;
}

int NativeAudioPlayerObject::getProgress(TiObject* obj)
{
	obj->setValue(Number::New(player_->position()));
	return NATIVE_ERROR_OK;
}

int NativeAudioPlayerObject::setUrl(TiObject* obj)
{
	QString url;
	int error = NativeControlObject::getString(obj, url);

	if (error != NATIVE_ERROR_OK)
	{
		return error;
	}

	audioSource_ = url;
    player_->setSourceUrl(QUrl(audioSource_));

	return NATIVE_ERROR_OK;
}

// not implemented
int NativeAudioPlayerObject::setVolume(TiObject* obj)
{
	return NATIVE_ERROR_NOTSUPPORTED;
}

// not implemented
int NativeAudioPlayerObject::getVolume(TiObject* obj)
{
	return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeAudioPlayerObject::start()
{
	player_->play();

	return NATIVE_ERROR_OK;
}

int NativeAudioPlayerObject::play()
{
	player_->play();

	return NATIVE_ERROR_OK;
}

int NativeAudioPlayerObject::stop()
{
	player_->stop();

	return NATIVE_ERROR_OK;
}

int NativeAudioPlayerObject::pause()
{
	player_->pause();

	return NATIVE_ERROR_OK;
}

int NativeAudioPlayerObject::mediaRelease()
{
	player_->reset();

	return NATIVE_ERROR_OK;
}

void NativeAudioPlayerObject::setupEvents(TiEventContainerFactory* containerFactory)
{
	NativeControlObject::setupEvents(containerFactory);

	TiEventContainer* change = containerFactory->createEventContainer();
	change->setDataProperty("type", tetCHANGE);
	events_.insert(tetCHANGE, EventPairSmartPtr(change, new AudioPlayerObjectEventHandler(change, this)));

	QObject::connect(player_, SIGNAL(bufferStatusChanged(bb::multimedia::BufferStatus::Type bufferState)), events_[tetCHANGE]->handler(), SLOT(changed(bb::multimedia::BufferStatus::Type bufferStatus)));
	QObject::connect(player_, SIGNAL(playbackCompleted()), events_[tetCHANGE]->handler(), SLOT(completed()));
}


AudioPlayerObjectEventHandler::AudioPlayerObjectEventHandler(TiEventContainer* eventContainer, NativeAudioPlayerObject* playerObject)
{
    eventContainer_ = eventContainer;
    playerObject_ = playerObject;
}

AudioPlayerObjectEventHandler::~AudioPlayerObjectEventHandler() {
}

void AudioPlayerObjectEventHandler::completed()
{
	eventContainer_->fireEvent();
}

void AudioPlayerObjectEventHandler::changed(bb::multimedia::BufferStatus::Type bufferStatus)
{
	eventContainer_->setDataProperty("description", "playing");

	eventContainer_->fireEvent();
}







