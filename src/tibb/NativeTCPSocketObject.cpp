/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeTCPSocketObject.h"

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
    int maxCount;
    int error = NativeControlObject::getInteger(obj, &maxCount);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    tcpServer_->setMaxPendingConnections(maxCount);
    return NATIVE_ERROR_OK;
}

PROP_SETGET(getListenQueueSize)
int NativeTCPSocketObject::getListenQueueSize(TiObject* obj, void* /*userContext*/)
{
    obj->setValue(Number::New(tcpServer_->maxPendingConnections()));
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setConnectedCallback)
int NativeTCPSocketObject::setConnectedCallback(TiObject* obj, void* userContext)
{
    if (socketState_ != SOCKET_STATE_INITIALIZED)
    {
        throw NativeException(Native::Msg::Invalid_socket_state);
    }
    Handle<Value> value = obj->getValue();
    if (value->IsFunction())
    {
        TiTCPSocketObject* context = (TiTCPSocketObject*)userContext;
        Handle<Object> source = Handle<Object>::Cast(context->getValue());
        TiV8Event* connectEvent = TiV8Event::createEvent(tetCONNECTED, Handle<Function>::Cast(value), source);
        setEventHandler(tetCONNECTED, connectEvent);
        events_[tetCONNECTED]->container()->setV8ValueProperty("socket", context->getValue());
        connectEvent->release();
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
        Handle<Object> source = Handle<Object>::Cast(context->getValue());
        TiV8Event* acceptEvent = TiV8Event::createEvent(tetACCEPTED, Handle<Function>::Cast(value), source);
        setEventHandler(tetACCEPTED, acceptEvent);
        events_[tetACCEPTED]->container()->setV8ValueProperty("socket", context->getValue());
        acceptEvent->release();
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

NativeTCPSocketObject::NativeTCPSocketObject(TiObject* tiObject)
    : NativeProxyObject(tiObject)
{
    socketState_ = SOCKET_STATE_INITIALIZED;
    port_ = -1;
    eventHandler_ = NULL;
    tcpClient_ = NULL;
    tcpServer_ = NULL;
}

NativeTCPSocketObject::~NativeTCPSocketObject()
{
    delete tcpClient_;
    delete tcpServer_;
    delete eventHandler_;
}

int NativeTCPSocketObject::getObjectType() const
{
    return N_TYPE_TCPSOCKET;
}

NativeTCPSocketObject* NativeTCPSocketObject::createTCPSocket(TiObject* tiObject)
{
    return new NativeTCPSocketObject(tiObject);
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
    if (tcpClient_ == NULL)
    {
        tcpClient_ = new QTcpSocket();
    }
    eventHandler_ = new TCPSocketEventHandler(this);
    events_.insert(tetCONNECTED, EventPairSmartPtr(containerFactory->createEventContainer(), eventHandler_));
    events_.insert(tetERROR, EventPairSmartPtr(containerFactory->createEventContainer(), eventHandler_));
    events_.insert(tetACCEPTED, EventPairSmartPtr(containerFactory->createEventContainer(), eventHandler_));
    QObject::connect(tcpClient_, SIGNAL(connected()), eventHandler_, SLOT(connected()));
    QObject::connect(tcpClient_, SIGNAL(error(QAbstractSocket::SocketError)), eventHandler_, SLOT(error(QAbstractSocket::SocketError)));
}

void NativeTCPSocketObject::connect()
{
    if (hostName_.isEmpty() || port_ == -1)
    {
        throw NativeException(Native::Msg::Invalid_hostname_or_port);
    }
    if (socketState_ == SOCKET_STATE_CONNECTED || socketState_ == SOCKET_STATE_LISTENING)
    {
        throw NativeException(Native::Msg::Invalid_socket_state);
    }
    Q_ASSERT(tcpClient_ != NULL);
    tcpClient_->connectToHost(hostName_, port_);
}

void NativeTCPSocketObject::close()
{
    if (socketState_ != SOCKET_STATE_CONNECTED && socketState_ != SOCKET_STATE_LISTENING)
    {
        throw NativeException(Native::Msg::Invalid_socket_state);
    }
    if (socketState_ == SOCKET_STATE_CONNECTED)
    {
        tcpClient_->disconnectFromHost();
        tcpClient_->close();
    }
    else if (socketState_ == SOCKET_STATE_LISTENING)
    {
        tcpServer_->close();
    }
    socketState_ = SOCKET_STATE_CLOSED;
}

void NativeTCPSocketObject::listen()
{
    if (socketState_ == SOCKET_STATE_CONNECTED || socketState_ == SOCKET_STATE_LISTENING)
    {
        throw NativeException(Native::Msg::Invalid_socket_state);
    }
    if (tcpServer_ == NULL)
    {
        tcpServer_ = new QTcpServer();
    }
    QHostAddress address = hostName_.isEmpty() ? QHostAddress::Any : QHostAddress(hostName_);
    int port = port_ == -1 ? 0 : port_;
    bool bSuccess = tcpServer_->listen(address, port);
    socketState_ = bSuccess ? SOCKET_STATE_LISTENING : SOCKET_STATE_ERROR;
}

void NativeTCPSocketObject::accept(TiEvent* /*errorCallback*/, int /*timeout*/)
{
    // TODO: Use errorCallback and timeout
    if (socketState_ != SOCKET_STATE_LISTENING)
    {
        throw NativeException(Native::Msg::Invalid_socket_state);
    }
    if (tcpServer_->hasPendingConnections())
    {
        eventHandler_->accepted();
    }
    else
    {
        // Accept next incoming connection immediately
        QObject::connect(tcpServer_, SIGNAL(newConnection()), eventHandler_, SLOT(accepted()), Qt::UniqueConnection);
    }
}

int NativeTCPSocketObject::write(NativeBufferObject* buffer, int offset, int length)
{
    if (socketState_ != SOCKET_STATE_CONNECTED)
    {
        throw NativeException(Native::Msg::Invalid_socket_state);
    }
    char* data = (char*)buffer->toString();
    int bufferLength = buffer->bufferSize();
    if (offset != -1 && length != -1)
    {
        /*
         * Validate the source buffer's offset and length.
         * - Checked offset and length to be valid
         * - Checked offset not to be above the buffer size
         */
        if (length < 0 || offset < 0 || (offset >= bufferLength))
        {
            throw NativeException(Native::Msg::Out_of_bounds);
        }
        bufferLength = min(length, bufferLength - offset);
    }

    int bytesWritten = tcpClient_->write(data + (offset == -1 ? 0 : offset), bufferLength);
    if (bytesWritten == -1 || !tcpClient_->waitForBytesWritten())
    {
        eventHandler_->error(tcpClient_->error());
        throw NativeException(QString(Native::Msg::Write_operation_failure).arg(tcpClient_->errorString()).toStdString());
    }

    return bytesWritten;
}

int NativeTCPSocketObject::read(NativeBufferObject* buffer, int offset, int length)
{
    if (socketState_ != SOCKET_STATE_CONNECTED)
    {
        throw NativeException(Native::Msg::Invalid_socket_state);
    }
    int bufferLength = buffer->bufferSize();
    int bytesRead = -1;
    if (tcpClient_->bytesAvailable() > 0 || tcpClient_->waitForReadyRead())
    {
        int bytes = tcpClient_->bytesAvailable();
        if (bytes != 0)
        {
            QByteArray readData;
            if (offset != -1 && length != -1)
            {
                if (length < 0 || offset < 0 || (offset >= bufferLength))
                {
                    throw NativeException(Native::Msg::Out_of_bounds);
                }
                readData = tcpClient_->read(min(length, bufferLength - offset));
            }
            else
            {
                readData = tcpClient_->read(bufferLength);
            }

            if (readData.isEmpty())
            {
                eventHandler_->error(tcpClient_->error());
            }
            else
            {
                buffer->replaceInternalData(readData, offset == -1 ? 0 : offset, readData.size());
            }

            bytesRead = readData.size();
        }
    }
    else
    {
        //TODO: we should fix this after separating reading thread from the main thread
        //eventHandler_->error(tcpClient_->error());
    }

    return bytesRead;
}
