/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeAbstractTextControlObject.h"

#include <bb/cascades/AbstractTextControl>
#include <bb/cascades/FontSize>
#include <QMap>
#include <QString>

#include "NativeLoggerObject.h"
#include "NativeMessageStrings.h"
#include "TiConstants.h"
#include "TiObject.h"
#include "V8Utils.h"

using namespace titanium;

static const char* FONT_FAMILY            = "fontFamily";
static const char* FONT_SIZE              = "fontSize";
static const char* FONT_STYLE             = "fontStyle";
static const char* FONT_STYLE_NORMAL      = "normal";
static const char* FONT_STYLE_ITALIC      = "italic";
static const char* FONT_WEIGHT            = "fontWeight";
static const char* FONT_WEIGHT_NORMAL     = "normal";
static const char* FONT_WEIGHT_BOLD       = "bold";

NativeAbstractTextControlObject::NativeAbstractTextControlObject(TiObject* tiObject,  NATIVE_TYPE objType)
    : NativeControlObject(tiObject, objType)
    , textControl_(NULL)
{
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
    QString text = V8ValueToQString(obj->getValue());
    textControl_->setText(text);
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
    Handle<Value> value = obj->getValue();
    int alignment;

    if (!value->IsNumber()) {
        QString s = V8ValueToQString(value);
        if (s == "left") {
            alignment = Ti::UI::TEXT_ALIGNMENT_LEFT;
        } else if (s == "center") {
            alignment = Ti::UI::TEXT_ALIGNMENT_CENTER;
        } else if (s == "right") {
            alignment = Ti::UI::TEXT_ALIGNMENT_RIGHT;
        } else {
            return NATIVE_ERROR_INVALID_ARG;
        }
    } else {
        alignment = value->IntegerValue();
    }

    switch (alignment)
    {
    case Ti::UI::TEXT_ALIGNMENT_LEFT:
        textControl_->textStyle()->setTextAlign(bb::cascades::TextAlign::Left);
        break;
    case Ti::UI::TEXT_ALIGNMENT_CENTER:
        textControl_->textStyle()->setTextAlign(bb::cascades::TextAlign::Center);
        break;
    case Ti::UI::TEXT_ALIGNMENT_RIGHT:
        textControl_->textStyle()->setTextAlign(bb::cascades::TextAlign::Right);
        break;
    default:
        return NATIVE_ERROR_INVALID_ARG;
    }

    return NATIVE_ERROR_OK;
}

int NativeAbstractTextControlObject::setFont(TiObject* obj)
{
    QMap<QString, QString> font;
    int error = NativeControlObject::getMapObject(obj, font);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }

    QMap<QString, QString>::const_iterator it = font.begin();
    for (; it != font.end(); ++it)
    {
        if (it.key().compare(FONT_FAMILY) == 0)
        {
            textControl_->textStyle()->setFontFamily(it.value());
        }
        else if (it.key().compare(FONT_SIZE) == 0)
        {
            bool bSucceeded;
            float size = it.value().toFloat(&bSucceeded);
            if (bSucceeded)
            {
                textControl_->textStyle()->setFontSize(bb::cascades::FontSize::PointValue);
                textControl_->textStyle()->setFontSizeValue(size);
            }
            else
            {
                N_DEBUG(Native::Msg::Failed_to_convert_font_size_to_float_with_value << ": " << it.value());
            }
        }
        else if (it.key().compare(FONT_STYLE) == 0)
        {
            if (it.value().compare(FONT_STYLE_NORMAL) == 0)
            {
                textControl_->textStyle()->setFontStyle(bb::cascades::FontStyle::Normal);
            }
            else if (it.value().compare(FONT_STYLE_ITALIC) == 0)
            {
                textControl_->textStyle()->setFontStyle(bb::cascades::FontStyle::Italic);
            }
            else
            {
                N_DEBUG(Native::Msg::Unknown_value_received << ": " << it.value());
            }
        }
        else if (it.key().compare(FONT_WEIGHT) == 0)
        {
            if (it.value().compare(FONT_WEIGHT_NORMAL) == 0)
            {
                textControl_->textStyle()->setFontWeight(bb::cascades::FontWeight::Normal);
            }
            else if (it.value().compare(FONT_WEIGHT_BOLD) == 0)
            {
                textControl_->textStyle()->setFontWeight(bb::cascades::FontWeight::Bold);
            }
            else
            {
                N_DEBUG(Native::Msg::Unknown_value_received << ": " << it.value());
            }
        }
        else
        {
            N_DEBUG(Native::Msg::Unknown_key_value_received << ": " << it.key() << ":" << it.value());
        }
    }

    return NATIVE_ERROR_OK;
}

void NativeAbstractTextControlObject::resize(float width, float height)
{
    NativeControlObject::resize(width, height);
    //textControl_->setPreferredWidth(width);
    //textControl_->setPreferredHeight(height);
}

