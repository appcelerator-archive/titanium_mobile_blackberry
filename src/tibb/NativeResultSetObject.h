/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVERESULTSETOBJECT_H_
#define NATIVERESULTSETOBJECT_H_

#include "NativeProxyObject.h"
#include <QtCore/QObject>
#include <QtNetwork/qtcpserver>
#include <QtNetwork/qtcpsocket>
#include "TiConstants.h"
#include "TiV8Event.h"
#include "TiResultSetObject.h"

class NativeBufferObject;
class TiObject;
class TiEventContainerFactory;
class ResultSetEventHandler;

using namespace Ti::Network::Socket;

enum NATIVE_RESULTSET_PROP
{
     N_RESULTSET_PROP_CONNECTED

    /* This MUST be the last element */
    , N_RESULTSET_PROP_LAST
};

/*
 * NativeResultSetObject
 *
 * NativeResultSetObject methods
 */
class NativeResultSetObject : public NativeProxyObject
{
public:
    friend class ResultSetEventHandler;
    static NativeResultSetObject* createResultSet(TiObject* tiObject);
    int getObjectType() const;
    int setPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext);
    int getPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext);

    // Properties
    int setConnectedCallback(TiObject* obj, void* userContext);
    int getConnectedCallback(TiObject* obj, void* userContext);

    void setupEvents(TiEventContainerFactory* containerFactory);

    // ResultSet methods
    void connect();

protected:
    virtual ~NativeResultSetObject();

private:
    explicit NativeResultSetObject(TiObject* tiObject);
    NativeResultSetObject(const NativeResultSetObject&);
    NativeResultSetObject& operator=(const NativeResultSetObject&);

    ResultSetEventHandler* eventHandler_;
};

// Event handler for Ti.Network.Socket.TCP
class ResultSetEventHandler : public QObject
{
    Q_OBJECT
public:
    explicit ResultSetEventHandler(NativeResultSetObject* owner)
    {
        Q_ASSERT(owner != NULL);
        owner_ = owner;
    }
    virtual ~ResultSetEventHandler() {}

public slots:
    void connected()
    {
        //owner_->socketState_ = SOCKET_STATE_CONNECTED;
        //owner_->fireEvent(NativeProxyObject::tetCONNECTED, NULL);
    }

private:
    NativeResultSetObject* owner_;

    // Disable copy ctor & assignment operator
    ResultSetEventHandler(const ResultSetEventHandler&);
    ResultSetEventHandler& operator=(const ResultSetEventHandler&);
};

#endif /* NATIVERESULTSETOBJECT_H_ */
