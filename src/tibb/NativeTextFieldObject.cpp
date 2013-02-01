/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeTextFieldObject.h"

#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/TextField>
#include <bb/cascades/TextFieldInputMode>
#include <QString>

NativeTextFieldObject::NativeTextFieldObject(TiObject* tiObject)
    : NativeAbstractTextControlObject(tiObject)
    , textField_(NULL)
{
}

NativeTextFieldObject::~NativeTextFieldObject()
{
}

int NativeTextFieldObject::getObjectType() const
{
    return N_TYPE_TEXT_FIELD;
}

NativeTextFieldObject* NativeTextFieldObject::createTextField(TiObject* tiObject)
{
    return new NativeTextFieldObject(tiObject);
}

int NativeTextFieldObject::initialize()
{
    textField_ = bb::cascades::TextField::create();
    setTextControl(textField_);
    return NATIVE_ERROR_OK;
}

int NativeTextFieldObject::setHintText(TiObject* obj)
{
    QString strHint;
    int error = NativeControlObject::getString(obj, strHint);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    textField_->setHintText(strHint);
    return NATIVE_ERROR_OK;
}

int NativeTextFieldObject::setPasswordMask(TiObject* obj)
{
    bool enabled;
    getBoolean(obj, &enabled);

    if (enabled) {
        textField_->setInputMode(bb::cascades::TextFieldInputMode::Password);
    } else {
        textField_->setInputMode(bb::cascades::TextFieldInputMode::Default);
    }

    return NATIVE_ERROR_OK;
}

int NativeTextFieldObject::setValue(TiObject* obj)
{
    QString text;
    int error = NativeControlObject::getString(obj, text);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    textField_->setText(text);
    return NATIVE_ERROR_OK;
}

void NativeTextFieldObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeControlObject::setupEvents(containerFactory);
    TiEventContainer* eventFieldChanged = containerFactory->createEventContainer();
    eventFieldChanged->setDataProperty("type", tetCHANGE);
    events_.insert(tetCHANGE, EventPairSmartPtr(eventFieldChanged, new TextFieldEventHandler(eventFieldChanged, this)));
    QObject::connect(textField_, SIGNAL(textChanging(QString)), events_[tetCHANGE]->handler(), SLOT(textChanging(QString)));
}

void NativeTextFieldObject::updateValue(QString value)
{
    tiObject_->forceSetProp("value", String::New(value.toUtf8().constData()));
}
