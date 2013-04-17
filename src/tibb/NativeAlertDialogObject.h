/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEALERTDIALOGOBJECT_H_
#define NATIVEALERTDIALOGOBJECT_H_

#include "NativeControlObject.h"
#include <bb/system/SystemDialog>
#include <bb/system/SystemUiButton>

#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <v8.h>
#pragma GCC diagnostic warning "-Wunused-parameter"

using namespace v8;

/*
 * NativeAlertDialogObject
 *
 * UI: Alert Dialog
 */

class NativeAlertDialogObject : public NativeControlObject
{
public:
    static NativeAlertDialogObject* createAlertDialog(TiObject* tiObject);
    virtual NATIVE_TYPE getObjectType() const;
    virtual int initialize();
    virtual NAHANDLE getNativeHandle() const;
    virtual int show();
    virtual int hide();
    virtual int setTitle(TiObject* obj);
    virtual int setMessage(TiObject* obj);
    virtual int setButtonNames(TiObject* obj);
    virtual int setCancel(TiObject* obj);

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

//Event handler for alert dialog object
class NativeAlertDialogEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit  NativeAlertDialogEventHandler(TiEventContainer* eventContainer);
    virtual ~NativeAlertDialogEventHandler();

public slots:
    void buttonSelected(bb::system::SystemUiResult::Type);


private:
    TiEventContainer* eventContainer_;

    // Disable copy ctor & assignment operator
    NativeAlertDialogEventHandler(const  NativeAlertDialogEventHandler&);
    NativeAlertDialogEventHandler& operator=(const  NativeAlertDialogEventHandler&);
};


//#include <QObjectUserData>

#endif /* NATIVEALERTDIALOGOBJECT_H_ */
