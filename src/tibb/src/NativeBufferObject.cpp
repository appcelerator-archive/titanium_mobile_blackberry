/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeBufferObject.h"

#include "NativeControlObject.h"
#include "NativeException.h"
#include "NativeMessageStrings.h"
#include "TiObject.h"

static NativeBufferObject::PropertyInfo properties[] = {
    {
        N_BUFFER_PROP_BYTEORDER,
        &NativeBufferObject::getByteOrder,
        &NativeBufferObject::setByteOrder
    },
    {
        N_BUFFER_PROP_LENGTH,
        &NativeBufferObject::getLength,
        &NativeBufferObject::setLength
    },
    {
        N_BUFFER_PROP_TYPE,
        &NativeBufferObject::getType,
        &NativeBufferObject::setType
    },
    {
        N_BUFFER_PROP_VALUE,
        &NativeBufferObject::getValue,
        &NativeBufferObject::setValue
    }
};

NativeBufferObject::NativeBufferObject(TiObject* object)
  : NativeProxyObject(object)
  , PropertyDelegateBase<NativeBufferObject>(this, properties, N_BUFFER_PROP_LAST) {
}

NativeBufferObject::~NativeBufferObject()
{
}

NATIVE_TYPE NativeBufferObject::getObjectType() const
{
    return N_TYPE_BUFFER;
}

NativeBufferObject* NativeBufferObject::createBuffer(TiObject* tiObject)
{
    return new NativeBufferObject(tiObject);
}

int NativeBufferObject::getByteOrder(TiObject* obj)
{
    obj->setValue(Number::New(byteOrder_));
    return NATIVE_ERROR_OK;
}

