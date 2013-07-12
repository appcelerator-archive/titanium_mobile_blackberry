/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeVideoPlayerObject.h"

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

#include <bb/cascades/ForeignWindowControl>
#include <bb/multimedia/VideoOutput>


using namespace bb::multimedia;
using namespace bb::cascades;
using namespace titanium;

NativeVideoPlayerObject::NativeVideoPlayerObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_VIDEOPLAYER), alwaysPrepare_(false)
{
}

NativeVideoPlayerObject::~NativeVideoPlayerObject()
{
	player_->reset();
}

NativeVideoPlayerObject* NativeVideoPlayerObject::createVideoPlayerObject(TiObject* tiObject)
{
    return new NativeVideoPlayerObject(tiObject);
}

NATIVE_TYPE NativeVideoPlayerObject::getObjectType() const
{
    return N_TYPE_VIDEOPLAYER;
}

int NativeVideoPlayerObject::initialize()
{
	player_ = new MediaPlayer();

	// create unique id for this window
	QString uid = QUuid::createUuid().toString();
	foreignWindow_ =  ForeignWindowControl::create()
	        .windowId(uid).updatedProperties(
					WindowProperty::Size | WindowProperty::Position
							| WindowProperty::Visible);
	player_->setWindowId(foreignWindow_->windowId());
	player_->setVideoOutput(VideoOutput::PrimaryDisplay);

	setControl(foreignWindow_);

    return NATIVE_ERROR_OK;
}

int NativeVideoPlayerObject::getPlaying(TiObject* obj)
{
	if (player_->bufferStatus() == bb::multimedia::BufferStatus::Playing) {
		obj->setValue(Boolean::New(true));
	}
	else {
		obj->setValue(Boolean::New(false));
	}

	return NATIVE_ERROR_OK;
}

int NativeVideoPlayerObject::getPaused(TiObject* obj)
{
	if (player_->mediaState() == bb::multimedia::MediaState::Paused) {
		obj->setValue(Boolean::New(true));
	}
	else {
		obj->setValue(Boolean::New(false));
	}

	return NATIVE_ERROR_OK;
}

int NativeVideoPlayerObject::getProgress(TiObject* obj)
{
	obj->setValue(Number::New(player_->position()));
	return NATIVE_ERROR_OK;
}

int NativeVideoPlayerObject::setUrl(TiObject* obj)
{
	QString url = V8ValueToQString(obj->getValue());
	if (url.startsWith("www.", Qt::CaseInsensitive) || url.startsWith("http://", Qt::CaseInsensitive) ||
								url.startsWith("https://", Qt::CaseInsensitive)) {
		videoSource = url;
	}
	else {
		videoSource = "app/native/assets/" + url; // local file
	}

    player_->setSourceUrl(QUrl(videoSource));

    if (alwaysPrepare_) {
    	player_->prepare();
    }

	return NATIVE_ERROR_OK;
}

int NativeVideoPlayerObject::setRepeatMode(TiObject* obj)
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
int NativeVideoPlayerObject::setVolume(TiObject* obj)
{
	return NATIVE_ERROR_NOTSUPPORTED;
}

// not implemented
int NativeVideoPlayerObject::getVolume(TiObject* obj)
{
	return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeVideoPlayerObject::start()
{
	player_->play();

	return NATIVE_ERROR_OK;
}

int NativeVideoPlayerObject::play()
{
	player_->play();

	return NATIVE_ERROR_OK;
}

int NativeVideoPlayerObject::stop()
{
	player_->stop();

	return NATIVE_ERROR_OK;
}

int NativeVideoPlayerObject::pause()
{
	player_->pause();

	return NATIVE_ERROR_OK;
}

int NativeVideoPlayerObject::mediaRelease()
{
	player_->reset();

	return NATIVE_ERROR_OK;
}

void NativeVideoPlayerObject::alwaysPrepare()
{
	alwaysPrepare_ = true;
}

void NativeVideoPlayerObject::setupEvents(TiEventContainerFactory* containerFactory)
{
	NativeControlObject::setupEvents(containerFactory);

	TiEventContainer* change = containerFactory->createEventContainer();
	change->setDataProperty("type", tetCHANGE);
	events_.insert(tetCHANGE, EventPairSmartPtr(change, new VideoPlayerObjectEventHandler(change, this)));

	TiEventContainer* completed = containerFactory->createEventContainer();
	change->setDataProperty("type", tetCOMPLETED);
	events_.insert(tetCOMPLETED, EventPairSmartPtr(completed,  new VideoPlayerObjectEventHandler(completed, this)));

	QObject::connect(player_, SIGNAL(bufferStatusChanged(bb::multimedia::BufferStatus::Type)),
							events_[tetCHANGE]->handler(), SLOT(changed(bb::multimedia::BufferStatus::Type)));
	QObject::connect(player_, SIGNAL(playbackCompleted()), events_[tetCOMPLETED]->handler(),
							SLOT(completed()));
	QObject::connect(player_, SIGNAL(repeatModeChanged(bb::multimedia::RepeatMode::Type)),
							events_[tetCHANGE]->handler(), SLOT(repeatModeChanged(bb::multimedia::RepeatMode::Type)));
	QObject::connect(foreignWindow_, SIGNAL(windowAttached(screen_window_t, QString, QString)),
							events_[tetCHANGE]->handler(),
							SLOT(windowAttached(screen_window_t, QString, QString)));
}


VideoPlayerObjectEventHandler::VideoPlayerObjectEventHandler(TiEventContainer* eventContainer, NativeVideoPlayerObject* playerObject)
{
    eventContainer_ = eventContainer;
    playerObject_ = playerObject;
}

VideoPlayerObjectEventHandler::~VideoPlayerObjectEventHandler() {
}

void VideoPlayerObjectEventHandler::completed()
{
	eventContainer_->fireEvent();
}

void VideoPlayerObjectEventHandler::changed(bb::multimedia::BufferStatus::Type bufferStatus)
{
	char* trackName = new char [playerObject_->videoSource.length()+8];
	sprintf(trackName, "track: %s", playerObject_->videoSource.toStdString().c_str());
	eventContainer_->setDataProperty("description", trackName);

	int width = playerObject_->player_->videoDimensions().width();
	int height = playerObject_->player_->videoDimensions().height();

	eventContainer_->setDataProperty("videoWidth", width);
	eventContainer_->setDataProperty("videoHeight", height);

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


void VideoPlayerObjectEventHandler::repeatModeChanged(bb::multimedia::RepeatMode::Type repeatMode)
{
	char* trackName = new char [playerObject_->videoSource.length()+8];
	sprintf(trackName, "track: %s", playerObject_->videoSource.toStdString().c_str());
	eventContainer_->setDataProperty("description", trackName);

	eventContainer_->setDataProperty("state", "Repeating");

	eventContainer_->fireEvent();
}

void VideoPlayerObjectEventHandler::windowAttached(screen_window_t screen, QString winGroup, QString winId)
{
	eventContainer_->setDataProperty("state", "Foreign Window Attached");

	eventContainer_->fireEvent();
}




