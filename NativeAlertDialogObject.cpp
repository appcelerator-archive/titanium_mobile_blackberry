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

NativeAlertDialogObject::NativeAlertDialogObject()
{
    nativeDialog_ = NULL;
    cancelIndex_ = -1;
}

NativeAlertDialogObject::~NativeAlertDialogObject()
{
}

NativeAlertDialogObject* NativeAlertDialogObject::createAlertDialog()
{
    return new NativeAlertDialogObject();
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
    QVector<QString> buttons;
    int error = NativeControlObject::getStringArray(obj, buttons);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }

    // Omit default buttons if button names provided
    nativeDialog_->confirmButton()->setLabel(QString::null);
    nativeDialog_->cancelButton()->setLabel(QString::null);
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

int NativeAlertDialogObject::getButtonNames(TiObject* obj)
{
    int buttonsCount = nativeDialog_->buttonCount();
    Handle<Array> buttonsArray = Array::New(buttonsCount);
    for (int i = 0; i < buttonsCount; ++i)
    {
        QString str = nativeDialog_->buttonAt(i)->label();
        buttonsArray->Set(Integer::New(i), String::New(str.toStdString().c_str()));
    }
    obj->setValue(buttonsArray);
    return NATIVE_ERROR_OK;
}

int NativeAlertDialogObject::setCancel(TiObject* obj)
{
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

int NativeAlertDialogObject::getCancel(TiObject* obj)
{
    Handle<Value> cancelProperty = Number::New(cancelIndex_);
    obj->setValue(cancelProperty);
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
    NativeControlObject::setupEvents(containerFactory);
    TiEventContainer* eventClick = containerFactory->createEventContainer();
    eventClick->setDataProperty("type", tetCLICK);
    events_.insert(tetCLICK, EventPairSmartPtr(eventClick, new AlertDialogEventHandler(eventClick)));
    QObject::connect(nativeDialog_, SIGNAL(buttonSelected(bb::system::SystemUiButton*)), events_[tetCLICK]->handler, SLOT(buttonSelected(bb::system::SystemUiButton*)));
    QObject::connect(nativeDialog_, SIGNAL(accepted(void)), events_[tetCLICK]->handler, SLOT(accepted(void)));
    QObject::connect(nativeDialog_, SIGNAL(rejected(void)), events_[tetCLICK]->handler, SLOT(rejected(void)));
}
