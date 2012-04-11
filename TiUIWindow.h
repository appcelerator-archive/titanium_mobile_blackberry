/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIWINDOW_H_
#define TIUIWINDOW_H_

#include "TiUIBase.h"

/*
 * Represents a Titanium window object
 *
 * This object can be created by:
 * Titanium.UI.createWindow({...});
 */
class TiUIWindow : public TiUIBase
{
public:
    static TiUIWindow* createWindow(NativeObjectFactory* objectFactory, const char* name);
protected:
    virtual ~TiUIWindow();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();
private:
    TiUIWindow(NativeObjectFactory* objectFactory, const char* name);
    static Handle<Value> open_(void* userContext, TiObject* caller, const Arguments& args);
};

#endif /* TIUIWINDOW_H_ */
