/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVELISTITEMOBJECT_H_
#define NATIVELISTITEMOBJECT_H_

#include "NativeControlObject.h"

#include <QVariant>

class TiObject;

class NativeListItemObject : public NativeControlObject {
public:
    NativeListItemObject(TiObject* object);
    virtual ~NativeListItemObject();

    virtual int getObjectType() const {
        return N_TYPE_LIST_ITEM;
    }

    virtual int setLeftImage(TiObject* obj);
    virtual int setTitle(TiObject* obj);

    QVariant data() const {
        return QVariant::fromValue(data_);
    }

private:
    QObject* data_;
};

#endif
