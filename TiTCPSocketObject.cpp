/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiTCPSocketObject.h"

#include "NativeTCPSocketObject.h"
#include "TiGenericFunctionObject.h"
#include "TiPropertyGetFunctionObject.h"
#include "TiPropertyMapObject.h"
#include "TiPropertySetFunctionObject.h"

const static TiProperty g_tiProperties[] =
{
    {
        "host", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_SOCKET_PROP_HOST
    },

    {
        "port", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_SOCKET_PROP_PORT
    },
};

TiTCPSocketObject::TiTCPSocketObject()
    : TiProxy("TCP")
{
}

TiTCPSocketObject::~TiTCPSocketObject()
{
}

void TiTCPSocketObject::addObjectToParent(TiObject* parent)
{
    TiTCPSocketObject* obj = new TiTCPSocketObject;
    parent->addMember(obj);
    obj->release();
}

TiTCPSocketObject* TiTCPSocketObject::createTCP(NativeObjectFactory* objectFactory)
{
    TiTCPSocketObject* obj = new TiTCPSocketObject();
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiTCPSocketObject::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiProxy::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_TCPSOCKET);
        setNativeObject(obj);
        obj->release();
    }
}

void TiTCPSocketObject::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();
    setTiBufferMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));

    TiGenericFunctionObject::addGenericFunctionToParent(this, "connect", this, _connect);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "close", this, _close);
}

void TiTCPSocketObject::setTiBufferMappingProperties(const TiProperty* props, int propertyCount)
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

Handle<Value> TiTCPSocketObject::_getValue(int propertyNumber, void* context)
{
    TiTCPSocketObject* self = (TiTCPSocketObject*) context;
    NativeObject* object = self->getNativeObject();
    TiObject value;
    if (object != NULL)
    {
        object->getPropertyValue(propertyNumber, &value);
    }
    return value.getValue();
}

VALUE_MODIFY TiTCPSocketObject::_valueModify(int propertyNumber, TiObject* value, void* context)
{
    TiTCPSocketObject* self = (TiTCPSocketObject*) context;
    NativeObject* object = self->getNativeObject();
    if (object == NULL)
    {
        return VALUE_MODIFY_NOT_SUPPORTED;
    }
    VALUE_MODIFY modify = VALUE_MODIFY_ALLOW;
    switch (object->setPropertyValue(propertyNumber, value))
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

Handle<Value> TiTCPSocketObject::_connect(void* userContext, TiObject* /*caller*/, const Arguments& /*args*/)
{
    HandleScope handleScope;
    TiTCPSocketObject* obj = (TiTCPSocketObject*) userContext;
    NativeTCPSocketObject* ntcp = (NativeTCPSocketObject*) obj->getNativeObject();
    ntcp->connect();
    return Undefined();
}

Handle<Value> TiTCPSocketObject::_close(void* userContext, TiObject* /*caller*/, const Arguments& /*args*/)
{
    HandleScope handleScope;
    TiTCPSocketObject* obj = (TiTCPSocketObject*) userContext;
    NativeTCPSocketObject* ntcp = (NativeTCPSocketObject*) obj->getNativeObject();
    ntcp->close();
    return Undefined();
}
