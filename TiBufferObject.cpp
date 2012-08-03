/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiBufferObject.h"
#include "NativeBufferObject.h"
#include "TiGenericFunctionObject.h"
#include "TiPropertyGetFunctionObject.h"
#include "TiPropertySetFunctionObject.h"
#include "TiPropertyMapObject.h"

const static TiProperty g_tiProperties[] =
{
    {
        "byteOrder", TI_PROP_PERMISSION_READ, N_BUFFER_PROP_BYTEORDER
    },

    {
        "length", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_BUFFER_PROP_LENGTH
    },

    {
        "type", TI_PROP_PERMISSION_READ, N_BUFFER_PROP_TYPE
    },

    {
        "value", TI_PROP_PERMISSION_READ, N_BUFFER_PROP_VALUE
    }
};


TiBufferObject::TiBufferObject()
    : TiProxy("Buffer")
{
}

TiBufferObject::~TiBufferObject()
{
}

void TiBufferObject::addObjectToParent(TiObject* parent)
{
    TiBufferObject* obj = new TiBufferObject;
    parent->addMember(obj);
}

TiBufferObject* TiBufferObject::createBuffer(NativeObjectFactory* objectFactory)
{
    TiBufferObject* obj = new TiBufferObject();
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiBufferObject::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiProxy::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_BUFFER);
        setNativeObject(obj);
        obj->release();
    }
}

void TiBufferObject::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();
    setTiBufferMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));

    TiGenericFunctionObject::addGenericFunctionToParent(this, "append", this, _append);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "copy", this, _copy);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "fill", this, _fill);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "insert", this, _insert);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "clone", this, _clone);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "clear", this, _clear);
}

void TiBufferObject::setTiBufferMappingProperties(const TiProperty* props, int propertyCount)
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

Handle<Value> TiBufferObject::_getValue(int propertyNumber, void* context)
{
    TiBufferObject* self = (TiBufferObject*) context;
    NativeObject* object = self->getNativeObject();
    TiObject value;
    if (object != NULL)
    {
        object->getPropertyValue(propertyNumber, &value);
    }
    return value.getValue();
}

VALUE_MODIFY TiBufferObject::_valueModify(int propertyNumber, TiObject* value, void* context)
{
    TiBufferObject* self = (TiBufferObject*) context;
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

Handle<Value> TiBufferObject::_append(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    Handle<Object> result;
    return handleScope.Close(result);
}

Handle<Value> TiBufferObject::_copy(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    Handle<Object> result;
    return handleScope.Close(result);
}

Handle<Value> TiBufferObject::_fill(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    Handle<Object> result;
    return handleScope.Close(result);
}

Handle<Value> TiBufferObject::_insert(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    Handle<Object> result;
    return handleScope.Close(result);
}

Handle<Value> TiBufferObject::_clone(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    Handle<Object> result;
    return handleScope.Close(result);
}

Handle<Value> TiBufferObject::_clear(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiBufferObject* obj = (TiBufferObject*) userContext;
    NativeBufferObject* nbo = (NativeBufferObject*) obj->getNativeObject();
    nbo->clear();
    return Undefined();
}
