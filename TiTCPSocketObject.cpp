/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiTCPSocketObject.h"

#include "NativeException.h"
#include "NativeTCPSocketObject.h"
#include "TiBufferObject.h"
#include "TiGenericFunctionObject.h"
#include "TiPropertyGetFunctionObject.h"
#include "TiPropertyMapObject.h"
#include "TiPropertySetFunctionObject.h"
#include "TiMessageStrings.h"

const static TiProperty g_tiProperties[] =
{
    {
        "accepted", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_SOCKET_PROP_ACCEPTED
    },

    {
        "connected", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_SOCKET_PROP_CONNECTED
    },

    {
        "error", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_SOCKET_PROP_ERROR
    },

    {
        "host", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_SOCKET_PROP_HOST
    },

    {
        "listenQueueSize", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_SOCKET_PROP_LISTENQUEUESIZE
    },

    {
        "port", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_SOCKET_PROP_PORT
    },

    {
        "state", TI_PROP_PERMISSION_READ, N_SOCKET_PROP_STATE
    },

    {
        "timeout", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_SOCKET_PROP_TIMEOUT
    }
};

TiTCPSocketObject::TiTCPSocketObject()
    : TiIOStreamObject("TCP")
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
        TiIOStreamObject::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_TCPSOCKET);
        setNativeObject(obj);
        obj->release();
    }
}

void TiTCPSocketObject::onCreateStaticMembers()
{
    TiIOStreamObject::onCreateStaticMembers();
    setTiBufferMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));

    TiGenericFunctionObject::addGenericFunctionToParent(this, "connect", this, _connect);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "close", this, _close);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "accept", this, _accept);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "listen", this, _listen);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "write", this, _write);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "read", this, _read);
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
    NativeTCPSocketObject* object = (NativeTCPSocketObject*)self->getNativeObject();
    TiObject value;
    if (object != NULL)
    {
        object->getPropertyValue(propertyNumber, &value, context);
    }
    return value.getValue();
}

VALUE_MODIFY TiTCPSocketObject::_valueModify(int propertyNumber, TiObject* value, void* context)
{
    TiTCPSocketObject* self = (TiTCPSocketObject*) context;
    NativeTCPSocketObject* object = (NativeTCPSocketObject*)self->getNativeObject();
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

Handle<Value> TiTCPSocketObject::_connect(void* userContext, TiObject* /*caller*/, const Arguments& /*args*/)
{
    HandleScope handleScope;
    TiTCPSocketObject* obj = (TiTCPSocketObject*) userContext;
    NativeTCPSocketObject* ntcp = (NativeTCPSocketObject*) obj->getNativeObject();
    try
    {
        ntcp->connect();
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}

Handle<Value> TiTCPSocketObject::_close(void* userContext, TiObject* /*caller*/, const Arguments& /*args*/)
{
    HandleScope handleScope;
    TiTCPSocketObject* obj = (TiTCPSocketObject*) userContext;
    NativeTCPSocketObject* ntcp = (NativeTCPSocketObject*) obj->getNativeObject();
    try
    {
        ntcp->close();
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}

Handle<Value> TiTCPSocketObject::_accept(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    HandleScope handleScope;
    TiTCPSocketObject* obj = (TiTCPSocketObject*) userContext;
    NativeTCPSocketObject* ntcp = (NativeTCPSocketObject*) obj->getNativeObject();
    try
    {
        // TODO: Parse accept parameters
        ntcp->accept(NULL, 0);
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}

Handle<Value> TiTCPSocketObject::_listen(void* userContext, TiObject* /*caller*/, const Arguments& /*args*/)
{
    HandleScope handleScope;
    TiTCPSocketObject* obj = (TiTCPSocketObject*) userContext;
    NativeTCPSocketObject* ntcp = (NativeTCPSocketObject*) obj->getNativeObject();
    try
    {
        ntcp->listen();
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}

Handle<Value> TiTCPSocketObject::_write(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    HandleScope handleScope;
    TiTCPSocketObject* obj = (TiTCPSocketObject*) userContext;
    NativeTCPSocketObject* ntcp = (NativeTCPSocketObject*) obj->getNativeObject();

    NativeBufferObject* nboSource = NULL;
    if (args[0]->IsObject())
    {
        TiBufferObject* objSource = dynamic_cast<TiBufferObject*>(getTiObjectFromJsObject(args[0]));
        if (objSource != NULL)
        {
            nboSource = (NativeBufferObject*) objSource->getNativeObject();
        }
    }

    // Invalid argument passed
    if (nboSource == NULL)
    {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }

    // Optional arguments provided
    int sourceOffset = -1, sourceLength = -1;
    if (args.Length() > 1)
    {
        // Should provided both offset and length
        if (args.Length() < 3)
        {
            return ThrowException(String::New(Ti::Msg::Missing_argument));
        }

        Handle<Number> sourceOffsetNum = Handle<Number>::Cast(args[1]);
        Handle<Number> sourceLengthNum = Handle<Number>::Cast(args[2]);
        sourceOffset = (int)sourceOffsetNum->Value();
        sourceLength = (int)sourceLengthNum->Value();
    }

    int bytesWritten = 0;
    try
    {
        bytesWritten = ntcp->write(nboSource, sourceOffset, sourceLength);
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }

    Handle<Number> result = Number::New(bytesWritten);
    return handleScope.Close(result);
}

Handle<Value> TiTCPSocketObject::_read(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }

    HandleScope handleScope;
    TiTCPSocketObject* obj = (TiTCPSocketObject*) userContext;
    NativeTCPSocketObject* ntcp = (NativeTCPSocketObject*) obj->getNativeObject();

    NativeBufferObject* nboSource = NULL;
    if (args[0]->IsObject())
    {
        TiBufferObject* objSource = dynamic_cast<TiBufferObject*>(getTiObjectFromJsObject(args[0]));
        if (objSource != NULL)
        {
            nboSource = (NativeBufferObject*) objSource->getNativeObject();
        }
    }

    // Invalid argument passed
    if (nboSource == NULL)
    {
        return ThrowException(String::New(Ti::Msg::Invalid_arguments));
    }

    // Optional arguments provided
    int sourceOffset = -1, sourceLength = -1;
    if (args.Length() > 1)
    {
        // Should provided both offset and length
        if (args.Length() < 3)
        {
            return ThrowException(String::New(Ti::Msg::Missing_argument));
        }

        Handle<Number> sourceOffsetNum = Handle<Number>::Cast(args[1]);
        Handle<Number> sourceLengthNum = Handle<Number>::Cast(args[2]);
        sourceOffset = (int)sourceOffsetNum->Value();
        sourceLength = (int)sourceLengthNum->Value();
    }

    int bytesRead = 0;
    try
    {
        bytesRead = ntcp->read(nboSource, sourceOffset, sourceLength);
    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }

    Handle<Number> result = Number::New(bytesRead);
    return handleScope.Close(result);
}
