/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NativeWindowObject_H_
#define NativeWindowObject_H_

#include "NativeControlObject.h"

class NativeWindowObject : public NativeControlObject {
public:
    static NativeObject* createWindow(TiObject* tiObject, NativeObjectFactory* factory);

    virtual int getObjectType() const {
        return N_TYPE_WINDOW;
    }
    virtual int addChildNativeObject(NativeObject* obj);

    void open();
    void close();

    void addAction(const QString& title);

protected:
    virtual int initialize();
    virtual void setupEvents(TiEventContainerFactory* factory);

private:
    explicit NativeWindowObject(TiObject* tiObject);
};

#endif
