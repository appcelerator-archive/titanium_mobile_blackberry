/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIPROXY_H_
#define TIPROXY_H_

#include "TiObject.h"

typedef void(*SET_PROPERTY_CALLBACK)(void*, Handle<Value>);
typedef Handle<Value>(*GET_PROPERTY_CALLBACK)(void*);

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
    virtual void setParametersFromObject(void* userContext, Local<Object> obj);

protected:
    TiProxy();
    explicit TiProxy(const char* name);
    virtual ~TiProxy();

    virtual void onAddEventListener(const char* eventName, Handle<Function> eventFunction);
    virtual void onRemoveEventListener(const char* eventName, Handle<Function> eventFunction);

    void createSettersAndGetters(const char*, SET_PROPERTY_CALLBACK, GET_PROPERTY_CALLBACK);

    static Handle<Value> createProxy(TiProxy* proxy, void* userContext, const Arguments& args);
    // for subclass
    static Handle<Value> createProxy(void*, TiObject*, const Arguments& args);

private:
    // Disable copy ctor & assignment operator
    TiProxy(const TiProxy& obj);
    TiProxy& operator=(const TiProxy& obj);

    static Handle<Value> _addEventListener(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _fireEvent(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _removeEventListener(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _getApiName(void*userContext);
};

#endif /* TIPROXY_H_ */
