/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeAlertDialogObject.h"

#include "NativeControlObject.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"

NativeAlertDialogObject::NativeAlertDialogObject(TiObject* tiObject)
    : NativeControlObject(tiObject)
    , nativeDialog_(NULL)
    , cancelIndex_(-1)
{
}

NativeAlertDialogObject::~NativeAlertDialogObject()
{
}

NativeAlertDialogObject* NativeAlertDialogObject::createAlertDialog(TiObject* tiObject)
{
    return new NativeAlertDialogObject(tiObject);
}

int NativeAlertDialogObject::getObjectType() const
{
    return N_TYPE_ALERTDIALOG;
}

int NativeAlertDialogObject::initialize()
{
    nativeDialog_ = new bb::system::SystemDialog();
    return NATIVE_ERROR_OK;
}

int NativeAlertDialogObject::setTitle(TiObject* obj)
{
    Q_ASSERT(nativeDialog_ != NULL);
    QString title;
    int error = NativeControlObject::getString(obj, title);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    nativeDialog_->setTitle(title);
    return NATIVE_ERROR_OK;
}

int NativeAlertDialogObject::setMessage(TiObject* obj)
{
    Q_ASSERT(nativeDialog_ != NULL);
    QString message;
    int error = NativeControlObject::getString(obj, message);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    nativeDialog_->setBody(message);
    return NATIVE_ERROR_OK;
}

int NativeAlertDialogObject::setButtonNames(TiObject* obj)
{
    Q_ASSERT(nativeDialog_ != NULL);
    QVector<QString> buttons;
    int error = NativeControlObject::getStringArray(obj, buttons);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }

    // Omit default buttons if button names provided
    nativeDialog_->confirmButton()->setLabel(QString::null);
    nativeDialog_->cancelButton()->setLabel(QString::null);
    // Clear possibly existed buttons
    nativeDialog_->clearButtons();
    for (int i = 0; i < buttons.size(); ++i)
    {
        bb::system::SystemUiButton* button = new bb::system::SystemUiButton();
        button->setLabel(buttons[i]);
        button->setProperty("index", QVariant::fromValue(i));
        button->setProperty("cancel", QVariant::fromValue(cancelIndex_ != -1 && cancelIndex_ == i));
        nativeDialog_->appendButton(button);
    }
    return NATIVE_ERROR_OK;
}

int NativeAlertDialogObject::setCancel(TiObject* obj)
{
    Q_ASSERT(nativeDialog_ != NULL);
    int error = NativeControlObject::getInteger(obj, &cancelIndex_);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    bb::system::SystemUiButton* button = nativeDialog_->buttonAt(cancelIndex_);
    if (button)
    {
        button->setProperty("cancel", QVariant::fromValue(true));
    }
    return NATIVE_ERROR_OK;
}

int NativeAlertDialogObject::show()
{
    nativeDialog_->show();
    return NATIVE_ERROR_OK;
}

int NativeAlertDialogObject::hide()
{
    nativeDialog_->cancel();
    return NATIVE_ERROR_OK;
}

NAHANDLE NativeAlertDialogObject::getNativeHandle() const
{
    return nativeDialog_;
}

void NativeAlertDialogObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    TiEventContainer* eventClick = containerFactory->createEventContainer();
    eventClick->setDataProperty("type", tetCLICK);
    events_.insert(tetCLICK, EventPairSmartPtr(eventClick, new AlertDialogEventHandler(eventClick)));
    QObject::connect(nativeDialog_, SIGNAL(finished(bb::system::SystemUiResult::Type)), events_[tetCLICK]->handler(), SLOT(buttonSelected(bb::system::SystemUiResult::Type)));
}
