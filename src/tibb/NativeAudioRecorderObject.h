/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEAUDIORECORDEROBJECT_H_
#define NATIVEAUDIORECORDEROBJECT_H_

#include "NativeControlObject.h"
#include <QtCore/QObject>
#include "TiLogger.h"
#include <bb/multimedia/BufferStatus>

namespace bb
{
namespace multimedia
{
class AudioRecorder;
}
}

class AudioRecorderObjectEventHandler;

class NativeAudioRecorderObject : public NativeControlObject
{
public:
    static NativeAudioRecorderObject* createAudioRecorderObject(TiObject* tiObject);
    virtual ~NativeAudioRecorderObject();
    virtual NATIVE_TYPE getObjectType() const;
    virtual int initialize();

    // properties
	virtual int getPaused(TiObject* obj);
	virtual int getRecording(TiObject* obj);
	virtual int getStopped(TiObject* obj);
	virtual int setUrl(TiObject* obj);
	virtual int getVolume(TiObject* obj);
	virtual int setVolume(TiObject* obj);

	int start();
   	int resume();
   	int stop();
   	int pause();
   	int mediaRelease();

    QString audioTarget;

protected:
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:

    explicit NativeAudioRecorderObject(TiObject* tiObject);
    // Disable copy ctor & assignment operator
    NativeAudioRecorderObject(const NativeAudioRecorderObject&);
    void operator=(const NativeAudioRecorderObject&);

    bb::multimedia::AudioRecorder* recorder_;

    AudioRecorderObjectEventHandler* eventHandler_;
};

#endif /* NATIVEAUDIORECORDEROBJECT_H_ */
