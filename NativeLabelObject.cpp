/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeLabelObject.h"
#include <bb/cascades/TextAlignment>

NativeLabelObject::NativeLabelObject()
{
    label_ = NULL;
}

NativeLabelObject::~NativeLabelObject()
{
}

int NativeLabelObject::getObjectType() const
{
    return NO_TYPE_LABEL;
}

int NativeLabelObject::setText(const char* text)
{
    QString str = text;
    label_->setText(str);
    return NATIVE_ERROR_OK;
}

int NativeLabelObject::setColor(const char* color)
{
    return NATIVE_ERROR_OK;
}

int NativeLabelObject::setTextAlign(const char* align)
{
    if (strcmp(align, "left") == 0)
    {
        label_->setTextAlignment(bb::cascades::TextAlignment::ForceLeft);
    }
    else if (strcmp(align, "right") == 0)
    {
        label_->setTextAlignment(bb::cascades::TextAlignment::ForceRight);
    }
    else if (strcmp(align, "center") == 0)
    {
        label_->setTextAlignment(bb::cascades::TextAlignment::Center);
    }
    else
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    return NATIVE_ERROR_OK;
}

int NativeLabelObject::initialize()
{
    label_ = bb::cascades::Label::create();
    setControl(label_);
    return NATIVE_ERROR_OK;
}

NAHANDLE NativeLabelObject::getNativeHandle() const
{
    return label_;
}

void NativeLabelObject::completeInitialization()
{
    NativeControlObject::completeInitialization();
}
