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

namespace bb
{
namespace cascades
{
class Sheet;
}
}
class NativeWindowObject : public NativeControlObject {
public:
    static NativeObject* createWindow(TiObject* tiObject, NativeObjectFactory* factory);

    virtual NATIVE_TYPE getObjectType() const {
        return N_TYPE_WINDOW;
    }
    virtual int addChildNativeObject(NativeObject* obj);
    virtual void updateLayout(QRectF rect);

    virtual int setOrientationModes(TiObject* obj);
    virtual int setTitle(TiObject* obj);

    void open(bool);
    void close();

    void addAction(const QString& title, const QString& image, v8::Handle<v8::Function> triggerCallback);
//    titanium::PageScene getScene();
    titanium::PageScene scene_;

protected:
    virtual int initialize();
    virtual void setupEvents(TiEventContainerFactory* factory);

private:
    explicit NativeWindowObject(TiObject* tiObject);

    bb::cascades::Sheet* modalSheet_;
    QString title_;
};

#endif
