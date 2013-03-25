/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#ifndef TIAUDIORECORDEROBJECT_H_
#define TIAUDIORECORDEROBJECT_H_

#include "TiUIBase.h"

/*
 * TiAudioRecorderObject
 *
 * Represents a Titanium AudioRecorderObject object
 *
 */

class TiAudioRecorderObject: public TiUIBase
{
public:
    static TiAudioRecorderObject* createAudioRecorderObject(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiAudioRecorderObject();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();

private:
	TiAudioRecorderObject();
	TiAudioRecorderObject(const char* name);

	static Handle<Value> _stop(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _start(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _resume(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _pause(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _release(void* userContext, TiObject*, const Arguments& args);
};

#endif /* TIAUDIORECORDEROBJECT_H_ */
