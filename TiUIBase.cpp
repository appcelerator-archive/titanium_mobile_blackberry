/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIBase.h"
#include "TiGenericFunctionObject.h"
#include "TiPropertySetFunctionObject.h"
#include "TiPropertyMapObject.h"

const static TI_PROPERTY g_tiProperties[] =
{
    {"text", "setText", "",TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_PROP_SET_TEXT},
    {"textAlign", "setTextAlign", "center", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_SET_TEXT_ALIGN}
};

TiUIBase::TiUIBase()
{
    nativeObjectFactory_ = NULL;
    nativeObject_ = NULL;
}

TiUIBase::~TiUIBase()
{
    if (!createConfig_.IsEmpty())
    {
        createConfig_.Dispose();
    }
    if (nativeObject_ != NULL)
    {
        nativeObject_->release();
        nativeObject_ = NULL;
    }
}

TiUIBase::TiUIBase(NativeObjectFactory* nativeObjectFactory, const char* name)
        : TiObject(name)
{
    nativeObjectFactory_ = nativeObjectFactory;
    nativeObject_ = NULL;
}

void TiUIBase::onStartMessagePump()
{
    if (nativeObject_ != NULL)
    {
        nativeObject_->completeInitialization();
    }
    TiObject::onStartMessagePump();
}

bool TiUIBase::isUIObject() const
{
    return true;
}

NativeObjectFactory* TiUIBase::getNativeObjectFactory() const
{
    return nativeObjectFactory_;
}

bool TiUIBase::canAddMembers() const
{
    return true;
}

NativeObject* TiUIBase::getNativeObject() const
{
    if (nativeObject_ != NULL)
    {
        nativeObject_->addRef();
    }
    return nativeObject_;
}

void TiUIBase::setTiMappingProperties(const TI_PROPERTY* prop, int propertyCount)
{
    int i;
    for (i = 0; i < propertyCount; i++)
    {
        TiObject* value = TiPropertyMapObject::addProperty(this, prop[i].propertyName, prop[i].nativePropertyNumber,
                                                           valueModify, this);
        if ((prop[i].permissions & TI_PROP_PERMISSION_WRITE) && (prop[i].propertySetterFunctionName != NULL))
        {
            TiPropertySetFunctionObject::addPropertySetter(this, value, prop[i].propertySetterFunctionName);
        }
        value->release();
    }
}

void TiUIBase::setNativeObject(NativeObject* nativeObject)
{
    if (nativeObject != NULL)
    {
        nativeObject->addRef();
    }
    if (nativeObject_ != NULL)
    {
        nativeObject_->release();
    }
    nativeObject_ = nativeObject;
}

void TiUIBase::onCreateStaticMembers()
{
    TiObject::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "add", this, add_);
    setTiMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));
}

void TiUIBase::setParametersFromObject(Local<Object> obj)
{
    HandleScope handleScope;
    int i;
    Handle < Value > value;
    Handle < Value > controlValue = getValue();
    if (!controlValue->IsObject())
    {
        return;
    }
    Handle < Object > self = Handle < Object > ::Cast(controlValue);
    for (i = 0; i < (int) (sizeof(g_tiProperties) / sizeof(*g_tiProperties)); i++)
    {
        value = obj->Get(String::New(g_tiProperties[i].propertyName));
        if (!value.IsEmpty())
        {
            self->Set(String::New(g_tiProperties[i].propertyName), value);
        }
    }
}

VALUE_MODIFY TiUIBase::valueModify(int propertyNumber, const char* value, void* context)
{
    TiUIBase* self = (TiUIBase*) context;
    NativeObject* object = self->getNativeObject();
    VALUE_MODIFY modify = VALUE_MODIFY_ALLOW;
    if (object == NULL)
    {
        return VALUE_MODIFY_NOT_SUPPORTED;
    }
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

Handle<Value> TiUIBase::add_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIBase* obj = (TiUIBase*) userContext;
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        TiObject* addObj = getTiObjectFromJsObject(args[0]);
        if ((addObj == NULL) || (!addObj->isUIObject()))
        {
            return Undefined();
        }
        TiUIBase* uiObj = (TiUIBase*) addObj;
        NativeObject* childNO = uiObj->getNativeObject();
        NativeObject* parentNO = obj->getNativeObject();
        parentNO->addChildNativeObject(childNO);
        childNO->release();
        parentNO->release();
    }
    else
    {
        // TODO: expand this excaption
    }
    return Undefined();
}
