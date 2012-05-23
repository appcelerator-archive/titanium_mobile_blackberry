/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeAbstractTextControlObject.h"
#include <bb/cascades/controls/abstracttextcontrol.h>
#include <bb/cascades/controls/textalignment.h>
#include <qt4/QtCore/qmap.h>
#include <qt4/QtCore/qstring.h>

NativeAbstractTextControlObject::NativeAbstractTextControlObject()
{
    textControl_ = NULL;
}

NativeAbstractTextControlObject::~NativeAbstractTextControlObject()
{
}

bb::cascades::AbstractTextControl* NativeAbstractTextControlObject::getTextControl() const
{
    return textControl_;
}

void NativeAbstractTextControlObject::setTextControl(bb::cascades::AbstractTextControl* textControl)
{
    textControl_ = textControl;
    setControl((bb::cascades::Control*)textControl_);
}

int NativeAbstractTextControlObject::setText(TiObject* obj)
{
    QString str;
    int error = NativeControlObject::getString(obj, str);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    textControl_->setText(str);
    return NATIVE_ERROR_OK;
}

int NativeAbstractTextControlObject::setColor(TiObject* obj)
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
    textControl_->textStyle()->setColor(cscolor);
    return NATIVE_ERROR_OK;
}

int NativeAbstractTextControlObject::setTextAlign(TiObject* obj)
{
    int value;
    int error = NativeControlObject::getInteger(obj, &value);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }

    switch (value)
    {
    case 0: // TEXT_ALIGNMENT_LEFT
        textControl_->textStyle()->setAlignment(bb::cascades::TextAlignment::ForceLeft);
        break;
    case 1: // TEXT_ALIGNMENT_CENTER
        textControl_->textStyle()->setAlignment(bb::cascades::TextAlignment::Center);
        break;
    case 2: // TEXT_ALIGNMENT_RIGHT
        textControl_->textStyle()->setAlignment(bb::cascades::TextAlignment::ForceRight);
        break;
    default:
        textControl_->textStyle()->setAlignment(bb::cascades::TextAlignment::Default);
        break;
    }

    return NATIVE_ERROR_OK;
}

int NativeAbstractTextControlObject::setFont(TiObject* obj)
{
    QMap<QString, QString> font;
    int error = NativeControlObject::getFontObject(obj, font);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }

    QMap<QString, QString>::const_iterator it = font.begin();
    for (; it != font.end(); ++it)
    {
        if (it.key().compare("fontFamily") == 0)
        {
            textControl_->textStyle()->setFontFamily(it.value());
        }
        else if (it.key().compare("fontSize") == 0)
        {
            bool bSucceed;
            float size = it.value().toFloat(&bSucceed);
            if (bSucceed)
            {
                textControl_->textStyle()->setSize(size);
            }
        }
        else if (it.key().compare("fontStyle") == 0)
        {
            if (it.value().compare("normal") == 0)
            {
                textControl_->textStyle()->setFontStyle(bb::cascades::FontStyle::Normal);
            }
            else if (it.value().compare("italic") == 0)
            {
                textControl_->textStyle()->setFontStyle(bb::cascades::FontStyle::Italic);
            }
            else
            {
                textControl_->textStyle()->setFontStyle(bb::cascades::FontStyle::Default);
            }
        }
        else if (it.key().compare("fontWeight") == 0)
        {
            if (it.value().compare("normal") == 0)
            {
                textControl_->textStyle()->setFontWeight(bb::cascades::FontWeight::Normal);
            }
            else if (it.value().compare("bold") == 0)
            {
                textControl_->textStyle()->setFontWeight(bb::cascades::FontWeight::Bold);
            }
            else
            {
                textControl_->textStyle()->setFontWeight(bb::cascades::FontWeight::Default);
            }
        }
    }

    return NATIVE_ERROR_OK;
}
