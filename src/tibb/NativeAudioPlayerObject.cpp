/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeAudioPlayerObject.h"

#include <bb/cascades/SystemDefaults>
#include <bb/multimedia/BufferStatus>
#include <bb/multimedia/MediaPlayer>
#include <bb/multimedia/MediaState>

#include "NativeLoggerObject.h"
#include "NativeMessageStrings.h"
#include "TiConstants.h"
#include "TiEvent.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "V8Utils.h"
#include "TiCore.h"
 
using namespace bb::multimedia;
using namespace titanium;

NativeAudioPlayerObject::NativeAudioPlayerObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_AUDIOPLAYER), alwaysPrepare_(false)
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
    return N_TYPE_AUDIOPLAYER;
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
	QString url = V8ValueToQString(obj->getValue());
	if (url.startsWith("www.", Qt::CaseInsensitive) || url.startsWith("http://", Qt::CaseInsensitive) ||
								url.startsWith("https://", Qt::CaseInsensitive)) {
		audioSource = url;
	}
	else {
		audioSource = Ti::TiHelper::getAssetPath(url); // local file
	}


    player_->setSourceUrl(QUrl(audioSource));

    if (alwaysPrepare_) {
    	player_->prepare();
    }

	return NATIVE_ERROR_OK;
}

int NativeAudioPlayerObject::setBitRate(TiObject* obj)
{
	float bitRate;
	int error = NativeControlObject::getFloat(obj, &bitRate);

	if (error != NATIVE_ERROR_OK) {
		return error;
	}

    player_->setSpeed(bitRate);

	return NATIVE_ERROR_OK;
}

int NativeAudioPlayerObject::setRepeatMode(TiObject* obj)
{
	bool repeat;
	int error = NativeControlObject::getBoolean(obj, &repeat);

	if (error != NATIVE_ERROR_OK) {
		return error;
	}

	if (repeat) {
		player_->setRepeatMode(bb::multimedia::RepeatMode::All);
	} else {
		player_->setRepeatMode(bb::multimedia::RepeatMode::None);
	}


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

void NativeAudioPlayerObject::alwaysPrepare()
{
	alwaysPrepare_ = true;
}

void NativeAudioPlayerObject::setupEvents(TiEventContainerFactory* containerFactory)
{
	NativeControlObject::setupEvents(containerFactory);

	TiEventContainer* change = containerFactory->createEventContainer();
	change->setDataProperty("type", tetCHANGE);
	events_.insert(tetCHANGE, EventPairSmartPtr(change, new AudioPlayerObjectEventHandler(change, this)));

	TiEventContainer* completed = containerFactory->createEventContainer();
	change->setDataProperty("type", tetCOMPLETED);
	events_.insert(tetCOMPLETED, EventPairSmartPtr(completed,  new AudioPlayerObjectEventHandler(completed, this)));

	QObject::connect(player_, SIGNAL(bufferStatusChanged(bb::multimedia::BufferStatus::Type)), events_[tetCHANGE]->handler(), SLOT(changed(bb::multimedia::BufferStatus::Type)));
	QObject::connect(player_, SIGNAL(playbackCompleted()), events_[tetCOMPLETED]->handler(), SLOT(completed()));
	QObject::connect(player_, SIGNAL(repeatModeChanged(bb::multimedia::RepeatMode::Type)), events_[tetCHANGE]->handler(), SLOT(repeatModeChanged(bb::multimedia::RepeatMode::Type)));
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
	char* trackName = new char [playerObject_->audioSource.length()+8];
	sprintf(trackName, "track: %s", playerObject_->audioSource.toStdString().c_str());
	eventContainer_->setDataProperty("description", trackName);

	switch (bufferStatus)
	{
		case bb::multimedia::BufferStatus::Playing:
			eventContainer_->setDataProperty("state", "Playing");
			break;
		case  bb::multimedia::BufferStatus::Idle:
			eventContainer_->setDataProperty("state", "Idle");
			break;
		case  bb::multimedia::BufferStatus::Buffering:
			eventContainer_->setDataProperty("state", "Buffering");
			break;
		default:
			eventContainer_->setDataProperty("state", "Unknown");
			break;
	}

	eventContainer_->fireEvent();
}


void AudioPlayerObjectEventHandler::repeatModeChanged(bb::multimedia::RepeatMode::Type repeatMode)
{
	char* trackName = new char [playerObject_->audioSource.length()+8];
	sprintf(trackName, "track: %s", playerObject_->audioSource.toStdString().c_str());
	eventContainer_->setDataProperty("description", trackName);

	eventContainer_->setDataProperty("state", "Repeating");

	eventContainer_->fireEvent();
}




