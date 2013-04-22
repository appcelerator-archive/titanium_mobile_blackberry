/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEALERTDIALOGOBJECT_H_
#define NATIVEALERTDIALOGOBJECT_H_

#include <bb/system/SystemDialog>
#include <bb/system/SystemUiButton>
#include <v8.h>

#include "NativeControlObject.h"

class NativeAlertDialogObject : public NativeControlObject {
public:
    static NativeAlertDialogObject* createAlertDialog(TiObject* tiObject);

    virtual int initialize();
    virtual NAHANDLE getNativeHandle() const {
        return nativeDialog_;
    }
    virtual NATIVE_TYPE getObjectType() const {
        return N_TYPE_ALERTDIALOG;
    }

    virtual int show();
    virtual int hide();

    virtual int setButtonNames(TiObject* obj);
    virtual int setCancel(TiObject* obj);
    virtual int setMessage(TiObject* obj);
    virtual int setTitle(TiObject* obj);

protected:
    virtual ~NativeAlertDialogObject();
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:
    explicit NativeAlertDialogObject(TiObject* tiObject);
    // Disable copy ctor & assignment operator
    NativeAlertDialogObject(const NativeAlertDialogObject&);
    NativeAlertDialogObject& operator=(const NativeAlertDialogObject&);

    bb::system::SystemDialog* nativeDialog_;
    int cancelIndex_;
};

#endif
