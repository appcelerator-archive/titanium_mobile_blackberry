/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIHTTPCLIENTOBJECT_H_
#define TIHTTPCLIENTOBJECT_H_

#include "TiProxy.h"

class NativeObjectFactory;

/*
 * TiHTTPClientObject
 *
 * HTTP client object that (mostly) implements the XMLHttpRequest specification.
 *
 * Titanium.Network.HTTPClient namespace
 */
class TiHTTPClientObject : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);
    static TiHTTPClientObject* createHTTPClient(NativeObjectFactory* objectFactory);

protected:
    virtual ~TiHTTPClientObject();
    virtual void onCreateStaticMembers();
    virtual void initializeTiObject(TiObject* parentContext);

    void setTiHTTPClientMappingProperties(const TiProperty* props, int propertyCount);
    static VALUE_MODIFY _valueModify(int propertyNumber, TiObject* value, void* context);
    static Handle<Value> _getValue(int propertyNumber, void* context);

    static Handle<Value> _open(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _abort(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _send(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _clearCookies(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _setRequestHeader(void* userContext, TiObject* caller, const Arguments& args);

private:
    TiHTTPClientObject();
    explicit TiHTTPClientObject(NativeObjectFactory* objectFactory);
    TiHTTPClientObject(const TiHTTPClientObject&);
    TiHTTPClientObject& operator=(const TiHTTPClientObject&);

    NativeObjectFactory* objectFactory_;
};


#endif /* TIHTTPCLIENTOBJECT_H_ */
