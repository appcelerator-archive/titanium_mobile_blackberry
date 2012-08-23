/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVETCPSOCKETOBJECT_H_
#define NATIVETCPSOCKETOBJECT_H_

#include "NativeProxyObject.h"
#include <QtCore/QObject>
#include <QtNetwork/qtcpserver>
#include <QtNetwork/qtcpsocket>
#include "TiConstants.h"
#include "TiV8Event.h"
#include "TiTCPSocketObject.h"

class NativeBufferObject;
class TiObject;
class TiEventContainerFactory;
class TCPSocketEventHandler;

using namespace Ti::Network::Socket;

enum NATIVE_SOCKET_PROP
{
    N_SOCKET_PROP_UNDEFINED
    , N_SOCKET_PROP_ACCEPTED
    , N_SOCKET_PROP_CONNECTED
    , N_SOCKET_PROP_ERROR
    , N_SOCKET_PROP_HOST
    , N_SOCKET_PROP_LISTENQUEUESIZE
    , N_SOCKET_PROP_PORT
    , N_SOCKET_PROP_STATE
    , N_SOCKET_PROP_TIMEOUT

    /* This MUST be the last element */
    , N_SOCKET_PROP_LAST
};

/*
 * NativeTCPSocketObject
 *
 * NativeTCPSocketObject methods
 */
class NativeTCPSocketObject : public NativeProxyObject
{
public:
    friend class TCPSocketEventHandler;
    static NativeTCPSocketObject* createTCPSocket();
    int getObjectType() const;
    int setPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext);
    int getPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext);

    // Properties
    int setHost(TiObject* obj, void* userContext);
    int getHost(TiObject* obj, void* userContext);
    int setPort(TiObject* obj, void* userContext);
    int getPort(TiObject* obj, void* userContext);
    int getState(TiObject* obj, void* userContext);
    int setAcceptedCallback(TiObject* obj, void* userContext);
    int getAcceptedCallback(TiObject* obj, void* userContext);
    int setConnectedCallback(TiObject* obj, void* userContext);
    int getConnectedCallback(TiObject* obj, void* userContext);
    int setErrorCallback(TiObject* obj, void* userContext);
    int getErrorCallback(TiObject* obj, void* userContext);
    int setListenQueueSize(TiObject* obj, void* userContext);
    int getListenQueueSize(TiObject* obj, void* userContext);

    void setupEvents(TiEventContainerFactory* containerFactory);

    // TCP Socket methods
    void connect();
    void close();
    void accept(TiEvent* errorCallback, int timeout);
    void listen();
    int write(NativeBufferObject* buffer, int offset = -1, int length = -1);
    int read(NativeBufferObject* buffer, int offset = -1, int length = -1);

protected:
    virtual ~NativeTCPSocketObject();

private:
    NativeTCPSocketObject();
    NativeTCPSocketObject(const NativeTCPSocketObject&);
    NativeTCPSocketObject& operator=(const NativeTCPSocketObject&);
    QTcpSocket* tcpClient_;
    QTcpServer* tcpServer_;
    int port_;
    QString hostName_;
    TI_SOCKET_STATE socketState_;

    // Callback container
    TiEventContainer* eventContainer_;
    TCPSocketEventHandler* eventHandler_;
};

// Event handler for Ti.Network.Socket.TCP
class TCPSocketEventHandler : public QObject
{
    Q_OBJECT
public:
    explicit TCPSocketEventHandler(TiEventContainer* eventContainer, NativeTCPSocketObject* owner)
    {
        Q_ASSERT(owner != NULL);
        eventContainer_ = eventContainer;
        owner_ = owner;
    }
    virtual ~TCPSocketEventHandler() {}

public slots:
    void connected()
    {
        owner_->socketState_ = SOCKET_STATE_CONNECTED;
        eventContainer_->fireEvent();
    }

    void accepted()
    {
        // Disconnect current slot from signal
        QObject::disconnect(owner_->tcpServer_, SIGNAL(newConnection()), owner_->eventHandler_, SLOT(accepted()));

        HandleScope handleScope;
        QTcpSocket* inboundSocket = owner_->tcpServer_->nextPendingConnection();
        Handle<Value> socketObj = eventContainer_->getV8ValueProperty("socket");
        Handle<ObjectTemplate> global = TiObject::getObjectTemplateFromJsObject(socketObj);
        Handle<Object> result = global->NewInstance();
        TiTCPSocketObject* socket = (TiTCPSocketObject*)TiObject::getTiObjectFromJsObject(socketObj);
        TiTCPSocketObject* inBoundSocket = TiTCPSocketObject::createTCP(socket->getNativeObjectFactory());
        inBoundSocket->setValue(result);
        TiObject::setTiObjectToJsObject(result, inBoundSocket);
        NativeTCPSocketObject* inBoundNative = (NativeTCPSocketObject*)inBoundSocket->getNativeObject();
        inBoundNative->tcpClient_ =  inboundSocket;
        inBoundNative->socketState_ = SOCKET_STATE_CONNECTED;
        inBoundNative->port_ = inboundSocket->peerPort();
        inBoundNative->hostName_ = inboundSocket->peerAddress().toString();
        eventContainer_->setV8ValueProperty("inbound", inBoundSocket->getValue());
        eventContainer_->fireEvent();
    }

    void error(QAbstractSocket::SocketError socketError)
    {
        eventContainer_->setDataProperty("error", owner_->tcpClient_->errorString().toStdString().c_str());
        eventContainer_->setDataProperty("errorCode", socketError);
        owner_->socketState_ = SOCKET_STATE_ERROR;
        eventContainer_->fireEvent();
    }

private:
    TiEventContainer* eventContainer_;
    NativeTCPSocketObject* owner_;

    // Disable copy ctor & assignment operator
    TCPSocketEventHandler(const TCPSocketEventHandler&);
    TCPSocketEventHandler& operator=(const TCPSocketEventHandler&);
};

#endif /* NATIVETCPSOCKETOBJECT_H_ */
