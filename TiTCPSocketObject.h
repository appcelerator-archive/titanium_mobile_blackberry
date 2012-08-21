/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TITCPSOCKETOBJECT_H_
#define TITCPSOCKETOBJECT_H_

#include "TiProxy.h"

/*
 * TiTCPSocketObject
 *
 * TCP socket that implements the Titanium.IOStream interface.
 *
 * Titanium.Network.Socket.TCP namespace
 */

class TiTCPSocketObject : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent);
    static TiTCPSocketObject* createTCP(NativeObjectFactory* objectFactory);

protected:
    virtual ~TiTCPSocketObject();
    virtual void onCreateStaticMembers();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiTCPSocketObject();
    TiTCPSocketObject(const TiTCPSocketObject&);
    TiTCPSocketObject& operator=(const TiTCPSocketObject&);

    void setTiBufferMappingProperties(const TiProperty* props, int propertyCount);
    static VALUE_MODIFY _valueModify(int propertyNumber, TiObject* value, void* context);
    static Handle<Value> _getValue(int propertyNumber, void* context);

    static Handle<Value> _connect(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _close(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _accept(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _listen(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _write(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _read(void* userContext, TiObject* caller, const Arguments& args);
};


#endif /* TITCPSOCKETOBJECT_H_ */
