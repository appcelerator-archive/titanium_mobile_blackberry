/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeUDPSocketObject.h"

#include "NativeBufferObject.h"
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

#define PROP_SETGET(NAME)               static int prop_##NAME(NativeUDPSocketObject* udpSocket, TiObject* obj, void * userContext) \
    {\
        return udpSocket->NAME(obj, userContext);\
    }

#define GET_ARRAY_SIZE(ARRAY)           (int)(sizeof(ARRAY)/sizeof(*(ARRAY)))

typedef int (*NATIVE_PROPSETGET_CALLBACK)(NativeUDPSocketObject*, TiObject*, void*);

struct NATIVE_PROPSETGET_SETTING
{
	NATIVE_UDPSOCKET_PROP propNumber;
    NATIVE_PROPSETGET_CALLBACK setter;
    NATIVE_PROPSETGET_CALLBACK getter;
};

class SetGetSocketProperties
{
public:
    SetGetSocketProperties(const NATIVE_PROPSETGET_SETTING* map, int mapEntries)
    {
        setters_ = new NATIVE_PROPSETGET_CALLBACK[N_UDPSOCKET_PROP_LAST];
        memset(setters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_UDPSOCKET_PROP_LAST);
        getters_ = new NATIVE_PROPSETGET_CALLBACK[N_UDPSOCKET_PROP_LAST];
        memset(getters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_UDPSOCKET_PROP_LAST);
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
        if (prop >= (std::size_t)N_UDPSOCKET_PROP_LAST)
        {
            return NULL;
        }
        return setters_[prop];
    }
    NATIVE_PROPSETGET_CALLBACK GetGetterCallback(size_t prop)
    {
        if (prop >= (std::size_t)N_UDPSOCKET_PROP_LAST)
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

PROP_SETGET(getPort)
int NativeUDPSocketObject::getPort(TiObject* obj, void* /*userContext*/)
{
    obj->setValue(Number::New(port_));
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setStartedCallback)
int NativeUDPSocketObject::setStartedCallback(TiObject* obj, void* userContext)
{
    Handle<Value> value = obj->getValue();
    if (value->IsFunction())
    {
        TiUDPSocketObject* context = (TiUDPSocketObject*)userContext;
        Handle<Object> source = Handle<Object>::Cast(context->getValue());
        TiV8Event* connectEvent = TiV8Event::createEvent(tetSTARTED, Handle<Function>::Cast(value), source);
        setEventHandler(tetSTARTED, connectEvent);
        events_[tetSTARTED]->container()->setV8ValueProperty("socket", context->getValue());
        connectEvent->release();
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_INVALID_ARG;
}

PROP_SETGET(getStartedCallback)
int NativeUDPSocketObject::getStartedCallback(TiObject* /*obj*/, void* /*userContext*/)
{
    // TODO: Implement this
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setErrorCallback)
int NativeUDPSocketObject::setErrorCallback(TiObject* obj, void* userContext)
{
    Handle<Value> value = obj->getValue();
    if (value->IsFunction())
    {
        TiUDPSocketObject* context = (TiUDPSocketObject*)userContext;
        Handle<Object> source = Handle<Object>::Cast(context->getValue());
        TiV8Event* errorEvent = TiV8Event::createEvent(tetERROR, Handle<Function>::Cast(value), source);
        setEventHandler(tetERROR, errorEvent);
        events_[tetERROR]->container()->setV8ValueProperty("socket", context->getValue());
        errorEvent->release();
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_INVALID_ARG;
}

PROP_SETGET(getErrorCallback)
int NativeUDPSocketObject::getErrorCallback(TiObject* /*obj*/, void* /*userContext*/)
{
    // TODO: Implement this
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setDataCallback)
int NativeUDPSocketObject::setDataCallback(TiObject* obj, void* userContext)
{
    Handle<Value> value = obj->getValue();
    if (value->IsFunction())
    {
        TiUDPSocketObject* context = (TiUDPSocketObject*)userContext;
        Handle<Object> source = Handle<Object>::Cast(context->getValue());
        TiV8Event* acceptEvent = TiV8Event::createEvent(tetDATA, Handle<Function>::Cast(value), source);
        setEventHandler(tetDATA, acceptEvent);
        events_[tetDATA]->container()->setV8ValueProperty("socket", context->getValue());
        acceptEvent->release();
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_INVALID_ARG;
}

PROP_SETGET(getDataCallback)
int NativeUDPSocketObject::getDataCallback(TiObject* /*obj*/, void* /*userContext*/)
{
    // TODO: Implement this
    return NATIVE_ERROR_NOTSUPPORTED;
}

NativeUDPSocketObject::NativeUDPSocketObject(TiObject* tiObject)
    : NativeProxyObject(tiObject)
{
    port_ = -1;
    eventHandler_ = NULL;
    udpSocket_ = NULL;
}

NativeUDPSocketObject::~NativeUDPSocketObject()
{
    delete udpSocket_;
    delete eventHandler_;
}

NATIVE_TYPE NativeUDPSocketObject::getObjectType() const
{
    return N_TYPE_UDPSOCKET;
}

NativeUDPSocketObject* NativeUDPSocketObject::createUDPSocket(TiObject* tiObject)
{
    return new NativeUDPSocketObject(tiObject);
}

const static NATIVE_PROPSETGET_SETTING g_SocketPropSetGet[] =
{
    {N_UDPSOCKET_PROP_ONSTARTED, PROP_SETGET_FUNCTION(setStartedCallback), PROP_SETGET_FUNCTION(getStartedCallback)},
    {N_UDPSOCKET_PROP_ONDATA, PROP_SETGET_FUNCTION(setDataCallback), PROP_SETGET_FUNCTION(getDataCallback)},
    {N_UDPSOCKET_PROP_ONERROR, PROP_SETGET_FUNCTION(setErrorCallback), PROP_SETGET_FUNCTION(getErrorCallback)},
    {N_UDPSOCKET_PROP_PORT, NULL, PROP_SETGET_FUNCTION(getPort)}
};

static SetGetSocketProperties g_SocketProps(g_SocketPropSetGet, GET_ARRAY_SIZE(g_SocketPropSetGet));

int NativeUDPSocketObject::setPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_SocketProps.GetSetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj, userContext);
}

int NativeUDPSocketObject::getPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_SocketProps.GetGetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj, userContext);
}

void NativeUDPSocketObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeProxyObject::setupEvents(containerFactory);
    eventHandler_ = new UDPSocketEventHandler(this);
    events_.insert(tetSTARTED, EventPairSmartPtr(containerFactory->createEventContainer(), eventHandler_));
    events_.insert(tetERROR, EventPairSmartPtr(containerFactory->createEventContainer(), eventHandler_));
    events_.insert(tetDATA, EventPairSmartPtr(containerFactory->createEventContainer(), eventHandler_));
}

