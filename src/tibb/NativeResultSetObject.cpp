/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeResultSetObject.h"

#include "NativeBufferObject.h"
#include "NativeControlObject.h"
#include "NativeException.h"
#include "NativeMessageStrings.h"
#include "TiObject.h"
#include "TiV8Event.h"


using namespace v8;

#define PROP_SETGET_FUNCTION(NAME)      prop_##NAME

#define PROP_SETGET(NAME)               static int prop_##NAME(NativeResultSetObject* ResultSet, TiObject* obj, void * userContext) \
    {\
        return ResultSet->NAME(obj, userContext);\
    }

#define GET_ARRAY_SIZE(ARRAY)           (int)(sizeof(ARRAY)/sizeof(*(ARRAY)))

typedef int (*NATIVE_PROPSETGET_CALLBACK)(NativeResultSetObject*, TiObject*, void*);

struct NATIVE_PROPSETGET_SETTING
{
    NATIVE_RESULTSET_PROP propNumber;
    NATIVE_PROPSETGET_CALLBACK setter;
    NATIVE_PROPSETGET_CALLBACK getter;
};

class SetGetResultSetProperties
{
public:
    SetGetResultSetProperties(const NATIVE_PROPSETGET_SETTING* map, int mapEntries)
    {
        setters_ = new NATIVE_PROPSETGET_CALLBACK[N_RESULTSET_PROP_LAST];
        memset(setters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_RESULTSET_PROP_LAST);
        getters_ = new NATIVE_PROPSETGET_CALLBACK[N_RESULTSET_PROP_LAST];
        memset(getters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_RESULTSET_PROP_LAST);
        for (int i = 0; i < mapEntries; i++)
        {
            setters_[map[i].propNumber] = map[i].setter;
            getters_[map[i].propNumber] = map[i].getter;
        }
    }
    ~SetGetResultSetProperties()
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
        if (prop >= (std::size_t)N_RESULTSET_PROP_LAST)
        {
            return NULL;
        }
        return setters_[prop];
    }
    NATIVE_PROPSETGET_CALLBACK GetGetterCallback(size_t prop)
    {
        if (prop >= (std::size_t)N_RESULTSET_PROP_LAST)
        {
            return NULL;
        }
        return getters_[prop];
    }
private:
    SetGetResultSetProperties(const SetGetResultSetProperties&);
    SetGetResultSetProperties& operator=(const SetGetResultSetProperties&);
    NATIVE_PROPSETGET_CALLBACK* setters_;
    NATIVE_PROPSETGET_CALLBACK* getters_;
};


PROP_SETGET(setConnectedCallback)
int NativeResultSetObject::setConnectedCallback(TiObject* obj, void* userContext)
{
	/*
    if (socketState_ != RESULTSET_STATE_INITIALIZED)
    {
        throw NativeException(Native::Msg::Invalid_socket_state);
    }
    Handle<Value> value = obj->getValue();
    if (value->IsFunction())
    {
        TiResultSetObject* context = (TiResultSetObject*)userContext;
        Handle<Object> source = Handle<Object>::Cast(context->getValue());
        TiV8Event* connectEvent = TiV8Event::createEvent(tetCONNECTED, Handle<Function>::Cast(value), source);
        setEventHandler(tetCONNECTED, connectEvent);
        events_[tetCONNECTED]->container->setV8ValueProperty("socket", context->getValue());
        connectEvent->release();
        return NATIVE_ERROR_OK;
    }
    */

    return NATIVE_ERROR_INVALID_ARG;
}

PROP_SETGET(getConnectedCallback)
int NativeResultSetObject::getConnectedCallback(TiObject* /*obj*/, void* /*userContext*/)
{
    // TODO: Implement this
    return NATIVE_ERROR_NOTSUPPORTED;
}


NativeResultSetObject::~NativeResultSetObject() {
}

int NativeResultSetObject::getObjectType() const {
    return N_TYPE_RESULTSET;
}

NativeResultSetObject* NativeResultSetObject::createResultSet(TiObject* tiObject) {
    return new NativeResultSetObject(tiObject);
}

const static NATIVE_PROPSETGET_SETTING g_ResultSetPropSetGet[] = {
    {N_RESULTSET_PROP_CONNECTED, PROP_SETGET_FUNCTION(setConnectedCallback), PROP_SETGET_FUNCTION(getConnectedCallback)}
};

static SetGetResultSetProperties g_ResultSetProps(g_ResultSetPropSetGet, GET_ARRAY_SIZE(g_ResultSetPropSetGet));

int NativeResultSetObject::setPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_ResultSetProps.GetSetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj, userContext);
}

int NativeResultSetObject::getPropertyValue(size_t propertyNumber, TiObject* obj, void* userContext)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_ResultSetProps.GetGetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj, userContext);
}

void NativeResultSetObject::setupEvents(TiEventContainerFactory* containerFactory) {

    /*
    NativeProxyObject::setupEvents(containerFactory);
    if (tcpClient_ == NULL)
    {
        tcpClient_ = new QResultSet();
    }
    eventHandler_ = new ResultSetEventHandler(this);
    events_.insert(tetCONNECTED, EventPairSmartPtr(containerFactory->createEventContainer(), eventHandler_));
    events_.insert(tetERROR, EventPairSmartPtr(containerFactory->createEventContainer(), eventHandler_));
    events_.insert(tetACCEPTED, EventPairSmartPtr(containerFactory->createEventContainer(), eventHandler_));
    QObject::connect(tcpClient_, SIGNAL(connected()), eventHandler_, SLOT(connected()));
    QObject::connect(tcpClient_, SIGNAL(error(QAbstractSocket::SocketError)), eventHandler_, SLOT(error(QAbstractSocket::SocketError)));
    */
}

void NativeResultSetObject::connect() {

	/*
    if (hostName_.isEmpty() || port_ == -1)
    {
        throw NativeException(Native::Msg::Invalid_hostname_or_port);
    }
    if (socketState_ == RESULTSET_STATE_CONNECTED || socketState_ == RESULTSET_STATE_LISTENING)
    {
        throw NativeException(Native::Msg::Invalid_socket_state);
    }
    Q_ASSERT(tcpClient_ != NULL);
    tcpClient_->connectToHost(hostName_, port_);
    */
}
