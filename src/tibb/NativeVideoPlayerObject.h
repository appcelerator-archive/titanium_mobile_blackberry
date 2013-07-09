/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEVIDEOPLAYEROBJECT_H_
#define NATIVEVIDEOPLAYEROBJECT_H_

#include "NativeControlObject.h"
#include <QtCore/QObject>
#include "TiLogger.h"
#include <bb/multimedia/BufferStatus>
#include <bb/multimedia/RepeatMode>
#include <screen/screen.h>

namespace bb
{
namespace multimedia
{
class MediaPlayer;
}
namespace cascades
{
class ForeignWindowControl;
}
}

class VideoPlayerObjectEventHandler;

class NativeVideoPlayerObject : public NativeControlObject
{
public:
    static NativeVideoPlayerObject* createVideoPlayerObject(TiObject* tiObject);
    virtual ~NativeVideoPlayerObject();
    virtual NATIVE_TYPE getObjectType() const;
    virtual int initialize();

    // properties
	virtual int getPaused(TiObject* obj);
	virtual int getPlaying(TiObject* obj);
	virtual int getProgress(TiObject* obj);
	virtual int setUrl(TiObject* obj);
	virtual int setRepeatMode(TiObject* obj);
	virtual int getVolume(TiObject* obj);
	virtual int setVolume(TiObject* obj);

	int start();
   	int play();
   	int stop();
   	int pause();
   	int mediaRelease();

   	void alwaysPrepare();

    QString videoSource;
    bb::multimedia::MediaPlayer* player_;

protected:
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:

    explicit NativeVideoPlayerObject(TiObject* tiObject);
    // Disable copy ctor & assignment operator
    NativeVideoPlayerObject(const NativeVideoPlayerObject&);
    void operator=(const NativeVideoPlayerObject&);

    bb::cascades::ForeignWindowControl* foreignWindow_;
    bool alwaysPrepare_;

    VideoPlayerObjectEventHandler* eventHandler_;
};

//Event handler for Video player object
class VideoPlayerObjectEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit VideoPlayerObjectEventHandler(TiEventContainer* eventContainer, NativeVideoPlayerObject* annotationObject);
    virtual ~VideoPlayerObjectEventHandler();

public slots:
    void changed(bb::multimedia::BufferStatus::Type);
    void completed();
    void repeatModeChanged(bb::multimedia::RepeatMode::Type);
    void windowAttached(screen_window_t, QString, QString);

private:
    TiEventContainer* eventContainer_;
    NativeVideoPlayerObject* playerObject_;
    // Disable copy ctor & assignment operator
    VideoPlayerObjectEventHandler(const VideoPlayerObjectEventHandler& eHandler);
    VideoPlayerObjectEventHandler& operator=(const VideoPlayerObjectEventHandler& eHandler);
};


#endif /* NATIVEVIDEOPLAYEROBJECT_H_ */