int NativeBufferObject::setByteOrder(TiObject* /*obj*/)
{
    /* COMMENTED OUT FOR NOW. IT IS NOT USED IN ANVIL
    int typeValue;
    int error = NativeControlObject::getInteger(obj, &typeValue);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    byteOrder_ = (Ti::Codec::TI_BYTE_ORDER)typeValue;
    return NATIVE_ERROR_OK;
    */
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeBufferObject::getLength(TiObject* obj)
{
    obj->setValue(Number::New(internalData_.size()));
    return NATIVE_ERROR_OK;
}

int NativeBufferObject::setLength(TiObject* obj)
{
    int lengthValue;
    int error = NativeControlObject::getInteger(obj, &lengthValue);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    int oldSize = internalData_.size();
    if (lengthValue > oldSize)
    {
        internalData_.append(QByteArray(lengthValue - oldSize, '\0'));
    }
    else
    {
        internalData_.truncate(lengthValue);
    }
    return NATIVE_ERROR_OK;
}

int NativeBufferObject::getType(TiObject* /*obj*/)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeBufferObject::setType(TiObject* /*obj*/)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeBufferObject::setValue(TiObject* obj)
{
    Handle<Value> v8Value = obj->getValue();
    if (v8Value.IsEmpty())
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    if (v8Value->IsNumber() || v8Value->IsNumberObject())
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

int NativeBufferObject::getValue(TiObject* /*obj*/)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

void NativeBufferObject::clear()
{
    //reset data, but keep size the same
    internalData_.fill('\0');
}

const char* NativeBufferObject::toString() const
{
    return internalData_.constData();
}

void NativeBufferObject::fill(char fillByte, int offset, int length)
{
    if (offset == -1 && length == -1)
    {
        // Fills the entire byte array
        internalData_.fill(fillByte);
    }
    else
    {
        /*
         * Do not allow buffer to grow.
         * - Checked offset and length to be valid
         * - Checked offset not to be above the buffer size
         * - Checked length to be in range [offset, buffer.size()]
         */
        if (length < 0 || offset < 0 || (offset >= internalData_.size()) ||
                (internalData_.size() - offset) < length)
        {
            throw NativeException(QString(Native::Msg::Out_of_bounds).toStdString());
        }
        QByteArray newArray(length, fillByte);
        internalData_.replace(offset, length, newArray);
    }
}

int NativeBufferObject::copy(NativeBufferObject* sourceBuffer, int offset, int sourceOffset, int sourceLength)
{
    if (offset >= internalData_.size() || offset < 0)
    {
        throw NativeException(QString(Native::Msg::Out_of_bounds).toStdString());
    }
    int bytesWritten = 0;
    const QByteArray& sourceData = sourceBuffer->internalData_;
    int sourceSize = 0, leftSize = 0;
    leftSize = internalData_.size() - offset;
    if (sourceOffset == -1 && sourceLength == -1)
    {
        sourceSize = sourceData.size();
    }
    else
    {
        /*
         * Validate the source buffer's sourceOffset and sourceLength.
         * - Checked sourceOffset and sourceLength to be valid
         * - Checked sourceOffset not to be above the buffer size
         * - Checked sourceLength to be in range [sourceOffset, sourcebuffer.size()]
         */
        if (sourceLength < 0 || sourceOffset < 0 || (sourceOffset >= sourceData.size()) ||
                (sourceData.size() - sourceOffset) < sourceLength)
        {
            throw NativeException(QString(Native::Msg::Out_of_bounds).toStdString());
        }
        sourceSize = sourceLength;
    }

    bytesWritten = (leftSize < sourceSize) ? leftSize : sourceSize;

    // Do not expand the original buffer if there is not enough room for data from sourceBuffer
    internalData_.replace(offset, bytesWritten, sourceData.mid(sourceOffset == -1 ? 0 : sourceOffset, bytesWritten));

    return bytesWritten;
}

int NativeBufferObject::append(NativeBufferObject* sourceBuffer, int sourceOffset, int sourceLength)
{
    int bytesWritten = 0;
    const QByteArray& sourceData = sourceBuffer->internalData_;
    if (sourceOffset == -1 && sourceLength == -1)
    {
        bytesWritten = sourceData.size();
        internalData_.append(sourceData);
    }
    else
    {
        /*
         * Validate the source buffer's sourceOffset and sourceLength.
         * - Checked sourceOffset and sourceLength to be valid
         * - Checked sourceOffset not to be above the buffer size
         * - Checked sourceLength to be in range [sourceOffset, sourcebuffer.size()]
         */
        if (sourceLength < 0 || sourceOffset < 0 || (sourceOffset >= sourceData.size()) ||
                (sourceData.size() - sourceOffset) < sourceLength)
        {
            throw NativeException(QString(Native::Msg::Out_of_bounds).toStdString());
        }
        bytesWritten = sourceLength;
        internalData_.append(sourceData.mid(sourceOffset, sourceLength));
    }
    return bytesWritten;
}

NativeBufferObject* NativeBufferObject::clone(TiObject* tiObject, int sourceOffset, int sourceLength)
{
    NativeBufferObject* cloneBuffer = NULL;
    if (sourceOffset == -1 && sourceLength == -1)
    {
        cloneBuffer = new NativeBufferObject(tiObject);
        cloneBuffer->internalData_ = QByteArray(internalData_);
    }
    else
    {
        /*
         * Validate the source buffer's sourceOffset and sourceLength.
         * - Checked sourceOffset and sourceLength to be valid
         * - Checked sourceOffset not to be above the buffer size
         * - Checked sourceLength to be in range [sourceOffset, sourcebuffer.size()]
         */
        if (sourceLength < 0 || sourceOffset < 0 || (sourceOffset >= internalData_.size()) ||
                (internalData_.size() - sourceOffset) < sourceLength)
        {
            throw NativeException(QString(Native::Msg::Out_of_bounds).toStdString());
        }
        cloneBuffer = new NativeBufferObject(tiObject);
        cloneBuffer->internalData_ = QByteArray(internalData_.mid(sourceOffset, sourceLength));
    }
    return cloneBuffer;
}

int NativeBufferObject::insert(NativeBufferObject* sourceBuffer, int offset, int sourceOffset, int sourceLength)
{
    if (offset >= internalData_.size() || offset < 0)
    {
        throw NativeException(QString(Native::Msg::Out_of_bounds).toStdString());
    }
    int bytesWritten = 0;
    const QByteArray& sourceData = sourceBuffer->internalData_;
    if (sourceOffset == -1 && sourceLength == -1)
    {
        bytesWritten = sourceData.size();
        internalData_.insert(offset, sourceData);
    }
    else
    {
        /*
         * Validate the source buffer's sourceOffset and sourceLength.
         * - Checked sourceOffset and sourceLength to be valid
         * - Checked sourceOffset not to be above the buffer size
         * - Checked sourceLength to be in range [sourceOffset, sourcebuffer.size()]
         */
        if (sourceLength < 0 || sourceOffset < 0 || (sourceOffset >= sourceData.size()) ||
                (sourceData.size() - sourceOffset) < sourceLength)
        {
            throw NativeException(QString(Native::Msg::Out_of_bounds).toStdString());
        }
        bytesWritten = sourceLength;
        internalData_.insert(offset, sourceData.mid(sourceOffset, sourceLength));
    }

    return bytesWritten;
}

int NativeBufferObject::bufferSize() const
{
    return internalData_.size();
}

void NativeBufferObject::replaceInternalData(const QByteArray& newArray, int offset, int length)
{
    internalData_ = internalData_.replace(offset, length, newArray);
}

int NativeBufferObject::setPropertyValue(size_t propertyNumber, TiObject* obj)
{
    return setProperty(propertyNumber, obj);
}

int NativeBufferObject::getPropertyValue(size_t propertyNumber, TiObject* obj)
{
    return getProperty(propertyNumber, obj);
}

void NativeBufferObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeProxyObject::setupEvents(containerFactory);
}
