/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIALERTDIALOG_H_
#define TIUIALERTDIALOG_H_

#include "TiUIBase.h"

/*
 * TiUIAlertDialog
 *
 * Represents a Titanium alert dialog object
 *
 */

class TiUIAlertDialog : public TiUIBase
{
public:
    static TiUIAlertDialog* createAlertDialog(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUIAlertDialog();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();

private:
    TiUIAlertDialog();
    static Handle<Value> show_(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> hide_(void* userContext, TiObject* caller, const Arguments& args);
    // Disable copy ctor & assignment operator
    TiUIAlertDialog(const TiUIAlertDialog& alertDialog);
    TiUIAlertDialog& operator=(const TiUIAlertDialog& alertDialog);
};


#endif /* TIUIALERTDIALOG_H_ */
