/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIOPTIONDIALOG_H_
#define TIUIOPTIONDIALOG_H_

#include "TiProxy.h"

/*
 * TiUIOptionDialog
 *
 * Represents a Titanium option dialog object
 *
 */
class TiUIOptionDialog : public TiProxy
{
public:
    static TiUIOptionDialog* createOptionDialog(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUIOptionDialog();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();

private:
    explicit TiUIOptionDialog();
    static Handle<Value> _show(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _hide(void* userContext, TiObject* caller, const Arguments& args);
    // Disable copy ctor & assignment operator
    TiUIOptionDialog(const TiUIOptionDialog& optionDialog);
    TiUIOptionDialog& operator=(const TiUIOptionDialog& optionDialog);

    static void _setCancel(void* userContext, Handle<Value> arg);
    static void _setSelectedIndex(void* userContext, Handle<Value> arg);
    static void _setDestructive(void* userContext, Handle<Value> arg);
    static void _setTitle(void* userContext, Handle<Value> arg);
    static void _setOptions(void* userContext, Handle<Value> arg);

};

#endif /* TIUIOPTIONDIALOG_H_ */
