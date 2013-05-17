/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIBLOBOBJECT_H_
#define TIBLOBOBJECT_H_

#include "TiProxy.h"

#include <QByteArray>

class TiBlobObject : public TiProxy
{
public:
    static TiBlobObject* createBlob(NativeObjectFactory* objectFactory);

    void setData(const QByteArray& data, const QString& mimeType);
    QByteArray data() const;
    QString mimeType() const;

protected:
    virtual ~TiBlobObject();
    virtual void onCreateStaticMembers();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiBlobObject();
    TiBlobObject(const TiBlobObject&);
    TiBlobObject& operator=(const TiBlobObject&);
};

#endif TIBLOBOBJECT_H_
