/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUDPSocketObject.h"

#include "NativeException.h"
#include "NativeUDPSocketObject.h"
#include "TiGenericFunctionObject.h"
#include "TiPropertyGetFunctionObject.h"
#include "TiPropertyMapObject.h"
#include "TiPropertySetFunctionObject.h"
#include "TiMessageStrings.h"
#include "V8Utils.h"

using namespace titanium;

const static TiProperty g_tiProperties[] =
{
    {
        "ondata", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_UDPSOCKET_PROP_ONDATA
    },

    {
        "onstarted", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_UDPSOCKET_PROP_ONSTARTED
    },

    {
        "onerror", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_UDPSOCKET_PROP_ONERROR
    },

    {
        "port", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_UDPSOCKET_PROP_PORT
    }
};

TiUDPSocketObject::TiUDPSocketObject()
    : TiProxy("UDP")
{
}

TiUDPSocketObject::~TiUDPSocketObject()
{
}

void TiUDPSocketObject::addObjectToParent(TiObject* parent)
{
	TiUDPSocketObject* obj = new TiUDPSocketObject;
    parent->addMember(obj);
    obj->setAttachedObject(parent);
    obj->release();
}

TiUDPSocketObject* TiUDPSocketObject::createUDP(NativeObjectFactory* objectFactory)
{
	TiUDPSocketObject* obj = new TiUDPSocketObject();
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUDPSocketObject::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiProxy::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_UDPSOCKET, this);
        setNativeObject(obj);
        obj->release();
    }
}

void TiUDPSocketObject::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();
    setTiSocketMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));

    TiGenericFunctionObject::addGenericFunctionToParent(this, "start", this, _start);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "stop", this, _stop);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "sendString", this, _sendString);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "sendBytes", this, _sendBytes);
}

void TiUDPSocketObject::setTiSocketMappingProperties(const TiProperty* props, int propertyCount)
{
    string name;
    char c[2];
    c[1] = 0;
    for (int i = 0; i < propertyCount; i++)
    {
        TiObject* value = TiPropertyMapObject::addProperty(this, props[i].propertyName, props[i].nativePropertyNumber,
                          _valueModify, _getValue, this);
        // For all properties that have write permissions, add a setter method, e.g., myLabel.text=<my text>; myLabel.setText(<my text>);
        if (props[i].permissions & TI_PROP_PERMISSION_WRITE)
        {
            c[0] = toupper(props[i].propertyName[0]);
            name = "set";
            name += c;
            name += props[i].propertyName + 1;
            TiPropertySetFunctionObject::addPropertySetter(this, value, name.c_str());
        }
        // For all properties that have read permissions, add a getter method, e.g., var test=myLabel.text; var test=myLabel.getText();
        if (props[i].permissions & TI_PROP_PERMISSION_READ)
        {
            c[0] = toupper(props[i].propertyName[0]);
            name = "get";
            name += c;
            name += props[i].propertyName + 1;
            TiPropertyGetFunctionObject::addPropertyGetter(this, value, name.c_str());
        }
        value->release();
    }
}

Handle<Value> TiUDPSocketObject::_getValue(int propertyNumber, void* context)
{
	TiUDPSocketObject* self = (TiUDPSocketObject*) context;
    NativeUDPSocketObject* object = (NativeUDPSocketObject*)self->getNativeObject();
    TiObject value;
    if (object != NULL)
    {
        object->getPropertyValue(propertyNumber, &value, context);
    }
    return value.getValue();
}

VALUE_MODIFY TiUDPSocketObject::_valueModify(int propertyNumber, TiObject* value, void* context)
{
	TiUDPSocketObject* self = (TiUDPSocketObject*) context;
    NativeUDPSocketObject* object = (NativeUDPSocketObject*)self->getNativeObject();
    if (object == NULL)
    {
        return VALUE_MODIFY_NOT_SUPPORTED;
    }
    VALUE_MODIFY modify = VALUE_MODIFY_ALLOW;
    switch (object->setPropertyValue(propertyNumber, value, self))
    {
    case NATIVE_ERROR_OK:
        modify = VALUE_MODIFY_ALLOW;
        break;
    case NATIVE_ERROR_NOTSUPPORTED:
        modify = VALUE_MODIFY_NOT_SUPPORTED;
        break;
    default:
        modify = VALUE_MODIFY_INVALID;
        break;
    }
    object->release();
    return modify;
}

Handle<Value> TiUDPSocketObject::_start(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1) {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    Handle<Value> value = args[0];
    int port = -1;
    if (value->IsNumber() || value->IsNumberObject()) {
    	port = Handle<Number>::Cast(value)->Value();
    } else if (value->IsObject()) {
    	value = Handle<Object>::Cast(value)->Get(String::New("port"));
    	port = Handle<Number>::Cast(value)->Value();
    }
    if (port <= 0) {
    	return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    HandleScope handleScope;
    TiUDPSocketObject* obj = (TiUDPSocketObject*) userContext;
    NativeUDPSocketObject* nudp = (NativeUDPSocketObject*) obj->getNativeObject();
    try {
        nudp->listen(port);
    }
    catch (NativeException& ne) {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}

Handle<Value> TiUDPSocketObject::_stop(void* userContext, TiObject* /*caller*/, const Arguments& /*args*/)
{
    HandleScope handleScope;
    TiUDPSocketObject* obj = (TiUDPSocketObject*) userContext;
    NativeUDPSocketObject* nudp = (NativeUDPSocketObject*) obj->getNativeObject();
    try {
        nudp->close();
    }
    catch (NativeException& ne) {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}

Handle<Value> TiUDPSocketObject::_sendString(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1) {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    Handle<Value> value = args[0];
    QString data;
    if (!value->IsObject()) {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    Handle<Object> dict = Handle<Object>::Cast(value);
    if (!dict->Has(String::New("data"))) {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    data = V8ValueToQString(dict->Get(String::New("data")));
    int port = -1;
    if (dict->Has(String::New("port"))) {
        port = Handle<Number>::Cast(dict->Get(String::New("port")))->Value();
    }
    QString host;
    if (dict->Has(String::New("host"))) {
        host = V8ValueToQString(dict->Get(String::New("host")));
    }

    HandleScope handleScope;
    TiUDPSocketObject* obj = (TiUDPSocketObject*) userContext;
    NativeUDPSocketObject* nudp = (NativeUDPSocketObject*) obj->getNativeObject();
    try {
        nudp->send(data.toUtf8(), !host.isEmpty() ? QHostAddress(host) : QHostAddress::Broadcast, port);
    }
    catch (NativeException& ne) {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}

Handle<Value> TiUDPSocketObject::_sendBytes(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1) {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    Handle<Value> value = args[0];
    QByteArray data;
    if (!value->IsObject()) {
    	return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    Handle<Object> dict = Handle<Object>::Cast(value);
    if (!dict->Has(String::New("data"))) {
    	return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    data = TiObject::getByteArrayFromValue(dict->Get(String::New("data")));
    int port = -1;
    if (dict->Has(String::New("port"))) {
    	port = Handle<Number>::Cast(dict->Get(String::New("port")))->Value();
    }
    QString host;
    if (dict->Has(String::New("host"))) {
    	host = V8ValueToQString(dict->Get(String::New("host")));
    }

    HandleScope handleScope;
    TiUDPSocketObject* obj = (TiUDPSocketObject*) userContext;
    NativeUDPSocketObject* nudp = (NativeUDPSocketObject*) obj->getNativeObject();
    try {
        nudp->send(data, !host.isEmpty() ? QHostAddress(host) : QHostAddress::Broadcast, port);
    }
    catch (NativeException& ne) {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}

