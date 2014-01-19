/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeHTTPClientObject.h"

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

#define PROP_SETGET(NAME)               static int prop_##NAME(NativeHTTPClientObject* httpClient, TiObject* obj, void * userContext) \
    {\
        return httpClient->NAME(obj, userContext);\
    }

#define GET_ARRAY_SIZE(ARRAY)           (int)(sizeof(ARRAY)/sizeof(*(ARRAY)))

typedef int (*NATIVE_PROPSETGET_CALLBACK)(NativeHTTPClientObject*, TiObject*, void*);

struct NATIVE_PROPSETGET_SETTING
{
    NATIVE_HTTPCLIENT_PROP propNumber;
    NATIVE_PROPSETGET_CALLBACK setter;
    NATIVE_PROPSETGET_CALLBACK getter;
};

class SetGetHTTPClientProperties
{
public:
	SetGetHTTPClientProperties(const NATIVE_PROPSETGET_SETTING* map, int mapEntries)
    {
        setters_ = new NATIVE_PROPSETGET_CALLBACK[N_HTTPCLIENT_PROP_LAST];
        memset(setters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_HTTPCLIENT_PROP_LAST);
        getters_ = new NATIVE_PROPSETGET_CALLBACK[N_HTTPCLIENT_PROP_LAST];
        memset(getters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_HTTPCLIENT_PROP_LAST);
        for (int i = 0; i < mapEntries; i++)
        {
            setters_[map[i].propNumber] = map[i].setter;
            getters_[map[i].propNumber] = map[i].getter;
        }
    }
    ~SetGetHTTPClientProperties()
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
        if (prop >= (std::size_t)N_HTTPCLIENT_PROP_LAST)
        {
            return NULL;
        }
        return setters_[prop];
    }
    NATIVE_PROPSETGET_CALLBACK GetGetterCallback(size_t prop)
    {
        if (prop >= (std::size_t)N_HTTPCLIENT_PROP_LAST)
        {
            return NULL;
        }
        return getters_[prop];
    }
private:
    SetGetHTTPClientProperties(const SetGetHTTPClientProperties&);
    SetGetHTTPClientProperties& operator=(const SetGetHTTPClientProperties&);
    NATIVE_PROPSETGET_CALLBACK* setters_;
    NATIVE_PROPSETGET_CALLBACK* getters_;
};

static QSettings defaultSettings("app/native/assets/app_properties.ini",
                                 QSettings::IniFormat);

QNetworkCookieJar* NativeHTTPClientObject::cookieStore_ = new QNetworkCookieJar();

NativeHTTPClientObject::NativeHTTPClientObject(TiObject* tiObject)
    : NativeProxyObject(tiObject)
{
    eventHandler_ = NULL;

    QString aguid = defaultSettings.value("aguid").toString();
	aguid_ = aguid.toAscii();
    networkAccessManager_.setCookieJar(cookieStore_);

    request_.setRawHeader("X-Titanium-ID", aguid_);
}

NativeHTTPClientObject::~NativeHTTPClientObject()
{
	delete reply_;
    delete eventHandler_;
    //delete cookieStore_;
}

NATIVE_TYPE NativeHTTPClientObject::getObjectType() const
{
    return N_TYPE_HTTPCLIENT;
}

NativeHTTPClientObject* NativeHTTPClientObject::createHTTPClient(TiObject* tiObject)
{
    return new NativeHTTPClientObject(tiObject);
}

