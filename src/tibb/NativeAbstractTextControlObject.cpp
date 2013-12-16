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
#include "TiUtils.h"
#include "TiCore.h"

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
	TiUtils *tiUtils = TiUtils::getInstance();
	ppi_ = tiUtils->getPPI();
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
	Ti::TiHelper::applyFontToText(Ti::TiValue(obj->getValue()), textControl_);
	return NATIVE_ERROR_OK;
}

void NativeAbstractTextControlObject::updateLayout(QRectF rect)
{
	NativeControlObject::updateLayout(rect);

	if (!deferWidth_) {
		textControl_->setPreferredWidth(rect.width());
	}

	if (!deferHeight_) {
		textControl_->setPreferredHeight(rect.height());
	}
}
