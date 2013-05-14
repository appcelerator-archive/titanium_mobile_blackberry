/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIEMAILDIALOG_
#define TIUIEMAILDIALOG_

#include "TiUIBase.h"

/*
 * TiUIEmailDialog
 *
 * Represents a Titanium imageView object
 *
 * This object can be created by:
 * Titanium.UI.createImageView({...});
 */
class TiUIEmailDialog : public TiUIBase
{
public:
    static TiUIEmailDialog* createEmailDialog(NativeObjectFactory* nativeObjectFactory);


protected:
    virtual ~TiUIEmailDialog();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiUIEmailDialog();
    virtual void onCreateStaticMembers();
    static Handle<Value> _open(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _addAttachment(void* userContext, TiObject* caller, const Arguments& args);

};


#endif /* TIUIEMAILDIALOG_ */


