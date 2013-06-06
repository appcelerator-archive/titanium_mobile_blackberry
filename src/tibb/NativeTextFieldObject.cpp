/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeTextFieldObject.h"

#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/TextField>
#include <bb/cascades/TextFieldInputMode>
#include <QString>

#include "KeyboardType.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "V8Utils.h"

using namespace bb::cascades;
using namespace titanium;

NativeTextFieldObject::NativeTextFieldObject(TiObject* tiObject)
    : NativeAbstractTextControlObject(tiObject, N_TYPE_TEXT_FIELD)
    , textField_(NULL)
{
}

NativeTextFieldObject::~NativeTextFieldObject()
{
}

NATIVE_TYPE NativeTextFieldObject::getObjectType() const
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

int NativeTextFieldObject::setBackgroundColor(TiObject* obj)
{
	NativeAbstractTextControlObject::setBackgroundColor(obj);
    Handle<Value> value = obj->getValue();
    if(value->IsNull()) {
    	textField_->setBackgroundVisible(true);
    } else {
    	textField_->setBackgroundVisible(false);
    }
}
int NativeTextFieldObject::setHintText(TiObject* obj)
{
    QString strHint = V8ValueToQString(obj->getValue());
    textField_->setHintText(strHint);
    return NATIVE_ERROR_OK;
}

int NativeTextFieldObject::setKeyboardType(TiObject* obj)
{
    Handle<Value> value = obj->getValue();
    if (!value->IsNumber()) {
        return NATIVE_ERROR_INVALID_ARG;
    }

    TextFieldInputMode::Type type;
    switch (value->Int32Value()) {
        case KeyboardType::DEFAULT:
            type = TextFieldInputMode::Default;
            break;
        case KeyboardType::ASCII:
            type = TextFieldInputMode::Text;
            break;
        case KeyboardType::EMAIL:
            type = TextFieldInputMode::EmailAddress;
            break;
        case KeyboardType::NUMBERS_PUNCTUATION:
            type = TextFieldInputMode::NumbersAndPunctuation;
            break;
        case KeyboardType::NAMEPHONE_PAD:
        case KeyboardType::PHONE_PAD:
            type = TextFieldInputMode::PhoneNumber;
            break;
        case KeyboardType::URL:
            type = TextFieldInputMode::Url;
            break;
        default:
            // Ignore any constants not supported.
            return NATIVE_ERROR_OK;
    }

    fprintf(stderr, "type = %i\n", type);
    textField_->setInputMode(type);
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
    QString text = V8ValueToQString(obj->getValue());
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
