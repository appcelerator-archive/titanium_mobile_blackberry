/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeBufferObject.h"
#include "NativeControlObject.h"
#include "TiObject.h"

#define PROP_SETGET_FUNCTION(NAME)      prop_##NAME

#define PROP_SETGET(NAME)               static int prop_##NAME(NativeBufferObject* buffer, TiObject* obj) \
    {\
        return buffer->NAME(obj);\
    }

#define GET_ARRAY_SIZE(ARRAY)           (int)(sizeof(ARRAY)/sizeof(*(ARRAY)))

typedef int (*NATIVE_PROPSETGET_CALLBACK)(NativeBufferObject*, TiObject*);

struct NATIVE_PROPSETGET_SETTING
{
    NATIVE_BUFFER_PROP propNumber;
    NATIVE_PROPSETGET_CALLBACK setter;
    NATIVE_PROPSETGET_CALLBACK getter;
};

class SetGetProperties
{
public:
    SetGetProperties(const NATIVE_PROPSETGET_SETTING* map, int mapEntries)
    {
        setters_ = new NATIVE_PROPSETGET_CALLBACK[N_PROP_LAST];
        memset(setters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_PROP_LAST);
        getters_ = new NATIVE_PROPSETGET_CALLBACK[N_PROP_LAST];
        memset(getters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_PROP_LAST);
        for (int i = 0; i < mapEntries; i++)
        {
            setters_[map[i].propNumber] = map[i].setter;
            getters_[map[i].propNumber] = map[i].getter;
        }
    }
    ~SetGetProperties()
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
        if (prop >= (std::size_t)N_PROP_LAST)
        {
            return NULL;
        }
        return setters_[prop];
    }
    NATIVE_PROPSETGET_CALLBACK GetGetterCallback(size_t prop)
    {
        if (prop >= (std::size_t)N_PROP_LAST)
        {
            return NULL;
        }
        return getters_[prop];
    }
private:
    // Disabled default and copy constructors
    SetGetProperties();
    SetGetProperties(const SetGetProperties& prop);
    // Disabled assignment operator
    const SetGetProperties& operator = (const SetGetProperties& prop);
    NATIVE_PROPSETGET_CALLBACK* setters_;
    NATIVE_PROPSETGET_CALLBACK* getters_;
};

NativeBufferObject::~NativeBufferObject()
{
}

int NativeBufferObject::getObjectType() const
{
    return N_TYPE_BUFFER;
}

NativeBufferObject* NativeBufferObject::createBuffer()
{
    return new NativeBufferObject;
}

PROP_SETGET(getByteOrder)
int NativeBufferObject::getByteOrder(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(getLength)
int NativeBufferObject::getLength(TiObject* obj)
{
    obj->setValue(Number::New(internalData_.size()));
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setLength)
int NativeBufferObject::setLength(TiObject* obj)
{
    int lengthValue;
    int error = NativeControlObject::getInteger(obj, &lengthValue);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    internalData_.resize(lengthValue);
    return NATIVE_ERROR_OK;
}

PROP_SETGET(getType)
int NativeBufferObject::getType(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setValue)
int NativeBufferObject::setValue(TiObject* obj)
{
    Handle<Value> v8Value = obj->getValue();
    if (v8Value.IsEmpty())
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    if (v8Value->IsNumber() || !v8Value->IsNumberObject())
    {
        if (v8Value->IsInt32())
        {
            Handle<Number> num = Handle<Number>::Cast(v8Value);
            int value = (int)num->Value();
            internalData_ = QByteArray::number(value);
        }
        else
        {
            Handle<Number> num = Handle<Number>::Cast(v8Value);
            double value = (double)num->Value();
            internalData_ = QByteArray::number(value);
        }
    }
    else if (v8Value->IsString() || v8Value->IsStringObject())
    {
        Handle<Value> value = v8Value->ToString();
        Handle<String> v8string = Handle<String>::Cast(value);
        String::Utf8Value v8UtfString(v8string);
        internalData_ = QByteArray(*v8UtfString);
    }
    return NATIVE_ERROR_OK;
}

PROP_SETGET(getValue)
int NativeBufferObject::getValue(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

void NativeBufferObject::clear()
{
    internalData_.clear();
}

const static NATIVE_PROPSETGET_SETTING g_propSetGet[] =
{
    {N_BUFFER_PROP_BYTEORDER, NULL, PROP_SETGET_FUNCTION(getByteOrder)},
    {N_BUFFER_PROP_LENGTH, PROP_SETGET_FUNCTION(setLength), PROP_SETGET_FUNCTION(getLength)},
    {N_BUFFER_PROP_TYPE, NULL, PROP_SETGET_FUNCTION(getType)},
    {N_BUFFER_PROP_VALUE, PROP_SETGET_FUNCTION(setValue), PROP_SETGET_FUNCTION(getValue)}
};

static SetGetProperties g_props(g_propSetGet, GET_ARRAY_SIZE(g_propSetGet));


int NativeBufferObject::setPropertyValue(size_t propertyNumber, TiObject* obj)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_props.GetSetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj);
}

int NativeBufferObject::getPropertyValue(size_t propertyNumber, TiObject* obj)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_props.GetGetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj);
}

void NativeBufferObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeProxyObject::setupEvents(containerFactory);
}
