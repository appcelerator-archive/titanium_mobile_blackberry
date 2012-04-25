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
#include "TiV8Event.h"

const static TI_PROPERTY g_tiProperties[] =
        {
                {"backgroundColor", "setBackgroundColor", "black", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
                        NATIVE_TYPE_CSTRING, N_PROP_SET_BACKGROUND_COLOR},

                {"label", "setLabel", "", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
                        NATIVE_TYPE_CSTRING, N_PROP_SET_LABEL},

                {"max", "setMax", "0", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
                        NATIVE_TYPE_INT | NATIVE_TYPE_DOUBLE, N_PROP_SET_MAX},

                {"min", "setMin", "0", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
                        NATIVE_TYPE_INT | NATIVE_TYPE_DOUBLE, N_PROP_SET_MIN},

                {"text", "setText", "", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
                        NATIVE_TYPE_CSTRING, N_PROP_SET_TEXT},

                {"textAlign", "setTextAlign", "center", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
                        NATIVE_TYPE_CSTRING | NATIVE_TYPE_INT, N_PROP_SET_TEXT_ALIGN},

                {"top", "setTop", "0", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
                        NATIVE_TYPE_INT | NATIVE_TYPE_DOUBLE, N_PROP_SET_TOP},

                {"value", "setValue", "0", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
                        NATIVE_TYPE_INT, N_PROP_SET_VALUE}
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
    for (int i = 0; i < propertyCount; i++)
    {
        TiObject* value = TiPropertyMapObject::addProperty(this, prop[i].propertyName, prop[i].nativePropertyNumber,
                                                           prop[i].supportedTypes,
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
    TiGenericFunctionObject::addGenericFunctionToParent(this, "addEventListener", this, addEventListener_);
    setTiMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));
}

void TiUIBase::setParametersFromObject(Local<Object> obj)
{
    HandleScope handleScope;
    Handle < Value > value;
    Handle < Value > controlValue = getValue();
    if (!controlValue->IsObject())
    {
        return;
    }
    Handle < Object > self = Handle < Object > ::Cast(controlValue);
    Handle < Array > propNames = obj->GetPropertyNames();
    uint32_t props = propNames->Length();
    Local < Value > propValue;
    Handle < String > propString;
    TiObject* foundProp;
    for (uint32_t i = 0; i < props; i++)
    {
        propString = Handle < String > ::Cast(propNames->Get(Integer::New(i)));
        String::Utf8Value propNameUTF(propString);
        foundProp = onLookupMember(*propNameUTF);
        if (foundProp != NULL)
        {
            propValue = obj->Get(propString);
            foundProp->setValue(propValue);
        }
    }
}

VALUE_MODIFY TiUIBase::valueModify(int propertyNumber, const char* value, void* context)
{
    TiUIBase* self = (TiUIBase*) context;
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

void TiUIBase::onAddEventListener(const char* eventName, Handle<Function> eventFunction)
{
    HandleScope handleScope;
    NativeObject* no = getNativeObject();
    if (no == NULL)
    {
        return;
    }
    Handle < Object > source = Handle < Object > ::Cast(getValue());
    Handle < ObjectTemplate > global = getObjectTemplateFromJsObject(getValue());
    TiV8Event* event = TiV8Event::createEvent(eventName, eventFunction, source);
    no->setEventHandler(eventName, event);
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
        // TODO: expand this exception
    }
    return Undefined();
}

Handle<Value> TiUIBase::addEventListener_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    if ((args.Length() != 2) || (!args[0]->IsString()) || (!args[1]->IsFunction()))
    {
        return Undefined();
    }
    TiUIBase* obj = (TiUIBase*) userContext;
    Handle < String > eventName = Handle < String > ::Cast(args[0]);
    Handle < Function > func = Handle < Function > ::Cast(args[1]);
    String::Utf8Value eventNameUTF(eventName);
    obj->onAddEventListener(*eventNameUTF, func);
    return Undefined();
}
