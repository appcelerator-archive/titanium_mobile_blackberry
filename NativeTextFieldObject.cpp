/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeTextFieldObject.h"
#include "TiEventContainerFactory.h"
#include "TiCascadesEventHandler.h"
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/textField>
#include <QtCore/QString>

NativeTextFieldObject::NativeTextFieldObject()
{
    textField_ = NULL;
    left_ = 0;
    top_ = 0;
}

NativeTextFieldObject::~NativeTextFieldObject()
{
}

int NativeTextFieldObject::getObjectType() const
{
    return N_TYPE_TEXT_FIELD;
}

NativeTextFieldObject* NativeTextFieldObject::createTextField()
{
    return new NativeTextFieldObject;
}

int NativeTextFieldObject::initialize(TiEventContainerFactory* containerFactory)
{
    textField_ = bb::cascades::TextField::create();
    setControl(textField_);
    eventFieldChanged_ = containerFactory->createEventContainer();
    eventFieldChanged_->setDataProperty("type", "change");
    eventHandler_ = new TiCascadesEventHandler(eventFieldChanged_);
    return NATIVE_ERROR_OK;
}

int NativeTextFieldObject::setWidth(float width)
{
    textField_->setMaxWidth(width);
    textField_->setMinWidth(width);
    return NATIVE_ERROR_OK;
}

int NativeTextFieldObject::setHeight(float height)
{
    textField_->setMaxHeight(height);
    textField_->setMinHeight(height);
    return NATIVE_ERROR_OK;
}

int NativeTextFieldObject::setLeft(float left)
{
    bb::cascades::AbsoluteLayoutProperties* pProp = new bb::cascades::AbsoluteLayoutProperties;
    left_ = left;
    pProp->setPositionX(left_);
    pProp->setPositionY(top_);
    textField_->setLayoutProperties(pProp);

    return NATIVE_ERROR_OK;
}

int NativeTextFieldObject::setTop(float top)
{
    bb::cascades::AbsoluteLayoutProperties* pProp = new bb::cascades::AbsoluteLayoutProperties;
    top_ = top;
    pProp->setPositionY(top_);
    pProp->setPositionX(left_);
    textField_->setLayoutProperties(pProp);

    return NATIVE_ERROR_OK;
}

int NativeTextFieldObject::setHintText(const char* hintText)
{
    textField_->setHintText(hintText);
    return NATIVE_ERROR_OK;
}

NAHANDLE NativeTextFieldObject::getNativeHandle() const
{
    return textField_;
}

void NativeTextFieldObject::completeInitialization()
{
    NativeControlObject::completeInitialization();
    QObject::connect(textField_, SIGNAL(textChanging(QString)), eventHandler_, SLOT(textChanging(QString)));
}

int NativeTextFieldObject::setEventHandler(const char* eventName, TiEvent* event)
{
    if (strcmp(eventName, "change") == 0)
    {
        eventFieldChanged_->addListener(event);
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}
