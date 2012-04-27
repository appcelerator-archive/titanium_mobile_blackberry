/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeLabelObject.h"
#include <bb/cascades/TextAlignment>
#include <bb/cascades/SystemFont>
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

int NativeLabelObject::setText(const char* text)
{
    QString str = text;
    label_->setText(str);
    return NATIVE_ERROR_OK;
}

int NativeLabelObject::setColor(const char* colortext)
{
    QString colorString = colortext;
    QColor color;
    color.setNamedColor(colorString);
    qreal r, g, b, a;
    color.getRgbF(&r, &g, &b, &a);
    bb::cascades::Color cscolor = bb::cascades::Color::fromRGBA(r, g, b, a);
    // TODO: setTextColor is not yet supported by Cascades. When it becomes
    // available, un-comment out the next line.
    //label_->setTextColor(cscolor);
    return NATIVE_ERROR_OK;
}

int NativeLabelObject::setTextAlign(const char* align)
{
    if (stricmp(align, "left") == 0)
    {
        label_->setTextAlignment(bb::cascades::TextAlignment::ForceLeft);
    }
    else if (stricmp(align, "right") == 0)
    {
        label_->setTextAlignment(bb::cascades::TextAlignment::ForceRight);
    }
    else if (stricmp(align, "center") == 0)
    {
        label_->setTextAlignment(bb::cascades::TextAlignment::Center);
    }
    else
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    return NATIVE_ERROR_OK;
}

int NativeLabelObject::initialize(TiEventContainerFactory*)
{
    label_ = bb::cascades::Label::create();
    setControl(label_);
    label_->setFont(bb::cascades::SystemFont::getFont(bb::cascades::SystemFont::H1));
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
