/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeBlobObject.h"

#include <QBuffer>
#include <QFile>

#include <v8.h>

#include "TiObject.h"

using namespace v8;

static NativeBlobObject::PropertyInfo properties[] = {
    { N_BLOB_PROP_FILE, &NativeBlobObject::isFile, 0 },
    { N_BLOB_PROP_LENGTH, &NativeBlobObject::getLength, 0 },
    { N_BLOB_PROP_MIMETYPE, &NativeBlobObject::getMIMEType, 0 },
    { N_BLOB_PROP_TEXT, &NativeBlobObject::getText, 0 }
};
static const int propertyCount = sizeof(properties) / sizeof(properties[0]);

NativeBlobObject* NativeBlobObject::createBlob(TiObject* object) {
    return new NativeBlobObject(object);
}

NativeBlobObject::NativeBlobObject(TiObject* object)
  : NativeProxyObject(object)
  , PropertyDelegateBase<NativeBlobObject>(this, properties, propertyCount) {
}

void NativeBlobObject::setData(const QByteArray& data, const QString& mimeType) {
    data_ = data;
    device_.reset(new QBuffer(&data_));
    mimeType_ = mimeType;
}

void NativeBlobObject::setData(const QString& filename) {
    data_ = QByteArray();
    device_.reset(new QFile(filename));
    // TODO(josh) add MIME guessing by extension
}

QByteArray NativeBlobObject::data() {
    if (!data_.isEmpty()) {
        // Data is already loaded into memory.
        return data_;
    }

    if (device_.isNull()) {
        // If there is no valid device return nothing.
        return QByteArray();
    }

    // Read all data available from the input device.
    device_->open(QIODevice::ReadOnly);
    data_ = device_->readAll();
    device_->close();

    return data_;
}

int NativeBlobObject::setPropertyValue(size_t propertyNumber, TiObject* obj) {
    return setProperty(propertyNumber, obj);
}

int NativeBlobObject::getPropertyValue(size_t propertyNumber, TiObject* obj) {
    return getProperty(propertyNumber, obj);
}

int NativeBlobObject::isFile(TiObject* value) {
    bool isFile = false;
    if (device_ && device_->inherits("QFile")) {
        isFile = true;
    }
    value->setValue(Boolean::New(isFile));
    return NATIVE_ERROR_OK;
}

int NativeBlobObject::getLength(TiObject* value) {
    int32_t len;
    if (data_.isEmpty() && device_) {
        len = device_->size();
    } else {
        len = data_.size();
    }
    value->setValue(Integer::New(len));
    return NATIVE_ERROR_OK;
}

int NativeBlobObject::getMIMEType(TiObject* value) {
    value->setValue(String::New(mimeType_.toUtf8().constData()));
    return NATIVE_ERROR_OK;
}

int NativeBlobObject::getText(TiObject* value) {
    // Assume the data is encoded using ASCII or UTF-8.
    QByteArray d = data();
    value->setValue(String::New(d.constData(), d.size()));
    return NATIVE_ERROR_OK;
}

