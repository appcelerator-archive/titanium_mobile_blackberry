/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiSocketObject.h"

#include "TiConstants.h"
#include "TiGenericFunctionObject.h"
#include "TiTCPSocketObject.h"
#include "TiUDPSocketObject.h"

TiSocketObject::TiSocketObject()
    : TiProxy("Socket")
{
}

TiSocketObject::~TiSocketObject()
{
}

void TiSocketObject::addObjectToParent(TiObject* parent, NativeObjectFactory* nativeObjectFactory)
{
    TiSocketObject* obj = new TiSocketObject;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->setAttachedObject(parent);
    parent->addMember(obj);
    obj->release();
}

void TiSocketObject::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createTCP", this, _createTCP);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createUDP", this, _createUDP);

    // Socket state constant from Titanium.Network.Socket namespace
    ADD_STATIC_TI_VALUE("CLOSED", Number::New(Ti::Network::Socket::SOCKET_STATE_CLOSED), this);
    ADD_STATIC_TI_VALUE("CONNECTED", Number::New(Ti::Network::Socket::SOCKET_STATE_CONNECTED), this);
    ADD_STATIC_TI_VALUE("ERROR", Number::New(Ti::Network::Socket::SOCKET_STATE_ERROR), this);
    ADD_STATIC_TI_VALUE("INITIALIZED", Number::New(Ti::Network::Socket::SOCKET_STATE_INITIALIZED), this);
    ADD_STATIC_TI_VALUE("LISTENING", Number::New(Ti::Network::Socket::SOCKET_STATE_LISTENING), this);
}

Handle<Value> TiSocketObject::_createTCP(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    HandleScope handleScope;
    TiSocketObject* obj = (TiSocketObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result = global->NewInstance();
    TiTCPSocketObject* newSocket = TiTCPSocketObject::createTCP(obj->getNativeObjectFactory());
    newSocket->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        newSocket->setParametersFromObject(newSocket, settingsObj);
    }
    setTiObjectToJsObject(result, newSocket);
    return handleScope.Close(result);
}

Handle<Value> TiSocketObject::_createUDP(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    HandleScope handleScope;
    TiSocketObject* obj = (TiSocketObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result = global->NewInstance();
    TiUDPSocketObject* newSocket = TiUDPSocketObject::createUDP(obj->getNativeObjectFactory());
    newSocket->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        newSocket->setParametersFromObject(newSocket, settingsObj);
    }
    setTiObjectToJsObject(result, newSocket);
    return handleScope.Close(result);
}
