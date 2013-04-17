/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEHTTPCLIENTOBJECT_H_
#define NATIVEHTTPCLIENTOBJECT_H_

#include <QByteArray>
#include <QObject>
#include <QNetworkReply>

#include "NativeProxyObject.h"
#include "TiConstants.h"
#include "TiV8Event.h"
#include "TiHTTPClientObject.h"

class NativeBufferObject;
class TiObject;
class TiEventContainerFactory;
class HTTPClientEventHandler;

using namespace Ti::Network::HTTPClient;

enum NATIVE_HTTPCLIENT_PROP
{
    N_HTTPCLIENT_PROP_UNDEFINED
    , N_HTTPCLIENT_PROP_AUTOENCODEURL
    , N_HTTPCLIENT_PROP_AUTOREDIRECT
    , N_HTTPCLIENT_PROP_ALLRESPONSEHEADERS
    , N_HTTPCLIENT_PROP_CACHE
    , N_HTTPCLIENT_PROP_CONNECTED
    , N_HTTPCLIENT_PROP_CONNECTIONTYPE
    , N_HTTPCLIENT_PROP_ENABLEKEEPALIVE
    , N_HTTPCLIENT_PROP_FILE
    , N_HTTPCLIENT_PROP_LOCATION
    , N_HTTPCLIENT_PROP_ONDATASTREAM
    , N_HTTPCLIENT_PROP_ONERROR
    , N_HTTPCLIENT_PROP_ONLOAD
    , N_HTTPCLIENT_PROP_ONREADYSTATECHANGE
    , N_HTTPCLIENT_PROP_ONSENDSTREAM
    , N_HTTPCLIENT_PROP_READYSTATE
    , N_HTTPCLIENT_PROP_RESPONSETEXT
    , N_HTTPCLIENT_PROP_RESPONSEDATA
    , N_HTTPCLIENT_PROP_RESPONSEXML
    , N_HTTPCLIENT_PROP_STATUS
    , N_HTTPCLIENT_PROP_STATUSTEXT
    , N_HTTPCLIENT_PROP_TIMEOUT
    , N_HTTPCLIENT_PROP_TLSVERSION
    , N_HTTPCLIENT_PROP_VALIDATESSECURECERTIFICATE
    , N_HTTPCLIENT_PROP_WITHCREDENTIALS

    /* This MUST be the last element */
    , N_HTTPCLIENT_PROP_LAST
};

enum NATIVE_HTTPCLIENT_METHOD
{
	N_HTTPCLIENT_METHOD_GET
	, N_HTTPCLIENT_METHOD_PUT
	, N_HTTPCLIENT_METHOD_POST
	, N_HTTPCLIENT_METHOD_DELELE
	, N_HTTPCLIENT_METHOD_HEAD
};

/*
 * NativeHTTPClientObject
 *
 * NativeHTTPClientObject methods
 */
class NativeHTTPClientObject : public NativeProxyObject
{
public:
    friend class HTTPClientEventHandler;
    static NativeHTTPClientObject* createHTTPClient(TiObject* tiObject);
    NATIVE_TYPE getObjectType() const;
    int setPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext);
    int getPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext);

    // Properties
    int getReadyState(TiObject* obj, void* userContext);
    int getResponseText(TiObject* obj, void* userContext);
    int setOnloadCallback(TiObject* obj, void* userContext);
    int getOnloadCallback(TiObject* obj, void* userContext);
    int setOnerrorCallback(TiObject* obj, void* userContext);
    int getOnerrorCallback(TiObject* obj, void* userContext);
    int setOnreadystatechangeCallback(TiObject* obj, void* userContext);
    int getOnreadystatechangeCallback(TiObject* obj, void* userContext);

    virtual void setupEvents(TiEventContainerFactory* containerFactory);

    // HTTPClient methods
    int abort();
    int open(const QString& method, const QUrl& url);
    int send(const QString& data);
    int clearCookies(const QString& host);
    int setRequestHeader(const QString& header, const QString& value);

protected:
    virtual ~NativeHTTPClientObject();
    void finished();

private:
    explicit NativeHTTPClientObject(TiObject* tiObject);
    NativeHTTPClientObject(const NativeHTTPClientObject&);
    NativeHTTPClientObject& operator=(const NativeHTTPClientObject&);

    TI_HTTPCLIENT_STATE readyState_;
    NATIVE_HTTPCLIENT_METHOD method_;
    QNetworkRequest request_;
    QNetworkReply* reply_;
    QNetworkAccessManager networkAccessManager_;
    HTTPClientEventHandler* eventHandler_;
    QByteArray responseData_;
};

// Event handler for Ti.Network.HTTPClient
class HTTPClientEventHandler : public QObject
{
    Q_OBJECT
public:
    explicit HTTPClientEventHandler(NativeHTTPClientObject* owner)
    {
        Q_ASSERT(owner != NULL);
        owner_ = owner;
    }
    virtual ~HTTPClientEventHandler() {}

    void attachToReply(QNetworkReply *reply)
    {
    	connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()));
    	connect(reply, SIGNAL(error()), this, SLOT(httpError(QNetworkReply::NetworkError)));
    	connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
    }

public slots:
    void httpFinished()
    {
    	owner_->finished();
        owner_->readyState_ = HTTPCLIENT_STATE_DONE;
        owner_->fireEvent(NativeProxyObject::tetREADYSTATECHANGE, NULL);
        owner_->fireEvent(NativeProxyObject::tetLOAD, NULL);
    }

    void httpReadyRead()
    {
        if (owner_->readyState_ != HTTPCLIENT_STATE_LOADING) {
        	owner_->readyState_ = HTTPCLIENT_STATE_LOADING;
        	owner_->fireEvent(NativeProxyObject::tetREADYSTATECHANGE, NULL);
        }
    }

    void httpError(QNetworkReply::NetworkError code)
    {
        owner_->events_[NativeProxyObject::tetERROR]->container()->setDataProperty(NativeProxyObject::tetERROR, owner_->reply_->errorString().toStdString().c_str());
        owner_->events_[NativeProxyObject::tetERROR]->container()->setDataProperty("errorCode", code);
        owner_->fireEvent(NativeProxyObject::tetERROR, NULL);
    }

private:
    NativeHTTPClientObject* owner_;

    // Disable copy ctor & assignment operator
    HTTPClientEventHandler(const HTTPClientEventHandler&);
    HTTPClientEventHandler& operator=(const HTTPClientEventHandler&);
};

#endif /* NATIVEHTTPCLIENTOBJECT_H_ */
