/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TISOCKETOBJECT_H_
#define TISOCKETOBJECT_H_

#include "TiProxy.h"

class NativeObjectFactory;

/*
 * TiSocketObject
 *
 * Socket module, used for creating sockets.
 *
 * Titanium.Network.Socket namespace
 */
class TiSocketObject : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);

protected:
    virtual ~TiSocketObject();
    virtual void onCreateStaticMembers();

private:
    TiSocketObject();
    explicit TiSocketObject(NativeObjectFactory* objectFactory);
    TiSocketObject(const TiSocketObject&);
    TiSocketObject& operator=(const TiSocketObject&);

    static Handle<Value> _createTCP(void* userContext, TiObject* caller, const Arguments& args);

    NativeObjectFactory* objectFactory_;
};


#endif /* TISOCKETOBJECT_H_ */
