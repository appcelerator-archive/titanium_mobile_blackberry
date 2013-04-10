/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_UI_CLIPBOARD_H
#define TI_UI_CLIPBOARD_H

#include "TiProxy.h"

class TiUIClipboardObject: public TiProxy {
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* factory);

protected:
    virtual ~TiUIClipboardObject();
    virtual void onCreateStaticMembers();

private:
    TiUIClipboardObject();

    Handle<Value> clipboardData(const QString& type) const;

    static Handle<Value> _getData(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _getText(void* userContext, TiObject* caller, const Arguments& args);
};

#endif
