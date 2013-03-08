/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeTextAreaObject.h"

#include "KeyboardType.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/TextArea>
#include <bb/cascades/TextAreaInputMode>
#include <QString>

using namespace bb::cascades;
using namespace titanium;

NativeTextAreaObject::NativeTextAreaObject(TiObject* tiObject)
    : NativeAbstractTextControlObject(tiObject, N_TYPE_TEXT_AREA)
    , textArea_(NULL)
{
}

NativeTextAreaObject::~NativeTextAreaObject()
{
}

NATIVE_TYPE NativeTextAreaObject::getObjectType() const
{
    return N_TYPE_TEXT_AREA;
}

NativeTextAreaObject* NativeTextAreaObject::createTextArea(TiObject* tiObject)
{
    return new NativeTextAreaObject(tiObject);
}

int NativeTextAreaObject::initialize()
{
    textArea_ = bb::cascades::TextArea::create();
    setTextControl(textArea_);
    return NATIVE_ERROR_OK;
}

int NativeTextAreaObject::setHintText(TiObject* obj)
{
    QString strHint;
    int error = NativeControlObject::getString(obj, strHint);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    textArea_->setHintText(strHint);
    return NATIVE_ERROR_OK;
}

int NativeTextAreaObject::setKeyboardType(TiObject* obj)
{
    Handle<Value> value = obj->getValue();
    if (!value->IsNumber()) {
        return NATIVE_ERROR_INVALID_ARG;
    }

    TextAreaInputMode::Type type;
    switch (value->Int32Value()) {
        case KeyboardType::DEFAULT:
            type = TextAreaInputMode::Default;
            break;
        case KeyboardType::ASCII:
            type = TextAreaInputMode::Text;
            break;
        case KeyboardType::EMAIL:
            type = TextAreaInputMode::EmailAddress;
            break;
        /*
        case KeyboardType::NUMBERS_PUNCTUATION:
            type = TextAreaInputMode::NumbersAndPunctuation;
            break;
        case KeyboardType::NAMEPHONE_PAD:
        case KeyboardType::PHONE_PAD:
            type = TextAreaInputMode::PhoneNumber;
            break;
        case KeyboardType::URL:
            type = TextAreaInputMode::Url;
            break;
        */
        default:
            // Ignore any constants not supported.
            return NATIVE_ERROR_OK;
    }

    fprintf(stderr, "type = %i\n", type);
    textArea_->setInputMode(type);
    return NATIVE_ERROR_OK;
}

int NativeTextAreaObject::setPasswordMask(TiObject* obj)
{
    bool enabled;
    getBoolean(obj, &enabled);

    /*
    if (enabled) {
        textArea_->setInputMode(bb::cascades::TextAreaInputMode::Password);
    } else {
        textArea_->setInputMode(bb::cascades::TextAreaInputMode::Default);
    }
    */

    return NATIVE_ERROR_OK;
}

int NativeTextAreaObject::setValue(TiObject* obj)
{
    QString text;
    int error = NativeControlObject::getString(obj, text);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    textArea_->setText(text);
    return NATIVE_ERROR_OK;
}

void NativeTextAreaObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeControlObject::setupEvents(containerFactory);
    TiEventContainer* eventAreaChanged = containerFactory->createEventContainer();
    eventAreaChanged->setDataProperty("type", tetCHANGE);
    events_.insert(tetCHANGE, EventPairSmartPtr(eventAreaChanged, new TextAreaEventHandler(eventAreaChanged, this)));
    QObject::connect(textArea_, SIGNAL(textChanging(QString)), events_[tetCHANGE]->handler(), SLOT(textChanging(QString)));
}

void NativeTextAreaObject::updateValue(QString value)
{
    tiObject_->forceSetProp("value", String::New(value.toUtf8().constData()));
}
