/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_APIOBJECT_H_
#define TI_APIOBJECT_H_

#include "TiProxy.h"
#include <QtNetwork/QTcpSocket>

/*
 * TiAPIObject
 *
 * Object that represents name space: Titanium.API
 */

class TiAPIObject : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent);
    static void Log(QString);
protected:
    virtual ~TiAPIObject();
    virtual void onCreateStaticMembers();

private:
    QTcpSocket *_socket;
    TiAPIObject();
    TiAPIObject(const TiAPIObject&);
    TiAPIObject& operator=(const TiAPIObject&);
    static Handle<Value> _debug(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _info(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _warn(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _error(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _log(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _timestamp(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _trace(void* userContext, TiObject* caller, const Arguments& args);
};

#endif /* TIAPIOBJECT_H_ */
