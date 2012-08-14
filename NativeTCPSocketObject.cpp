/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeTCPSocketObject.h"

#include "NativeControlObject.h"
#include "TiObject.h"

#define PROP_SETGET_FUNCTION(NAME)      prop_##NAME

#define PROP_SETGET(NAME)               static int prop_##NAME(NativeTCPSocketObject* tcpSocket, TiObject* obj) \
    {\
        return tcpSocket->NAME(obj);\
    }

#define GET_ARRAY_SIZE(ARRAY)           (int)(sizeof(ARRAY)/sizeof(*(ARRAY)))

typedef int (*NATIVE_PROPSETGET_CALLBACK)(NativeTCPSocketObject*, TiObject*);

struct NATIVE_PROPSETGET_SETTING
{
    NATIVE_SOCKET_PROP propNumber;
    NATIVE_PROPSETGET_CALLBACK setter;
    NATIVE_PROPSETGET_CALLBACK getter;
};

class SetGetSocketProperties
{
public:
    SetGetSocketProperties(const NATIVE_PROPSETGET_SETTING* map, int mapEntries)
    {
        setters_ = new NATIVE_PROPSETGET_CALLBACK[N_SOCKET_PROP_LAST];
        memset(setters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_SOCKET_PROP_LAST);
        getters_ = new NATIVE_PROPSETGET_CALLBACK[N_SOCKET_PROP_LAST];
        memset(getters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_SOCKET_PROP_LAST);
        for (int i = 0; i < mapEntries; i++)
        {
            setters_[map[i].propNumber] = map[i].setter;
            getters_[map[i].propNumber] = map[i].getter;
        }
    }
    ~SetGetSocketProperties()
    {
        if (setters_ != NULL)
        {
            delete[] setters_;
            setters_ = NULL;
        }
        if (getters_ != NULL)
        {
            delete[] getters_;
            getters_ = NULL;
        }
    }
    NATIVE_PROPSETGET_CALLBACK GetSetterCallback(size_t prop)
    {
        if (prop >= (std::size_t)N_SOCKET_PROP_LAST)
        {
            return NULL;
        }
        return setters_[prop];
    }
    NATIVE_PROPSETGET_CALLBACK GetGetterCallback(size_t prop)
    {
        if (prop >= (std::size_t)N_SOCKET_PROP_LAST)
        {
            return NULL;
        }
        return getters_[prop];
    }
private:
    SetGetSocketProperties(const SetGetSocketProperties&);
    SetGetSocketProperties& operator=(const SetGetSocketProperties&);
    NATIVE_PROPSETGET_CALLBACK* setters_;
    NATIVE_PROPSETGET_CALLBACK* getters_;
};

PROP_SETGET(setHost)
int NativeTCPSocketObject::setHost(TiObject* obj)
{
    int error = NativeControlObject::getString(obj, hostName_);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    return NATIVE_ERROR_OK;
}

PROP_SETGET(getHost)
int NativeTCPSocketObject::getHost(TiObject* obj)
{
    obj->setValue(String::New(hostName_.toStdString().c_str()));
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setPort)
int NativeTCPSocketObject::setPort(TiObject* obj)
{
    int error = NativeControlObject::getInteger(obj, &port_);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    return NATIVE_ERROR_OK;
}

PROP_SETGET(getPort)
int NativeTCPSocketObject::getPort(TiObject* obj)
{
    obj->setValue(Number::New(port_));
    return NATIVE_ERROR_OK;
}

NativeTCPSocketObject::~NativeTCPSocketObject()
{
}

int NativeTCPSocketObject::getObjectType() const
{
    return N_TYPE_TCPSOCKET;
}

NativeTCPSocketObject* NativeTCPSocketObject::createTCPSocket()
{
    return new NativeTCPSocketObject;
}

const static NATIVE_PROPSETGET_SETTING g_SocketPropSetGet[] =
{
    {N_SOCKET_PROP_HOST, PROP_SETGET_FUNCTION(setHost), PROP_SETGET_FUNCTION(getHost)},
    {N_SOCKET_PROP_PORT, PROP_SETGET_FUNCTION(setPort), PROP_SETGET_FUNCTION(getPort)}
};

static SetGetSocketProperties g_SocketProps(g_SocketPropSetGet, GET_ARRAY_SIZE(g_SocketPropSetGet));

int NativeTCPSocketObject::setPropertyValue(size_t propertyNumber, TiObject* obj)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_SocketProps.GetSetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj);
}

int NativeTCPSocketObject::getPropertyValue(size_t propertyNumber, TiObject* obj)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_SocketProps.GetGetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj);
}

void NativeTCPSocketObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeProxyObject::setupEvents(containerFactory);
}

void NativeTCPSocketObject::connect()
{
    tcpSocket_.connectToHost(hostName_, port_);
}

void NativeTCPSocketObject::close()
{
    tcpSocket_.close();
}
