/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#ifndef TIAUDIOPLAYEROBJECT_H_
#define TIAUDIOPLAYEROBJECT_H_

#include "TiUIBase.h"

/*
 * TiAudioPlayerObject
 *
 * Represents a Titanium AudioPlayerObject object
 *
 */

class TiAudioPlayerObject: public TiUIBase
{
public:
    static TiAudioPlayerObject* createAudioPlayerObject(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiAudioPlayerObject();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();

private:
	TiAudioPlayerObject();

	static Handle<Value> _play(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _stop(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _start(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _pause(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _release(void* userContext, TiObject*, const Arguments& args);
};

#endif /* TIAUDIOPLAYEROBJECT_H_ */
