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
    virtual int getObjectType() const;
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
class AlertDialogEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit AlertDialogEventHandler(TiEventContainer* eventContainer)
    {
        eventContainer_ = eventContainer;
    }
    virtual ~AlertDialogEventHandler() {}

public slots:
    void buttonSelected(bb::system::SystemUiResult::Type type)
    {
        bb::system::SystemDialog* dialog = static_cast<bb::system::SystemDialog*>(sender());
        bb::system::SystemUiButton* selectedButton = dialog->buttonSelection();
        if (selectedButton == NULL) {
            return;
        }

        QVariant index = selectedButton->property("index");
        QVariant cancel = selectedButton->property("cancel");
        eventContainer_->setDataProperty("index", index.toInt(NULL));
        eventContainer_->setDataProperty("cancel", cancel.toBool());
        eventContainer_->fireEvent();
    }

private:
    TiEventContainer* eventContainer_;

    // Disable copy ctor & assignment operator
    AlertDialogEventHandler(const AlertDialogEventHandler&);
    AlertDialogEventHandler& operator=(const AlertDialogEventHandler&);
};
#include <QObjectUserData>

#endif /* NATIVEALERTDIALOGOBJECT_H_ */
