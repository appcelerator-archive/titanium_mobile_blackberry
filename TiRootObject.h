/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIROOTOBJECT_H_
#define TIROOTOBJECT_H_

#include "TiObject.h"

using namespace std;

struct FUNCTION_ENTRY;
/*
 * TiRootObject
 *
 * Root namespace in Titanium
 */

typedef int (*MESSAGELOOPENTRY)(void*);

class TiRootObject : public TiObject
{
public:
    static TiRootObject* createRootObject();
    int executeScript(NativeObjectFactory* objectFactory, const char* javaScript,
                      MESSAGELOOPENTRY messageLoopEntry, void* context);

protected:
    virtual ~TiRootObject();
    virtual void onCreateStaticMembers();

private:
    TiRootObject();

    static Handle<Value> _L(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _alert(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _clearInterval(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _clearTimeout(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _decodeURIComponent(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _encodeURIComponent(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _require(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _setInterval(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _setTimeout(void* userContext, TiObject* caller, const Arguments& args);

    Persistent<Context> context_;
    Handle<ObjectTemplate> globalTemplate_;
    NativeObjectFactory* objectFactory_;
};

#endif /* TIROOTOBJECT_H_ */
