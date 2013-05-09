/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIOBJECT_H_
#define TIUIOBJECT_H_

#include "TiProxy.h"

typedef TiProxy* (*CREATEOBJECTCALLBACK)(NativeObjectFactory*);

/*
 * TiUIObject
 *
 * Titanium.UI namespace
 */
class TiUIObject : public TiProxy
{
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);

protected:
    virtual ~TiUIObject();
    virtual void onCreateStaticMembers();

private:
    TiUIObject();
    TiUIObject(NativeObjectFactory* objectFactory);
    static Handle<Value> _createControlHelper(void* userContext, CREATEOBJECTCALLBACK createCallback, const Arguments& args);
    static Handle<Value> _createTabGroup(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createWindow(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createLabel(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createButton(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createSlider(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createProgressBar(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createImageView(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createTextField(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createTextArea(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createActivityIndicator(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createTab(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createSwitch(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createOptionDialog(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createTableView(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createTableViewRow(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createPicker(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createAlertDialog(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createView(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createWebView(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _createScrollView(void* userContext, TiObject*, const Arguments& args);
    static Handle<Value> _createScrollableView(void* userContext, TiObject*, const Arguments& args);

    static Handle<Value> _setBackgroundColor(void* userContext, TiObject* caller, const Arguments& args);

    NativeObjectFactory* objectFactory_;
    NativeObject* contentContainer_;
};

#endif /* TIUIOBJECT_H_ */
