/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIPROXY_H_
#define TIPROXY_H_

#include "TiObject.h"

/*
 * Class TiProxy
 *
 * This class is used to bind the methods of Ti.Proxy to objects that extend it
 *
 * TiProxy inherits directly from TiObject and is inherited by all Ti classes
 * that extend its functionality.
 */

class TiProxy : public TiObject
{
public:
    virtual void onCreateStaticMembers();

protected:
    TiProxy();
    explicit TiProxy(const char* name);
    virtual ~TiProxy();

    virtual void onAddEventListener(const char* eventName, Handle<Function> eventFunction) const;
    virtual void onRemoveEventListener(const char* eventName, Handle<Function> eventFunction) const;

private:
    // Disable copy ctor & assignment operator
    TiProxy(const TiProxy& obj);
    TiProxy& operator=(const TiProxy& obj);

    static Handle<Value> _addEventListener(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _fireEvent(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _removeEventListener(void* userContext, TiObject* caller, const Arguments& args);
};

#endif /* TIPROXY_H_ */
