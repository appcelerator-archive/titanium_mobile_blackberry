/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIMEDIA_H_
#define TIMEDIA_H_

#include "TiProxy.h"

typedef TiProxy* (*CREATEOBJECTCALLBACK)(NativeObjectFactory*);

/*
 * TiMedia
 *
 * Titanium.Media namespace
 */
class TiMedia : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);

protected:
    virtual ~TiMedia();
    virtual void onCreateStaticMembers();

private:
    TiMedia();
    TiMedia(NativeObjectFactory* objectFactory);
    static Handle<Value> _createControlHelper(void* userContext, CREATEOBJECTCALLBACK createCallback, const Arguments& args);
    static Handle<Value> _createAudioPlayer(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createSound(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createAudioRecorder(void* userContext, TiObject* caller, const Arguments& args);

    NativeObjectFactory* objectFactory_;
    NativeObject* contentContainer_;
};

#endif /* TIMEDIA_H_ */
