/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIOPTIONDIALOG_H_
#define TIUIOPTIONDIALOG_H_

#include "TiUIBase.h"

/*
 * TiUIOptionDialog
 *
 * Represents a Titanium option dialog object
 *
 */
class TiUIOptionDialog : public TiUIBase
{
public:
    static TiUIOptionDialog* createOptionDialog(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUIOptionDialog();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();

private:
    explicit TiUIOptionDialog(NativeObjectFactory* nativeObjectFactory);
    static Handle<Value> show_(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> hide_(void* userContext, TiObject* caller, const Arguments& args);
    // Disable copy ctor & assignment operator
    TiUIOptionDialog(const TiUIOptionDialog& optionDialog);
    TiUIOptionDialog& operator=(const TiUIOptionDialog& optionDialog);
};

#endif /* TIUIOPTIONDIALOG_H_ */
