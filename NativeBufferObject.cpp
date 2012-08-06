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

class SetGetBufferProperties
{
public:
    SetGetBufferProperties(const NATIVE_PROPSETGET_SETTING* map, int mapEntries)
    {
        setters_ = new NATIVE_PROPSETGET_CALLBACK[N_BUFFER_PROP_LAST];
        memset(setters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_BUFFER_PROP_LAST);
        getters_ = new NATIVE_PROPSETGET_CALLBACK[N_BUFFER_PROP_LAST];
        memset(getters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_BUFFER_PROP_LAST);
        for (int i = 0; i < mapEntries; i++)
        {
            setters_[map[i].propNumber] = map[i].setter;
            getters_[map[i].propNumber] = map[i].getter;
        }
    }
    ~SetGetBufferProperties()
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
        if (prop >= (std::size_t)N_BUFFER_PROP_LAST)
        {
            return NULL;
        }
        return setters_[prop];
    }
    NATIVE_PROPSETGET_CALLBACK GetGetterCallback(size_t prop)
    {
        if (prop >= (std::size_t)N_BUFFER_PROP_LAST)
        {
            return NULL;
        }
        return getters_[prop];
    }
private:
    SetGetBufferProperties(const SetGetBufferProperties&);
    SetGetBufferProperties& operator=(const SetGetBufferProperties&);
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
    obj->setValue(Number::New(byteOrder_));
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setByteOrder)
int NativeBufferObject::setByteOrder(TiObject* obj)
{
    int typeValue;
    int error = NativeControlObject::getInteger(obj, &typeValue);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    byteOrder_ = (Ti::Codec::TI_BYTE_ORDER)typeValue;
    return NATIVE_ERROR_OK;
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
int NativeBufferObject::getType(TiObject* /*obj*/)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setType)
int NativeBufferObject::setType(TiObject* /*obj*/)
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
        if (v8Value->IsInt32() || v8Value->IsUint32())
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
int NativeBufferObject::getValue(TiObject* /*obj*/)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

void NativeBufferObject::clear()
{
    internalData_.clear();
}

const char* NativeBufferObject::toString() const
{
    return internalData_.constData();
}

void NativeBufferObject::fill(double fillByte, int offset, int length)
{
    QByteArray newArray = QByteArray::number(fillByte);
    int size = newArray.size();
    if (offset == -1 && length == -1)
    {
        // Fills the entire byte array
        int oldSize = internalData_.size();
        for (int i = 0; i < (oldSize / size) - 1; ++i)
        {
            newArray.append(QByteArray::number(fillByte));
        }
        internalData_ = newArray;
    }
    else
    {
        for (int i = 0; i < (length / size) - 1; ++i)
        {
            newArray.append(QByteArray::number(fillByte));
        }
        internalData_.replace(offset, length, newArray);
    }
}

const static NATIVE_PROPSETGET_SETTING g_BufferPropSetGet[] =
{
    {N_BUFFER_PROP_BYTEORDER, PROP_SETGET_FUNCTION(setByteOrder), PROP_SETGET_FUNCTION(getByteOrder)},
    {N_BUFFER_PROP_LENGTH, PROP_SETGET_FUNCTION(setLength), PROP_SETGET_FUNCTION(getLength)},
    {N_BUFFER_PROP_TYPE, PROP_SETGET_FUNCTION(setType), PROP_SETGET_FUNCTION(getType)},
    {N_BUFFER_PROP_VALUE, PROP_SETGET_FUNCTION(setValue), PROP_SETGET_FUNCTION(getValue)}
};

static SetGetBufferProperties g_BufferProps(g_BufferPropSetGet, GET_ARRAY_SIZE(g_BufferPropSetGet));

int NativeBufferObject::setPropertyValue(size_t propertyNumber, TiObject* obj)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_BufferProps.GetSetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj);
}

int NativeBufferObject::getPropertyValue(size_t propertyNumber, TiObject* obj)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_BufferProps.GetGetterCallback(propertyNumber);
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
