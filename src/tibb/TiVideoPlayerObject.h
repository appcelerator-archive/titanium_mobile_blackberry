/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#ifndef TIVIDEOPLAYEROBJECT_H_
#define TIVIDEOPLAYEROBJECT_H_

#include "TiUIBase.h"

/*
 * TiVideoPlayerObject
 *
 * Represents a Titanium VideoPlayerObject object
 *
 */

class TiVideoPlayerObject: public TiUIBase
{
public:
    static TiVideoPlayerObject* createVideoPlayerObject(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiVideoPlayerObject();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();

private:
	TiVideoPlayerObject();

	static Handle<Value> _play(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _stop(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _start(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _pause(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _release(void* userContext, TiObject*, const Arguments& args);
};

#endif /* TIVIDEOPLAYEROBJECT_H_ */
