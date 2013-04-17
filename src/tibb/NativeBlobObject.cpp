/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeBlobObject.h"

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

int NativeBlobObject::setPropertyValue(size_t propertyNumber, TiObject* obj) {
    return setProperty(propertyNumber, obj);
}

int NativeBlobObject::getPropertyValue(size_t propertyNumber, TiObject* obj) {
    return getProperty(propertyNumber, obj);
}

int NativeBlobObject::isFile(TiObject* value) {
    // File based blobs not yet supported.
    value->setValue(Null());
    return NATIVE_ERROR_OK;
}

int NativeBlobObject::getLength(TiObject* value) {
    value->setValue(Integer::New(data_.size()));
    return NATIVE_ERROR_OK;
}

int NativeBlobObject::getMIMEType(TiObject* value) {
    value->setValue(String::New(mimeType_.toUtf8().constData()));
    return NATIVE_ERROR_OK;
}

int NativeBlobObject::getText(TiObject* value) {
    // Assume the data is encoded using ASCII or UTF-8.
    value->setValue(String::New(data_.constData(), data_.size()));
    return NATIVE_ERROR_OK;
}

