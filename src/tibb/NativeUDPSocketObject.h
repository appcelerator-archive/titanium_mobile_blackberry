/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEUDPSOCKETOBJECT_H_
#define NATIVEUDPSOCKETOBJECT_H_

#include "NativeProxyObject.h"
#include <QtCore/QObject>
#include <QtNetwork/QUdpSocket>
#include "TiConstants.h"
#include "TiV8Event.h"
#include "TiUDPSocketObject.h"

class NativeBufferObject;
class TiObject;
class TiEventContainerFactory;
class UDPSocketEventHandler;

using namespace Ti::Network::Socket;

enum NATIVE_UDPSOCKET_PROP
{
    N_UDPSOCKET_PROP_UNDEFINED
    , N_UDPSOCKET_PROP_ONSTARTED
    , N_UDPSOCKET_PROP_ONDATA
    , N_UDPSOCKET_PROP_ONERROR
    , N_UDPSOCKET_PROP_PORT
    /* This MUST be the last element */
    , N_UDPSOCKET_PROP_LAST
};

/*
 * NativeUDPSocketObject
 *
 * NativeUDPSocketObject methods
 */
class NativeUDPSocketObject : public NativeProxyObject
{
public:
    friend class UDPSocketEventHandler;
    static NativeUDPSocketObject* createUDPSocket(TiObject* tiObject);
    int getObjectType() const;
    int setPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext);
    int getPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext);

    // Properties
    int setPort(TiObject* obj, void* userContext);
    int getPort(TiObject* obj, void* userContext);
    int setStartedCallback(TiObject* obj, void* userContext);
    int getStartedCallback(TiObject* obj, void* userContext);
    int setDataCallback(TiObject* obj, void* userContext);
    int getDataCallback(TiObject* obj, void* userContext);
    int setErrorCallback(TiObject* obj, void* userContext);
    int getErrorCallback(TiObject* obj, void* userContext);

    void setupEvents(TiEventContainerFactory* containerFactory);

    // UDP Socket methods
    void listen(int port);
    void close();
    void send(const QByteArray& datagram, const QHostAddress& addr, int port);

protected:
    virtual ~NativeUDPSocketObject();
    void datagramReady();

private:
    explicit NativeUDPSocketObject(TiObject* tiObject);
    NativeUDPSocketObject(const NativeUDPSocketObject&);
    NativeUDPSocketObject& operator=(const NativeUDPSocketObject&);
    QUdpSocket* udpSocket_;
    int port_;

    UDPSocketEventHandler* eventHandler_;
};

// Event handler for Ti.Network.Socket.UDP
class UDPSocketEventHandler : public QObject
{
    Q_OBJECT
public:
    explicit UDPSocketEventHandler(NativeUDPSocketObject* owner)
    {
        Q_ASSERT(owner != NULL);
        owner_ = owner;
    }
    virtual ~UDPSocketEventHandler() {}

public slots:
    void udpReadyRead()
    {
    	owner_->datagramReady();
    }

    void udpError(QAbstractSocket::SocketError socketError)
    {
        owner_->events_[NativeProxyObject::tetERROR]->container()->setDataProperty(NativeProxyObject::tetERROR, owner_->udpSocket_->errorString().toStdString().c_str());
        owner_->events_[NativeProxyObject::tetERROR]->container()->setDataProperty("errorCode", socketError);
        owner_->fireEvent(NativeProxyObject::tetERROR, NULL);
    }

private:
    NativeUDPSocketObject* owner_;

    // Disable copy ctor & assignment operator
    UDPSocketEventHandler(const UDPSocketEventHandler&);
    UDPSocketEventHandler& operator=(const UDPSocketEventHandler&);
};

#endif /* NATIVEUDPSOCKETOBJECT_H_ */
