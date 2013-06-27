/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVETABLEVIEWROWOBJECT_H_
#define NATIVETABLEVIEWROWOBJECT_H_

#include "NativeControlObject.h"

#include <QScopedPointer>
#include <QVariant>

class TableViewRowData;
class TiObject;

class NativeTableViewRowObject : public NativeControlObject {
public:
    NativeTableViewRowObject(TiObject* object);
    virtual ~NativeTableViewRowObject();

    virtual NATIVE_TYPE getObjectType() const {
        return N_TYPE_TABLE_VIEW_ROW;
    }

    virtual int addChildNativeObject(NativeObject* obj);

    virtual int setLeftImage(TiObject* obj);
    virtual int setTitle(TiObject* obj);
    virtual int setHeader(TiObject* obj);
    virtual int setSubHeader(TiObject* obj);
    void removeHeader();
    QVariant data() const;

private:
    QScopedPointer<TableViewRowData> data_;
};

#endif
