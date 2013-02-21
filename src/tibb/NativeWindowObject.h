/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NativeWindowObject_H_
#define NativeWindowObject_H_

#include <v8.h>

#include "NativeControlObject.h"
#include "PageScene.h"

class NativeWindowObject : public NativeControlObject {
public:
    static NativeObject* createWindow(TiObject* tiObject, NativeObjectFactory* factory);

    virtual NATIVE_TYPE getObjectType() const {
        return N_TYPE_WINDOW;
    }
    virtual int addChildNativeObject(NativeObject* obj);
    virtual void updateLayout(QRectF rect);

    virtual int setOrientationModes(TiObject* obj);

    void open();
    void close();

    void addAction(const QString& title, const QString& image, v8::Handle<v8::Function> triggerCallback);

protected:
    virtual int initialize();
    virtual void setupEvents(TiEventContainerFactory* factory);

private:
    explicit NativeWindowObject(TiObject* tiObject);

    titanium::PageScene scene_;
};

#endif
