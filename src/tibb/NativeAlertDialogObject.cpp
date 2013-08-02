/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeAlertDialogObject.h"

#include "EventHandler.h"
#include "NativeControlObject.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "V8Utils.h"

using namespace titanium;

class NativeAlertDialogEventHandler : public EventHandler {
    Q_OBJECT

public:
    explicit  NativeAlertDialogEventHandler(TiEventContainer* eventContainer)
      : EventHandler(eventContainer) { }

public slots:
    void buttonSelected(bb::system::SystemUiResult::Type) {
        bb::system::SystemDialog* dialog = static_cast<bb::system::SystemDialog*>(sender());
        bb::system::SystemUiButton* selectedButton = dialog->buttonSelection();
        if (selectedButton == NULL) {
          return;
        }

        QVariant index = selectedButton->property("index");
        QVariant cancel = selectedButton->property("cancel");
        TiEventContainer* container = getEventContainer();
        container->setDataProperty("index", index.toInt(NULL));
        container->setDataProperty("cancel", cancel.toBool());
        container->fireEvent();
    }
};

#include "NativeAlertDialogObject.moc"

NativeAlertDialogObject::NativeAlertDialogObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_ALERTDIALOG)
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

int NativeAlertDialogObject::initialize()
{
    // By default the dialog should have a single "OK" button.
    nativeDialog_ = new bb::system::SystemDialog("OK");
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

int NativeAlertDialogObject::setButtonNames(TiObject* obj)
{
    Q_ASSERT(nativeDialog_ != NULL);
    QVector<QString> buttons;
    if(obj->getValue()->IsNull())
    {
        nativeDialog_->clearButtons();
        nativeDialog_->confirmButton()->setLabel("OK");
        return NATIVE_ERROR_OK;
    }
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
    Local<Number> index = obj->getValue()->ToNumber();
    if (index.IsEmpty()) {
        return NATIVE_ERROR_INVALID_ARG;
    }

    bb::system::SystemUiButton* button = nativeDialog_->buttonAt(cancelIndex_);
    if (button) {
        button->setProperty("cancel", false);
    }

    cancelIndex_ = index->Value();
    button = nativeDialog_->buttonAt(cancelIndex_);
    if (button) {
        button->setProperty("cancel", true);
    }

    return NATIVE_ERROR_OK;
}

int NativeAlertDialogObject::setMessage(TiObject* obj)
{
	v8::Handle<v8::Value> a = obj->getValue();
	v8::Local<v8::String> b = a->ToString();
	const char *c =  *v8::String::Utf8Value(b);
    QString message = V8ValueToQString(obj->getValue());
    nativeDialog_->setBody(message);

    return NATIVE_ERROR_OK;
}

int NativeAlertDialogObject::setTitle(TiObject* obj)
{
    QString title = V8ValueToQString(obj->getValue());
    nativeDialog_->setTitle(title);

    return NATIVE_ERROR_OK;
}

void NativeAlertDialogObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeControlObject::setupEvents(containerFactory);

    TiEventContainer* eventClick = containerFactory->createEventContainer();
    eventClick->setDataProperty("type", tetCLICK);
    events_.insert(tetCLICK, EventPairSmartPtr(eventClick, new NativeAlertDialogEventHandler(eventClick)));
    QObject::connect(nativeDialog_, SIGNAL(finished(bb::system::SystemUiResult::Type)), events_[tetCLICK]->handler(), SLOT(buttonSelected(bb::system::SystemUiResult::Type)));
}

