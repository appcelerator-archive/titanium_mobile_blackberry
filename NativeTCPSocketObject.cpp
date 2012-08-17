/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeTCPSocketObject.h"

#include "NativeControlObject.h"
#include "NativeException.h"
#include "NativeMessageStrings.h"
#include "TiObject.h"
#include "TiV8Event.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <v8.h>
#pragma GCC diagnostic warning "-Wunused-parameter"

using namespace v8;

#define PROP_SETGET_FUNCTION(NAME)      prop_##NAME

#define PROP_SETGET(NAME)               static int prop_##NAME(NativeTCPSocketObject* tcpSocket, TiObject* obj, void * userContext) \
    {\
        return tcpSocket->NAME(obj, userContext);\
    }

#define GET_ARRAY_SIZE(ARRAY)           (int)(sizeof(ARRAY)/sizeof(*(ARRAY)))

typedef int (*NATIVE_PROPSETGET_CALLBACK)(NativeTCPSocketObject*, TiObject*, void*);

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
int NativeTCPSocketObject::setHost(TiObject* obj, void* /*userContext*/)
{
    if (socketState_ == SOCKET_STATE_INITIALIZED)
    {
        int error = NativeControlObject::getString(obj, hostName_);
        if (!N_SUCCEEDED(error))
        {
            return error;
        }
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_INVALID_ARG;
}

PROP_SETGET(getHost)
int NativeTCPSocketObject::getHost(TiObject* obj, void* /*userContext*/)
{
    obj->setValue(String::New(hostName_.toStdString().c_str()));
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setPort)
int NativeTCPSocketObject::setPort(TiObject* obj, void* /*userContext*/)
{
    if (socketState_ == SOCKET_STATE_INITIALIZED)
    {
        int error = NativeControlObject::getInteger(obj, &port_);
        if (!N_SUCCEEDED(error))
        {
            return error;
        }
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_INVALID_ARG;
}

PROP_SETGET(getPort)
int NativeTCPSocketObject::getPort(TiObject* obj, void* /*userContext*/)
{
    obj->setValue(Number::New(port_));
    return NATIVE_ERROR_OK;
}

PROP_SETGET(getState)
int NativeTCPSocketObject::getState(TiObject* obj, void* /*userContext*/)
{
    obj->setValue(Number::New(socketState_));
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setListenQueueSize)
int NativeTCPSocketObject::setListenQueueSize(TiObject* obj, void* /*userContext*/)
{
    if (socketState_ == SOCKET_STATE_LISTENING)
    {
        int maxCount;
        int error = NativeControlObject::getInteger(obj, &maxCount);
        if (!N_SUCCEEDED(error))
        {
            return error;
        }
        tcpServer_->setMaxPendingConnections(maxCount);
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_INVALID_ARG;
}

PROP_SETGET(getListenQueueSize)
int NativeTCPSocketObject::getListenQueueSize(TiObject* obj, void* /*userContext*/)
{
    if (socketState_ == SOCKET_STATE_LISTENING)
    {
        obj->setValue(Number::New(tcpServer_->maxPendingConnections()));
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_INVALID_ARG;
}

PROP_SETGET(setConnectedCallback)
int NativeTCPSocketObject::setConnectedCallback(TiObject* obj, void* userContext)
{
    Handle<Value> value = obj->getValue();
    if (value->IsFunction())
    {
        TiTCPSocketObject* context = (TiTCPSocketObject*)userContext;
        TiEventContainerFactory* eventFactory = context->getNativeObjectFactory()->getEventContainerFactory();
        if (!eventContainer_)
        {
            eventContainer_ = eventFactory->createEventContainer();
        }
        Handle<Object> source = Handle<Object>::Cast(context->getValue());
        TiV8Event* connectEvent = TiV8Event::createEvent("connected", Handle<Function>::Cast(value), source);
        eventContainer_->addListener(connectEvent);
        TCPSocketEventHandler* eHandler = new TCPSocketEventHandler(eventContainer_, this);
        eventContainer_->setV8ValueProperty("socket", context->getValue());
        QObject::connect(tcpClient_, SIGNAL(connected()), eHandler, SLOT(connected()));
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_INVALID_ARG;
}

PROP_SETGET(getConnectedCallback)
int NativeTCPSocketObject::getConnectedCallback(TiObject* /*obj*/, void* /*userContext*/)
{
    // TODO: Implement this
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setErrorCallback)
int NativeTCPSocketObject::setErrorCallback(TiObject* obj, void* userContext)
{
    Handle<Value> value = obj->getValue();
    if (value->IsFunction())
    {
        TiTCPSocketObject* context = (TiTCPSocketObject*)userContext;
        TiEventContainerFactory* eventFactory = context->getNativeObjectFactory()->getEventContainerFactory();
        if (!eventContainer_)
        {
            eventContainer_ = eventFactory->createEventContainer();
        }
        Handle<Object> source = Handle<Object>::Cast(context->getValue());
        TiV8Event* connectEvent = TiV8Event::createEvent("error", Handle<Function>::Cast(value), source);
        eventContainer_->addListener(connectEvent);
        TCPSocketEventHandler* eHandler = new TCPSocketEventHandler(eventContainer_, this);
        eventContainer_->setV8ValueProperty("socket", context->getValue());
        QObject::connect(tcpClient_, SIGNAL(error()), eHandler, SLOT(error()));
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_INVALID_ARG;
}

PROP_SETGET(getErrorCallback)
int NativeTCPSocketObject::getErrorCallback(TiObject* /*obj*/, void* /*userContext*/)
{
    // TODO: Implement this
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setAcceptedCallback)
int NativeTCPSocketObject::setAcceptedCallback(TiObject* obj, void* userContext)
{
    Handle<Value> value = obj->getValue();
    if (value->IsFunction())
    {
        TiTCPSocketObject* context = (TiTCPSocketObject*)userContext;
        TiEventContainerFactory* eventFactory = context->getNativeObjectFactory()->getEventContainerFactory();
        if (!eventContainer_)
        {
            eventContainer_ = eventFactory->createEventContainer();
        }
        Handle<Object> source = Handle<Object>::Cast(context->getValue());
        TiV8Event* connectEvent = TiV8Event::createEvent("accepted", Handle<Function>::Cast(value), source);
        eventContainer_->addListener(connectEvent);
        eventContainer_->setV8ValueProperty("socket", context->getValue());
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_INVALID_ARG;
}

PROP_SETGET(getAcceptedCallback)
int NativeTCPSocketObject::getAcceptedCallback(TiObject* /*obj*/, void* /*userContext*/)
{
    // TODO: Implement this
    return NATIVE_ERROR_NOTSUPPORTED;
}

NativeTCPSocketObject::NativeTCPSocketObject()
{
    socketState_ = SOCKET_STATE_INITIALIZED;
    port_ = -1;
    eventContainer_ = NULL;
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
    {N_SOCKET_PROP_ACCEPTED, PROP_SETGET_FUNCTION(setAcceptedCallback), PROP_SETGET_FUNCTION(getAcceptedCallback)},
    {N_SOCKET_PROP_CONNECTED, PROP_SETGET_FUNCTION(setConnectedCallback), PROP_SETGET_FUNCTION(getConnectedCallback)},
    {N_SOCKET_PROP_ERROR, PROP_SETGET_FUNCTION(setErrorCallback), PROP_SETGET_FUNCTION(getErrorCallback)},
    {N_SOCKET_PROP_HOST, PROP_SETGET_FUNCTION(setHost), PROP_SETGET_FUNCTION(getHost)},
    {N_SOCKET_PROP_LISTENQUEUESIZE, PROP_SETGET_FUNCTION(setListenQueueSize), PROP_SETGET_FUNCTION(getListenQueueSize)},
    {N_SOCKET_PROP_PORT, PROP_SETGET_FUNCTION(setPort), PROP_SETGET_FUNCTION(getPort)},
    {N_SOCKET_PROP_STATE, NULL, PROP_SETGET_FUNCTION(getState)}
};

static SetGetSocketProperties g_SocketProps(g_SocketPropSetGet, GET_ARRAY_SIZE(g_SocketPropSetGet));

int NativeTCPSocketObject::setPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_SocketProps.GetSetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj, userContext);
}

int NativeTCPSocketObject::getPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_SocketProps.GetGetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj, userContext);
}

void NativeTCPSocketObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeProxyObject::setupEvents(containerFactory);
    if (!eventContainer_)
    {
        eventContainer_ = containerFactory->createEventContainer();
    }
}

void NativeTCPSocketObject::connect()
{
    if (hostName_.isEmpty() || port_ == -1)
    {
        throw NativeException(QString(Native::Msg::Invalid_hostname_or_port).toStdString());
    }
    if (socketState_ == SOCKET_STATE_CONNECTED || socketState_ == SOCKET_STATE_LISTENING)
    {
        throw NativeException(QString(Native::Msg::Invalid_socket_state).toStdString());
    }
    tcpClient_->connectToHost(hostName_, port_);
}

void NativeTCPSocketObject::close()
{
    if (socketState_ != SOCKET_STATE_CONNECTED || socketState_ != SOCKET_STATE_LISTENING)
    {
        throw NativeException(QString(Native::Msg::Invalid_socket_state).toStdString());
    }
    tcpClient_->close();
    socketState_ = SOCKET_STATE_CLOSED;
}

void NativeTCPSocketObject::listen()
{
    if (hostName_.isEmpty() || port_ == -1)
    {
        throw NativeException(QString(Native::Msg::Invalid_hostname_or_port).toStdString());
    }
    if (socketState_ == SOCKET_STATE_CONNECTED || socketState_ == SOCKET_STATE_LISTENING)
    {
        throw NativeException(QString(Native::Msg::Invalid_socket_state).toStdString());
    }
    tcpServer_ = new QTcpServer();
    bool bSuccess = tcpServer_->listen(QHostAddress(hostName_), port_);
    socketState_ = bSuccess ? SOCKET_STATE_LISTENING : SOCKET_STATE_ERROR;
}

void NativeTCPSocketObject::accept(TiEvent* /*errorCallback*/, int /*timeout*/)
{
    // TODO: Use errorCallback and timeout
    if (socketState_ != SOCKET_STATE_LISTENING)
    {
        throw NativeException(QString(Native::Msg::Invalid_socket_state).toStdString());
    }
    TCPSocketEventHandler* eHandler = new TCPSocketEventHandler(eventContainer_, this);
    if (tcpServer_->hasPendingConnections())
    {
        eHandler->accepted();
    }
    else
    {
        // Accept next incoming connection immediately
        QObject::connect(tcpServer_, SIGNAL(newConnection()), eHandler, SLOT(accepted()));
    }
}
