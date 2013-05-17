/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiBlobObject.h"

#include "NativeBlobObject.h"

const static TiProperty g_tiProperties[] = {
    { "file", TI_PROP_PERMISSION_READ, N_BLOB_PROP_FILE },
    { "length", TI_PROP_PERMISSION_READ, N_BLOB_PROP_LENGTH },
    { "mimeType", TI_PROP_PERMISSION_READ, N_BLOB_PROP_MIMETYPE },
    { "text", TI_PROP_PERMISSION_READ, N_BLOB_PROP_TEXT }
};

TiBlobObject* TiBlobObject::createBlob(NativeObjectFactory* objectFactory) {
    TiBlobObject* obj = new TiBlobObject();
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

TiBlobObject::TiBlobObject()
    : TiProxy("Blob") {
}

TiBlobObject::~TiBlobObject() {
}

void TiBlobObject::onCreateStaticMembers() {
    TiProxy::onCreateStaticMembers();
    setTiMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));
}

void TiBlobObject::initializeTiObject(TiObject* parentContext) {
    if (!isInitialized())
    {
        TiProxy::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_BLOB, this);
        setNativeObject(obj);
        obj->release();
    }
}

void TiBlobObject::setData(const QByteArray& data, const QString& mimeType) {
    NativeBlobObject* blob = static_cast<NativeBlobObject*>(getNativeObject());
    blob->setData(data, mimeType);
}

QByteArray TiBlobObject::data() const {
    NativeBlobObject* blob = static_cast<NativeBlobObject*>(getNativeObject());
    return blob->data();
}

QString TiBlobObject::mimeType() const {
    NativeBlobObject* blob = static_cast<NativeBlobObject*>(getNativeObject());
    return blob->mimeType();
}

