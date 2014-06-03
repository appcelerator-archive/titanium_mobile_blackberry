/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiMediaAudioPlayerProxy.h"
namespace TiMedia {

TiMediaAudioPlayerProxy::TiMediaAudioPlayerProxy(const char* name) : Ti::TiProxy(name), _autoPlay(false)
{
	createPropertyFunction("isPaused", _isPaused);
	createPropertyFunction("isPlaying", _isPlaying);
	createPropertyFunction("pause", _pause);
	createPropertyFunction("play", _play);
	createPropertyFunction("release", _release);
	createPropertyFunction("start", _start);
	createPropertyFunction("stateDescription", _stateDescription);
	createPropertyFunction("stop", _stop);

	createPropertySetterGetter("allowBackground", _setAllowBackground, _getAllowBackground);
	createPropertySetterGetter("autoplay", _setAutoplay, _getAutoplay);
	createPropertySetterGetter("bitRate", _setBitRate, _getBitRate);
	createPropertySetterGetter("bufferSize", _setBufferSize, _getBufferSize);
	createPropertySetterGetter("idle", _setIdle, _getIdle);
	createPropertySetterGetter("paused", _setPaused, _getPaused);
	createPropertySetterGetter("playing", _setPlaying, _getPlaying);
	createPropertySetterGetter("progress", _setProgress, _getProgress);
	createPropertySetterGetter("repeatMode", _setRepeatMode, _getRepeatMode);
	createPropertySetterGetter("state", _setState, _getState);
	createPropertySetterGetter("url", _setUrl, _getUrl);
	createPropertySetterGetter("volume", _setVolume, _getVolume);
	createPropertySetterGetter("waiting", _setWaiting, _getWaiting);
	TiMediaAudioPlayerEventHandler* eventHandler = new TiMediaAudioPlayerEventHandler(this);

	_mediaPlayer = new bb::multimedia::MediaPlayer();


	QObject::connect(_mediaPlayer, SIGNAL(bufferStatusChanged(bb::multimedia::BufferStatus::Type)), eventHandler, SLOT(onChanged(bb::multimedia::BufferStatus::Type)));
	QObject::connect(_mediaPlayer, SIGNAL(playbackCompleted()), eventHandler, SLOT(onCompleted()));
	QObject::connect(_mediaPlayer, SIGNAL(repeatModeChanged(bb::multimedia::RepeatMode::Type)), eventHandler, SLOT(onRepeatModeChanged(bb::multimedia::RepeatMode::Type)));
	QObject::connect(_mediaPlayer, SIGNAL(error(bb::multimedia::MediaError::Type, unsigned int)), eventHandler, SLOT(onError(bb::multimedia::MediaError::Type, unsigned int)));
}

TiMediaAudioPlayerProxy::~TiMediaAudioPlayerProxy()
{
	_mediaPlayer->deleteLater();
}


TI_GETTER_DEFER(TiMediaAudioPlayerProxy, getAllowBackground)
void TiMediaAudioPlayerProxy::setAllowBackground(Ti::TiValue val)
{

}
TI_GETTER_DEFER(TiMediaAudioPlayerProxy, getAutoplay)
void TiMediaAudioPlayerProxy::setAutoplay(Ti::TiValue val)
{
	_autoPlay = val.toBool();
}
TI_GETTER_DEFER(TiMediaAudioPlayerProxy, getBitRate)
void TiMediaAudioPlayerProxy::setBitRate(Ti::TiValue val)
{
	_mediaPlayer->setSpeed(val.toNumber());
}
TI_GETTER_DEFER(TiMediaAudioPlayerProxy, getBufferSize)
void TiMediaAudioPlayerProxy::setBufferSize(Ti::TiValue val)
{

}
TI_GETTER_DEFER(TiMediaAudioPlayerProxy, getIdle)
void TiMediaAudioPlayerProxy::setIdle(Ti::TiValue val)
{

}
Ti::TiValue TiMediaAudioPlayerProxy::getPaused() \
{
	return isPaused(Ti::TiValue());
}
void TiMediaAudioPlayerProxy::setPaused(Ti::TiValue val)
{
	if(val.toBool()) {
		if (_mediaPlayer->bufferStatus() == bb::multimedia::BufferStatus::Playing) {
			_mediaPlayer->pause();
		}
	} else {
		_mediaPlayer->play();
	}
}
Ti::TiValue TiMediaAudioPlayerProxy::getPlaying()
{
	return isPlaying(Ti::TiValue());
}
void TiMediaAudioPlayerProxy::setPlaying(Ti::TiValue val)
{
	if(!val.toBool()) {
		if (_mediaPlayer->bufferStatus() == bb::multimedia::BufferStatus::Playing) {
			_mediaPlayer->pause();
		}
	} else {
		_mediaPlayer->play();
	}
}
Ti::TiValue TiMediaAudioPlayerProxy::getProgress()
{
	Ti::TiValue returnValue;
	returnValue.setBool(_mediaPlayer->position());
	return returnValue;
}
void TiMediaAudioPlayerProxy::setProgress(Ti::TiValue val)
{
}

TI_GETTER_DEFER(TiMediaAudioPlayerProxy, getRepeatMode)
void TiMediaAudioPlayerProxy::setRepeatMode(Ti::TiValue val)
{
	if (val.toBool()) {
		_mediaPlayer->setRepeatMode(bb::multimedia::RepeatMode::All);
	} else {
		_mediaPlayer->setRepeatMode(bb::multimedia::RepeatMode::None);
	}

}
TI_GETTER_DEFER(TiMediaAudioPlayerProxy, getState)
void TiMediaAudioPlayerProxy::setState(Ti::TiValue val)
{

}
TI_GETTER_DEFER(TiMediaAudioPlayerProxy, getUrl)
void TiMediaAudioPlayerProxy::setUrl(Ti::TiValue val)
{
	QString url = val.toString();
	QString audioSource;
	if (
			url.startsWith("www.", Qt::CaseInsensitive) ||
			url.startsWith("http://", Qt::CaseInsensitive) ||
			url.startsWith("https://", Qt::CaseInsensitive)) {
		audioSource = QString(url);
	}
	else
	{
		audioSource = Ti::TiHelper::getAssetPath(url);
		audioSource.replace(audioSource.indexOf("assets/"), QString("assets/").size(), "asset:///"); // local file
	}
	bb::multimedia::MediaError::Type err = _mediaPlayer->setSourceUrl(QUrl(audioSource));

	_mediaPlayer->prepare();
    if (_autoPlay) {
    	_mediaPlayer->play();
    }

}
TI_GETTER_DEFER(TiMediaAudioPlayerProxy, getVolume)
void TiMediaAudioPlayerProxy::setVolume(Ti::TiValue val)
{

}
TI_GETTER_DEFER(TiMediaAudioPlayerProxy, getWaiting)
void TiMediaAudioPlayerProxy::setWaiting(Ti::TiValue val)
{

}
Ti::TiValue TiMediaAudioPlayerProxy::isPaused(Ti::TiValue val)
{
	Ti::TiValue returnValue;
	returnValue.setBool(_mediaPlayer->mediaState() == bb::multimedia::MediaState::Paused);
	return returnValue;
}
Ti::TiValue TiMediaAudioPlayerProxy::isPlaying(Ti::TiValue val)
{
	Ti::TiValue returnValue;
	if (_mediaPlayer->bufferStatus() == bb::multimedia::BufferStatus::Playing) {
		returnValue.setBool(true);
	} else {
		returnValue.setBool(false);
	}
	return returnValue;
}
Ti::TiValue TiMediaAudioPlayerProxy::pause(Ti::TiValue val)
{
	_mediaPlayer->pause();
	return Ti::TiValue();
}
Ti::TiValue TiMediaAudioPlayerProxy::play(Ti::TiValue val)
{
	_mediaPlayer->play();
	return Ti::TiValue();
}
Ti::TiValue TiMediaAudioPlayerProxy::release(Ti::TiValue val)
{
	_mediaPlayer->reset();
	return Ti::TiValue();
}
Ti::TiValue TiMediaAudioPlayerProxy::start(Ti::TiValue val)
{
	_mediaPlayer->play();
	return Ti::TiValue();
}
Ti::TiValue TiMediaAudioPlayerProxy::stateDescription(Ti::TiValue val)
{
	return Ti::TiValue();
}
Ti::TiValue TiMediaAudioPlayerProxy::stop(Ti::TiValue val)
{
	_mediaPlayer->stop();
	return Ti::TiValue();
}

bb::multimedia::MediaPlayer* TiMediaAudioPlayerProxy::getNativeMediaPlayer()
{
	return _mediaPlayer;
}

TiMediaAudioPlayerEventHandler::TiMediaAudioPlayerEventHandler(TiMediaAudioPlayerProxy* proxy) : _proxy(proxy)
{

}
TiMediaAudioPlayerEventHandler::~TiMediaAudioPlayerEventHandler()
{

}
void TiMediaAudioPlayerEventHandler::onChanged(bb::multimedia::BufferStatus::Type status)
{
	QString type;
	switch (status)
	{
		case bb::multimedia::BufferStatus::Playing: type = "playing"; break;
		case bb::multimedia::BufferStatus::Idle: type = "idle"; break;
		case bb::multimedia::BufferStatus::Buffering: type = "buffering"; break;
		default: type = "unknown"; break;
	}
	Ti::TiEventParameters params;
	params.addParam("description", _proxy->getNativeMediaPlayer()->sourceUrl().toString());
	params.addParam("state", type);
	params.addParam("type", Ti::TiConstants::EventChange);
	_proxy->fireEvent(Ti::TiConstants::EventChange, params);
}
void TiMediaAudioPlayerEventHandler::onCompleted()
{
	Ti::TiEventParameters params;
	params.addParam("type", Ti::TiConstants::EventComplete);
	_proxy->fireEvent(Ti::TiConstants::EventComplete, params);
}
void TiMediaAudioPlayerEventHandler::onRepeatModeChanged(bb::multimedia::RepeatMode::Type)
{
	Ti::TiEventParameters params;
	params.addParam("description", _proxy->getNativeMediaPlayer()->sourceUrl().toString());
	params.addParam("state", "repeating");
	params.addParam("type", Ti::TiConstants::EventChange);
	_proxy->fireEvent(Ti::TiConstants::EventChange, params);
}

void TiMediaAudioPlayerEventHandler::onError(bb::multimedia::MediaError::Type type, unsigned int position)
{
	if(type == bb::multimedia::MediaError::None) return;
	QString description;
	switch(type)
	{
	case  bb::multimedia::MediaError::Internal: description = "An unexpected internal error."; break;
	case  bb::multimedia::MediaError::InvalidParameter: description = "An invalid parameter."; break;
	case  bb::multimedia::MediaError::InvalidState: description = "An illegal operation given the context state."; break;
	case  bb::multimedia::MediaError::UnsupportedValue: description = "An unrecognized input or output type or an out-of-range speed setting."; break;
	case  bb::multimedia::MediaError::UnsupportedMediaType: description = "A data format not recognized by any plugin."; break;
	case  bb::multimedia::MediaError::DrmProtected: description = "The file is DRM-protected."; break;
	case  bb::multimedia::MediaError::UnsupportedOperation: description = "An illegal operation."; break;
	case  bb::multimedia::MediaError::Read: description = "An I/O error at the source."; break;
	case  bb::multimedia::MediaError::Write: description = "An I/O error at the sink."; break;
	case  bb::multimedia::MediaError::SourceUnavailable: description = "Cannot open the source."; break;
	case  bb::multimedia::MediaError::ResourceCorrupted: description = "Found corrupt data on the DVD."; break;
	case  bb::multimedia::MediaError::OutputUnavailable: description = "Cannot open the sink (possibly because no plugin recognizes it)."; break;
	case  bb::multimedia::MediaError::OutOfMemory: description = "Insufficient memory to perform the requested operation."; break;
	case  bb::multimedia::MediaError::ResourceUnavailable: description = "A required resource such as an encoder or an output feed is presently unavailable."; break;
	case  bb::multimedia::MediaError::DrmNoRights: description = "The client has insufficient digital permissions to play the file."; break;
	case  bb::multimedia::MediaError::DrmCorruptedDataStore: description = "The DRM data store is corrupted."; break;
	case  bb::multimedia::MediaError::DrmOutputRestricted: description = "A DRM output protection mismatch on an unspecified output."; break;
	case  bb::multimedia::MediaError::DrmHdmiOutputRestricted: description = "A DRM output protection mismatch on an HDMI output."; break;
	case  bb::multimedia::MediaError::DrmDisplayPortOutputRestricted: description = "A DRM output protection mismatch on a DISPLAYPORT output."; break;
	case  bb::multimedia::MediaError::DrmDviOutputRestricted: description = "A DRM output protection mismatch on a DVI output."; break;
	case  bb::multimedia::MediaError::DrmAnalogVideoOutputRestricted: description = "A DRM output protection mismatch on a video ANALOG output."; break;
	case  bb::multimedia::MediaError::DrmAnalogAudioOutputRestricted: description = "A DRM output protection mismatch on an audio ANALOG output."; break;
	case  bb::multimedia::MediaError::DrmToslinkOutputRestricted: description = "A DRM output protection mismatch on a TOSLINK output."; break;
	case  bb::multimedia::MediaError::DrmSpdifOutputRestricted: description = "A DRM output protection mismatch on an S/PDIF output."; break;
	case  bb::multimedia::MediaError::DrmBluetoothOutputRestricted: description = "A DRM output protection mismatch on a BLUETOOTH output."; break;
	case  bb::multimedia::MediaError::DrmWirelessHdOutputRestricted: description = "A DRM output protection mismatch on a WIRELESSHD output."; break;
	default: break;
	}
	Ti::TiEventParameters params;
	params.addParam("description", description);
	params.addParam("code", type);
	params.addParam("type", Ti::TiConstants::EventError);
	_proxy->fireEvent(Ti::TiConstants::EventError, params);
}

}