PROP_SETGET(setOnloadCallback)
int NativeHTTPClientObject::setOnloadCallback(TiObject* obj, void* userContext)
{
    Handle<Value> value = obj->getValue();
    if (value->IsFunction())
    {
    	TiHTTPClientObject* context = (TiHTTPClientObject*)userContext;
        Handle<Object> source = Handle<Object>::Cast(context->getValue());
        TiV8Event* acceptEvent = TiV8Event::createEvent(tetLOAD, Handle<Function>::Cast(value), source);
        setEventHandler(tetLOAD, acceptEvent);
        acceptEvent->release();
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_INVALID_ARG;
}

PROP_SETGET(getOnloadCallback)
int NativeHTTPClientObject::getOnloadCallback(TiObject* /*obj*/, void* /*userContext*/)
{
    // TODO: Implement this
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setOnerrorCallback)
int NativeHTTPClientObject::setOnerrorCallback(TiObject* obj, void* userContext)
{
    Handle<Value> value = obj->getValue();
    if (value->IsFunction())
    {
    	TiHTTPClientObject* context = (TiHTTPClientObject*)userContext;
        Handle<Object> source = Handle<Object>::Cast(context->getValue());
        TiV8Event* acceptEvent = TiV8Event::createEvent(tetERROR, Handle<Function>::Cast(value), source);
        setEventHandler(tetERROR, acceptEvent);
        acceptEvent->release();
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_INVALID_ARG;
}

PROP_SETGET(getOnerrorCallback)
int NativeHTTPClientObject::getOnerrorCallback(TiObject* /*obj*/, void* /*userContext*/)
{
    // TODO: Implement this
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setOnreadystatechangeCallback)
int NativeHTTPClientObject::setOnreadystatechangeCallback(TiObject* obj, void* userContext)
{
    Handle<Value> value = obj->getValue();
    if (value->IsFunction())
    {
    	TiHTTPClientObject* context = (TiHTTPClientObject*)userContext;
        Handle<Object> source = Handle<Object>::Cast(context->getValue());
        TiV8Event* acceptEvent = TiV8Event::createEvent(tetREADYSTATECHANGE, Handle<Function>::Cast(value), source);
        setEventHandler(tetREADYSTATECHANGE, acceptEvent);
        acceptEvent->release();
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_INVALID_ARG;
}

PROP_SETGET(getOnreadystatechangeCallback)
int NativeHTTPClientObject::getOnreadystatechangeCallback(TiObject* /*obj*/, void* /*userContext*/)
{
    // TODO: Implement this
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(getReadyState)
int NativeHTTPClientObject::getReadyState(TiObject* obj, void* /*userContext*/)
{
    obj->setValue(Number::New(readyState_));
    return NATIVE_ERROR_OK;
}

PROP_SETGET(getAllResponseHeaders)
int NativeHTTPClientObject::getAllResponseHeaders(TiObject* obj, void* /*userContext*/)
{

    if (reply_ == NULL) {
        return NATIVE_ERROR_INVALID_ARG;
    }
    
    QList< QPair<QByteArray, QByteArray> > rawHeader = reply_->rawHeaderPairs();
    QString rawHeaderList;
    
    for (int i = 0; i < rawHeader.length(); i++){
        QPair<QByteArray, QByteArray> pair = rawHeader.value(i);
        rawHeaderList.append(pair.first + " : " + pair.second + "\n");
    }
    
    obj->setValue(String::New(rawHeaderList.toAscii(), rawHeaderList.size()));
    
    return NATIVE_ERROR_OK;
}

PROP_SETGET(getStatus)
int NativeHTTPClientObject::getStatus(TiObject* obj, void* /*userContext*/)
{
    if (reply_ == NULL) {
        return NATIVE_ERROR_INVALID_ARG;
    }
    
    QVariant status = reply_->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    
    obj->setValue(Number::New(status.toInt()));

    return NATIVE_ERROR_OK;
}

PROP_SETGET(getStatusText)
int NativeHTTPClientObject::getStatusText(TiObject* obj, void* /*userContext*/)
{
    if (reply_ == NULL) {
        return NATIVE_ERROR_INVALID_ARG;
    }
    
    QString statusText = reply_->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    
    obj->setValue(String::New(statusText.toUtf8(), statusText.size()));
    
    return NATIVE_ERROR_OK;
}

PROP_SETGET(getResponseText)
int NativeHTTPClientObject::getResponseText(TiObject* obj, void* /*userContext*/)
{
    if (reply_ == NULL) {
        return NATIVE_ERROR_INVALID_ARG;
    }

    if (responseData_.isEmpty()) {
        if (reply_ == NULL) {
            return NATIVE_ERROR_INVALID_ARG;
        }
        responseData_ = reply_->readAll();
    }

    obj->setValue(String::New(responseData_.constData(), responseData_.size()));

    return NATIVE_ERROR_OK;
}

const static NATIVE_PROPSETGET_SETTING g_HTTPClientPropSetGet[] =
{
    {N_HTTPCLIENT_PROP_ONLOAD, PROP_SETGET_FUNCTION(setOnloadCallback), PROP_SETGET_FUNCTION(getOnloadCallback)},
    {N_HTTPCLIENT_PROP_ONERROR, PROP_SETGET_FUNCTION(setOnerrorCallback), PROP_SETGET_FUNCTION(getOnerrorCallback)},
    {N_HTTPCLIENT_PROP_ONREADYSTATECHANGE, PROP_SETGET_FUNCTION(setOnreadystatechangeCallback), PROP_SETGET_FUNCTION(getOnreadystatechangeCallback)},
    {N_HTTPCLIENT_PROP_READYSTATE, NULL, PROP_SETGET_FUNCTION(getReadyState)},
    {N_HTTPCLIENT_PROP_ALLRESPONSEHEADERS, NULL, PROP_SETGET_FUNCTION(getAllResponseHeaders)},
    {N_HTTPCLIENT_PROP_STATUS, NULL, PROP_SETGET_FUNCTION(getStatus)},
    {N_HTTPCLIENT_PROP_STATUSTEXT, NULL, PROP_SETGET_FUNCTION(getStatusText)},
    {N_HTTPCLIENT_PROP_RESPONSETEXT, NULL, PROP_SETGET_FUNCTION(getResponseText)}
};

static SetGetHTTPClientProperties g_HTTPClientProps(g_HTTPClientPropSetGet, GET_ARRAY_SIZE(g_HTTPClientPropSetGet));

int NativeHTTPClientObject::setPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_HTTPClientProps.GetSetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj, userContext);
}

int NativeHTTPClientObject::getPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_HTTPClientProps.GetGetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj, userContext);
}

void NativeHTTPClientObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeProxyObject::setupEvents(containerFactory);
    eventHandler_ = new HTTPClientEventHandler(this);
    events_.insert(tetLOAD, EventPairSmartPtr(containerFactory->createEventContainer(), eventHandler_));
    events_.insert(tetERROR, EventPairSmartPtr(containerFactory->createEventContainer(), eventHandler_));
    events_.insert(tetREADYSTATECHANGE, EventPairSmartPtr(containerFactory->createEventContainer(), eventHandler_));
}

int NativeHTTPClientObject::abort()
{
	if (reply_ == NULL) {
		return NATIVE_ERROR_INVALID_ARG;
	}
	reply_->abort();
	delete reply_;
	reply_ = NULL;
	readyState_ = HTTPCLIENT_STATE_UNSENT;
	return NATIVE_ERROR_OK;
}

int NativeHTTPClientObject::open(const QString& method, const QUrl& url)
{
    request_.setUrl(url);
    method_ = N_HTTPCLIENT_METHOD_GET;
    if (method == "PUT") {
        method_ = N_HTTPCLIENT_METHOD_PUT;
    } else if (method == "POST") {
        method_ = N_HTTPCLIENT_METHOD_POST;
    }
        return NATIVE_ERROR_OK;
}

int NativeHTTPClientObject::send(const QString& data)
{
	(void)data;
	switch (method_) {
	case N_HTTPCLIENT_METHOD_GET:
		reply_ = networkAccessManager_.get(request_);
		break;
	case N_HTTPCLIENT_METHOD_POST:
		reply_ = networkAccessManager_.post(request_, data.toUtf8());
		break;
	default:
		return NATIVE_ERROR_NOTSUPPORTED;
	}
	eventHandler_->attachToReply(reply_);

	readyState_ = HTTPCLIENT_STATE_OPENED;
    fireEvent(NativeProxyObject::tetREADYSTATECHANGE, NULL);
	return NATIVE_ERROR_OK;
}

int NativeHTTPClientObject::clearCookies(const QString& host)
{
	(void)host;
	return NATIVE_ERROR_OK;
}

int NativeHTTPClientObject::setRequestHeader(const QString& header, const QString& value)
{
	request_.setRawHeader(header.toAscii(), value.toAscii());

	return NATIVE_ERROR_OK;
}


void NativeHTTPClientObject::finished()
{
}
