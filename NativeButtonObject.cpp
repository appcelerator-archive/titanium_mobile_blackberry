/*
 * NativeButtonObject.cpp
 *
 *  Created on: 2012-04-17
 *      Author: dcampbell
 */

#include "NativeButtonObject.h"

NativeButtonObject::NativeButtonObject()
{
    button_=NULL;
}

NativeButtonObject::~NativeButtonObject()
{
}

int NativeButtonObject::getObjectType() const
{
    return NO_TYPE_BUTTON;
}

int NativeButtonObject::initialize()
{
    button_=bb::cascades::Button::create();
    setControl(button_);
    return NATIVE_ERROR_OK;
}

NAHANDLE NativeButtonObject::getNativeHandle() const
{
    return button_;
}

int NativeButtonObject::setLabel(const char* text)
{
    QString str = text;
    button_->setText(str);
    return NATIVE_ERROR_OK;
}
