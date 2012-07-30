/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEALERTDIALOGOBJECT_H_
#define NATIVEALERTDIALOGOBJECT_H_

#include "NativeProxyObject.h"
#include <bps/dialog.h>

/*
 * NativeAlertDialogObject
 *
 * UI: Alert Dialog
 */

class NativeAlertDialogObject : public NativeProxyObject
{
public:
    static NativeAlertDialogObject* createAlertDialog();
    virtual int getObjectType() const;
    virtual int initialize();
    virtual NAHANDLE getNativeHandle() const;
    virtual int show();
    virtual int hide();
    virtual int setTitle(TiObject* obj);
    virtual int setMessage(TiObject* obj);

protected:
    virtual ~NativeAlertDialogObject();

private:
    NativeAlertDialogObject();
    // Disable copy ctor & assignment operator
    NativeAlertDialogObject(const NativeAlertDialogObject& alertDialog);
    NativeAlertDialogObject& operator=(const NativeAlertDialogObject& alertDialog);
    dialog_instance_t nativeDialog_;
    QString alertMessage_;
    QString alertTitle_;
};


#endif /* NATIVEALERTDIALOGOBJECT_H_ */
