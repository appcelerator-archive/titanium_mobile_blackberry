/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TICODECOBJECT_H_
#define TICODECOBJECT_H_

#include "TiProxy.h"

/*
 * TiCodecObject
 *
 * Titanium.Codec namespace
 * A module for translating between primitive types and raw byte streams.
 * The Codec module can be used for encoding strings and numbers into Buffer objects,
 * and decoding primitive types from buffers.
 */
class TiCodecObject : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent);

protected:
    virtual ~TiCodecObject();
    virtual void onCreateStaticMembers();

private:
    TiCodecObject();
    TiCodecObject(const TiCodecObject&);
    TiCodecObject& operator=(const TiCodecObject&);

    static Handle<Value> _decodeNumber(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _decodeString(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _encodeNumber(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _encodeString(void* userContext, TiObject* caller, const Arguments& args);
};

#endif /* TICODECOBJECT_H_ */
