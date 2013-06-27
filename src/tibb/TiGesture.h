/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_GESTURE_H
#define TI_GESTURE_H

#include "TiProxy.h"

class TiGesture : public TiProxy {
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* factory);

    virtual void onCreateStaticMembers();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiGesture();
    static Handle<Value> _isLandscape(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _isPortrait(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _isFaceDown(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _isFaceUp(void* userContext, TiObject* caller, const Arguments& args);

};

#endif

