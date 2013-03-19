/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEAUDIOPLAYEROBJECT_H_
#define NATIVEAUDIOPLAYEROBJECT_H_

#include "NativeControlObject.h"
#include <QtCore/QObject>
#include "TiLogger.h"
#include <bb/multimedia/BufferStatus>

namespace bb
{
namespace multimedia
{
class MediaPlayer;
}
}

class AudioPlayerObjectEventHandler;

class NativeAudioPlayerObject : public NativeControlObject
{
public:
    static NativeAudioPlayerObject* createAudioPlayerObject(TiObject* tiObject);
    virtual ~NativeAudioPlayerObject();
    virtual NATIVE_TYPE getObjectType() const;
    virtual int initialize();

    // properties
	virtual int getPaused(TiObject* obj);
	virtual int getPlaying(TiObject* obj);
	virtual int getProgress(TiObject* obj);
	virtual int setUrl(TiObject* obj);
	virtual int getVolume(TiObject* obj);
	virtual int setVolume(TiObject* obj);

	int start();
   	int play();
   	int stop();
   	int pause();
   	int mediaRelease();

protected:
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:

    explicit NativeAudioPlayerObject(TiObject* tiObject);
    // Disable copy ctor & assignment operator
    NativeAudioPlayerObject(const NativeAudioPlayerObject&);
    void operator=(const NativeAudioPlayerObject&);

    QString audioSource_;
    bb::multimedia::MediaPlayer* player_;

    AudioPlayerObjectEventHandler* eventHandler_;
};

//Event handler for audio player object
class AudioPlayerObjectEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit AudioPlayerObjectEventHandler(TiEventContainer* eventContainer, NativeAudioPlayerObject* annotationObject);
    virtual ~AudioPlayerObjectEventHandler();

public slots:
    void changed(bb::multimedia::BufferStatus::Type bufferStatus);
    void completed();

private:
    TiEventContainer* eventContainer_;
    NativeAudioPlayerObject* playerObject_;
    // Disable copy ctor & assignment operator
    AudioPlayerObjectEventHandler(const AudioPlayerObjectEventHandler& eHandler);
    AudioPlayerObjectEventHandler& operator=(const AudioPlayerObjectEventHandler& eHandler);
};


#endif /* NATIVEAUDIOPLAYEROBJECT_H_ */
