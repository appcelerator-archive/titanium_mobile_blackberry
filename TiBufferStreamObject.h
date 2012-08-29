/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIBUFFERSTREAMOBJECT_H_
#define TIBUFFERSTREAMOBJECT_H_

#include "TiIOStreamObject.h"

class TiBufferObject;

/*
 * TiBufferStreamObject
 *
 * Object that represents name space: Titanium.BufferStream
 */

class TiBufferStreamObject : public TiIOStreamObject
{
public:
    static void addObjectToParent(TiObject* parent);
    static TiBufferStreamObject* createBufferStream(Handle<Object> params);

protected:
    virtual ~TiBufferStreamObject();
    virtual void onCreateStaticMembers();

private:
    TiBufferStreamObject();
    TiBufferStreamObject(const TiBufferStreamObject&);
    TiBufferStreamObject& operator=(const TiBufferStreamObject&);
};

#endif /* TIBUFFERSTREAMOBJECT_H_ */
