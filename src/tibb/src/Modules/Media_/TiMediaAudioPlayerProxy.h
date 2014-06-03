/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVE_TiMediaAudioPlayerProxy_TESTPROXY_H_
#define NATIVE_TiMediaAudioPlayerProxy_TESTPROXY_H_

#include <TiCore.h>
#include <bb/multimedia/MediaPlayer>
#include <bb/multimedia/RepeatMode>
#include <bb/multimedia/BufferStatus>
#include <bb/multimedia/MediaError>

namespace TiMedia {

class TiMediaAudioPlayerProxy : public Ti::TiProxy
{
public:
	CREATE_PROXY(TiMediaAudioPlayerProxy)
	TiMediaAudioPlayerProxy(const char*);
	virtual ~TiMediaAudioPlayerProxy();

	Ti::TiValue isPaused(Ti::TiValue);
	Ti::TiValue isPlaying(Ti::TiValue);
	Ti::TiValue pause(Ti::TiValue);
	Ti::TiValue play(Ti::TiValue);
	Ti::TiValue release(Ti::TiValue);
	Ti::TiValue start(Ti::TiValue);
	Ti::TiValue stateDescription(Ti::TiValue);
	Ti::TiValue stop(Ti::TiValue);

	EXPOSE_METHOD(TiMediaAudioPlayerProxy, isPaused)
	EXPOSE_METHOD(TiMediaAudioPlayerProxy, isPlaying)
	EXPOSE_METHOD(TiMediaAudioPlayerProxy, pause)
	EXPOSE_METHOD(TiMediaAudioPlayerProxy, play)
	EXPOSE_METHOD(TiMediaAudioPlayerProxy, release)
	EXPOSE_METHOD(TiMediaAudioPlayerProxy, start)
	EXPOSE_METHOD(TiMediaAudioPlayerProxy, stateDescription)
	EXPOSE_METHOD(TiMediaAudioPlayerProxy, stop)

	TI_CREATE_SETTER_GETTER(TiMediaAudioPlayerProxy, setAllowBackground, getAllowBackground);
	TI_CREATE_SETTER_GETTER(TiMediaAudioPlayerProxy, setAutoplay, getAutoplay);
	TI_CREATE_SETTER_GETTER(TiMediaAudioPlayerProxy, setBitRate, getBitRate);
	TI_CREATE_SETTER_GETTER(TiMediaAudioPlayerProxy, setBufferSize, getBufferSize);
	TI_CREATE_SETTER_GETTER(TiMediaAudioPlayerProxy, setIdle, getIdle);
	TI_CREATE_SETTER_GETTER(TiMediaAudioPlayerProxy, setPaused, getPaused);
	TI_CREATE_SETTER_GETTER(TiMediaAudioPlayerProxy, setPlaying, getPlaying);
	TI_CREATE_SETTER_GETTER(TiMediaAudioPlayerProxy, setProgress, getProgress);
	TI_CREATE_SETTER_GETTER(TiMediaAudioPlayerProxy, setRepeatMode, getRepeatMode);
	TI_CREATE_SETTER_GETTER(TiMediaAudioPlayerProxy, setState, getState);
	TI_CREATE_SETTER_GETTER(TiMediaAudioPlayerProxy, setUrl, getUrl);
	TI_CREATE_SETTER_GETTER(TiMediaAudioPlayerProxy, setVolume, getVolume);
	TI_CREATE_SETTER_GETTER(TiMediaAudioPlayerProxy, setWaiting, getWaiting);
	bb::multimedia::MediaPlayer* getNativeMediaPlayer();
private:
	bb::multimedia::MediaPlayer *_mediaPlayer;
	bool _autoPlay;
};

class TiMediaAudioPlayerEventHandler : public QObject
{
	Q_OBJECT;
public:
	TiMediaAudioPlayerEventHandler(TiMediaAudioPlayerProxy*);
	virtual ~TiMediaAudioPlayerEventHandler();
public slots:
	void onChanged(bb::multimedia::BufferStatus::Type);
	void onCompleted();
	void onRepeatModeChanged(bb::multimedia::RepeatMode::Type);
	void onError(bb::multimedia::MediaError::Type, unsigned int);
private:
	TiMediaAudioPlayerProxy *_proxy;
};
}
#endif /* NATIVE_<%- moduleName %>_TESTPROXY_H_ */
