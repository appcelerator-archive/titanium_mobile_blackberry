/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeLabelObject.h"
#include <bb/cascades/TextAlignment>
#include <bb/cascades/Color>
#include <qtgui/QColor>

NativeLabelObject::NativeLabelObject()
{
    label_ = NULL;
}

NativeLabelObject::~NativeLabelObject()
{
}

NativeLabelObject* NativeLabelObject::createLabel()
{
    return new NativeLabelObject;
}

int NativeLabelObject::getObjectType() const
{
    return N_TYPE_LABEL;
}

int NativeLabelObject::setText(TiObject* obj)
{
    QString str;
    int error = NativeControlObject::getString(obj, str);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    label_->setText(str);
    return NATIVE_ERROR_OK;
}

int NativeLabelObject::setColor(TiObject* obj)
{
    float r;
    float g;
    float b;
    float a;

    int error = NativeControlObject::getColorComponents(obj, &r, &g, &b, &a);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    bb::cascades::Color cscolor = bb::cascades::Color::fromRGBA(r, g, b, a);
    // TODO: setTextColor is not yet supported by Cascades. When it becomes
    // available, un-comment out the next line.
    //label_->setTextColor(cscolor);
    return NATIVE_ERROR_OK;
}

int NativeLabelObject::setTextAlign(TiObject* obj)
{
    // TODO: finish
    return NATIVE_ERROR_OK;
}

int NativeLabelObject::initialize(TiEventContainerFactory*)
{
    label_ = bb::cascades::Label::create();
    setControl(label_);
    // TODO: Set label layout here
    return NATIVE_ERROR_OK;
}
