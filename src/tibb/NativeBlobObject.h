/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEBLOBOBJECT_H_
#define NATIVEBLOBOBJECT_H_

#include <QByteArray>

#include "NativeProxyObject.h"
#include "PropertyDelegate.h"

enum N_BLOB_PROPS {
    N_BLOB_PROP_FILE,
    N_BLOB_PROP_LENGTH,
    N_BLOB_PROP_MIMETYPE,
    N_BLOB_PROP_TEXT
};

class NativeBlobObject : public NativeProxyObject,
                         public titanium::PropertyDelegateBase<NativeBlobObject> {
public:
    static NativeBlobObject* createBlob(TiObject* object);
    NATIVE_TYPE getObjectType() const {
        return N_TYPE_BLOB;
    }

    void setData(const QByteArray& data, const QString& mimeType) {
        data_ = data;
        mimeType_ = mimeType;
    }

    int setPropertyValue(size_t propertyNumber, TiObject* obj);
    int getPropertyValue(size_t propertyNumber, TiObject* obj);

    int isFile(TiObject* value);
    int getLength(TiObject* value);
    int getMIMEType(TiObject* value);
    int getText(TiObject* value);

protected:
    virtual ~NativeBlobObject() { }

private:
    explicit NativeBlobObject(TiObject* tiObject);
    NativeBlobObject(const NativeBlobObject&);
    NativeBlobObject& operator=(const NativeBlobObject&);

    QByteArray data_;
    QString mimeType_;
};

#endif
