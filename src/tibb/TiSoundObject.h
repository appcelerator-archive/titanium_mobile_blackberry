/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#ifndef TISOUNDOBJECT_H_
#define TISOUNDOBJECT_H_

#include "TiUIBase.h"

/*
 * TiSoundObject
 *
 * Represents a Titanium SoundObject object
 *
 */

class TiSoundObject: public TiUIBase
{
public:
    static TiSoundObject* createSoundObject(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiSoundObject();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();

private:
	TiSoundObject();
	TiSoundObject(const char* name);

	static Handle<Value> _play(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _stop(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _pause(void* userContext, TiObject*, const Arguments& args);
	static Handle<Value> _release(void* userContext, TiObject*, const Arguments& args);
};

#endif /* TISOUNDOBJECT_H_ */
