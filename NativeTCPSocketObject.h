/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVETCPSOCKETOBJECT_H_
#define NATIVETCPSOCKETOBJECT_H_

#include "NativeProxyObject.h"
#include <QtNetwork/qtcpsocket>

class TiObject;
class TiEventContainerFactory;

enum NATIVE_SOCKET_PROP
{
    N_SOCKET_PROP_UNDEFINED
    , N_SOCKET_PROP_HOST
    , N_SOCKET_PROP_PORT

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
    static NativeTCPSocketObject* createTCPSocket();
    int getObjectType() const;
    int setPropertyValue(size_t propertyNumber, TiObject* obj);
    int getPropertyValue(size_t propertyNumber, TiObject* obj);
    int setHost(TiObject* obj);
    int getHost(TiObject* obj);
    int setPort(TiObject* obj);
    int getPort(TiObject* obj);
    void setupEvents(TiEventContainerFactory* containerFactory);

    void connect();
    void close();

protected:
    virtual ~NativeTCPSocketObject();

private:
    NativeTCPSocketObject() {};
    NativeTCPSocketObject(const NativeTCPSocketObject&);
    NativeTCPSocketObject& operator=(const NativeTCPSocketObject&);
    // Native TCP socket
    QTcpSocket tcpSocket_;
    int port_;
    QString hostName_;
};


#endif /* NATIVETCPSOCKETOBJECT_H_ */
