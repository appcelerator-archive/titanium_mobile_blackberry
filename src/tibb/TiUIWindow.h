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
 * TiUIWindow
 *
 * Represents a Titanium window object
 *
 * This object can be created by:
 * Titanium.UI.createWindow({...});
 */
class TiUIWindow : public TiUIBase
{
public:
    static TiUIWindow* createWindow(NativeObjectFactory* objectFactory);

protected:
    virtual ~TiUIWindow();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();
    bool isModal;

private:
	TiUIWindow();
	static Handle<Value> _getModal(void* userContext);
	static void _setModal(void* userContext, Handle<Value> value);
    static Handle<Value> _open(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _close(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _addAction(void* userContext, TiObject* caller, const Arguments& args);
	static Handle<Value> _getLeftNavButton(void* userContext);
	static void _setLeftNavButton(void* userContext, Handle<Value> value);
	static Handle<Value> _getRightNavButton(void* userContext);
	static void _setRightNavButton(void* userContext, Handle<Value> value);

};

#endif /* TIUIWINDOW_H_ */