void NativeUDPSocketObject::listen(int port)
{
    if (port <= 0) {
        throw NativeException(Native::Msg::Invalid_hostname_or_port);
    }
    if (udpSocket_ != NULL) {
        throw NativeException(Native::Msg::Invalid_socket_state);
    }
    port_ = port;
    udpSocket_ = new QUdpSocket();
    udpSocket_->bind(port_, QUdpSocket::ShareAddress);
    QObject::connect(udpSocket_, SIGNAL(readyRead()), eventHandler_, SLOT(udpReadyRead()));
    QObject::connect(udpSocket_, SIGNAL(error(QAbstractSocket::SocketError)), eventHandler_, SLOT(udpError(QAbstractSocket::SocketError)));
	fireEvent(NativeProxyObject::tetSTARTED, NULL);
}

void NativeUDPSocketObject::close()
{
    if (udpSocket_ == NULL) {
        throw NativeException(Native::Msg::Invalid_socket_state);
    }
    udpSocket_->abort();
    delete udpSocket_;
    udpSocket_ = NULL;
}

void NativeUDPSocketObject::send(const QByteArray& datagram, const QHostAddress& addr, int port)
{
    if (udpSocket_ == NULL) {
    	udpSocket_ = new QUdpSocket();
    }
    if (port == -1) {
    	port = port_;
    }
    udpSocket_->writeDatagram(datagram.data(), datagram.size(), addr, port);
}

void NativeUDPSocketObject::datagramReady()
{
	while (udpSocket_->hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(udpSocket_->pendingDatagramSize());
		QHostAddress addr;
		quint16 port = 0;
		if (udpSocket_->readDatagram(datagram.data(), datagram.size(), &addr, &port) == -1) {
			continue;
		}
        events_[NativeProxyObject::tetDATA]->container()->setDataProperty("stringData", datagram.data());
        events_[NativeProxyObject::tetDATA]->container()->setV8ValueProperty("bytesData", TiObject::getValueFromByteArray(datagram));
        events_[NativeProxyObject::tetDATA]->container()->setDataProperty("address", addr.toString().toAscii().data());
        events_[NativeProxyObject::tetDATA]->container()->setDataProperty("port", (int)port);
		fireEvent(NativeProxyObject::tetDATA, NULL);
	}
}
