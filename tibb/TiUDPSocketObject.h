/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUDPSOCKETOBJECT_H_
#define TIUDPSOCKETOBJECT_H_

#include "TiProxy.h"

/*
 * TiUDPSocketObject
 *
 * UDP socket
 *
 * Titanium.Network.Socket.UDP namespace
 */

class TiUDPSocketObject : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent);
    static TiUDPSocketObject* createUDP(NativeObjectFactory* objectFactory);

protected:
    virtual ~TiUDPSocketObject();
    virtual void onCreateStaticMembers();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiUDPSocketObject();
    TiUDPSocketObject(const TiUDPSocketObject&);
    TiUDPSocketObject& operator=(const TiUDPSocketObject&);

    void setTiSocketMappingProperties(const TiProperty* props, int propertyCount);
    static VALUE_MODIFY _valueModify(int propertyNumber, TiObject* value, void* context);
    static Handle<Value> _getValue(int propertyNumber, void* context);

    static Handle<Value> _start(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _stop(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _sendString(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _sendBytes(void* userContext, TiObject* caller, const Arguments& args);
};


#endif /* TIUDPSOCKETOBJECT_H_ */
