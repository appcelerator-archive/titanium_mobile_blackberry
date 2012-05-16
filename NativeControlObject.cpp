/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeControlObject.h"

#include "TiObject.h"
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <bb/cascades/Color>
#include <qtgui/QColor>

#define PROP_SETTING_FUNCTION(NAME)     prop_##NAME

#define PROP_SETTER(NAME)               static int prop_##NAME(NativeControlObject* object, TiObject* obj) \
    {\
        return object->NAME(obj);\
    }

typedef int (*NATIVE_PROPSET_CALLBACK)(NativeControlObject*, TiObject*);

// Prototypes
static void initPropertyMap();

// Statics
static vector<NATIVE_PROPSET_CALLBACK> s_functionMap;


NativeControlObject::NativeControlObject()
{
    control_ = NULL;
    initPropertyMap();
}

NativeControlObject::~NativeControlObject()
{
}

bb::cascades::Control* NativeControlObject::getControl() const
{
    return control_;
}

void NativeControlObject::setControl(bb::cascades::Control* control)
{
    control_ = control;
}

// PROP_SETTER_xxx creates a static version of functions which
// calls the non-static on method on the NativeControlObject
// class.

PROP_SETTER(setBackgroundColor)
int NativeControlObject::setBackgroundColor(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setColor)
int NativeControlObject::setColor(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setLabel)
int NativeControlObject::setLabel(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setMax)
int NativeControlObject::setMax(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setMin)
int NativeControlObject::setMin(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setText)
int NativeControlObject::setText(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setTextAlign)
int NativeControlObject::setTextAlign(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setTitle)
int NativeControlObject::setTitle(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setTop)
int NativeControlObject::setTop(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setValue)
int NativeControlObject::setValue(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setVisible)
int NativeControlObject::setVisible(TiObject* obj)
{
    bool visible;
    int error = getBoolean(obj, &visible);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    ((bb::cascades::Control*)getNativeHandle())->setVisible(visible);
    return NATIVE_ERROR_OK;
}

// PROP_SETTING_FUNCTION resolves the static name of the function, e.g.,
// PROP_SETTING_FUNCTION(setBackgroundColor) resolves to "prop_setBackgroundColor"

static void initPropertyMap()
{
    static bool initialized = false;
    if (initialized == false)
    {
        initialized = true;
        s_functionMap.resize(N_PROP_LAST);

        s_functionMap[N_PROP_UNDEFINED]                         = NULL;
        s_functionMap[N_PROP_ANCHOR_POINT]                      = NULL;
        s_functionMap[N_PROP_ANIMATED_CENTER_POINT]             = NULL;
        s_functionMap[N_PROP_AUTO_LINK]                         = NULL;
        s_functionMap[N_PROP_BACKGROUND_COLOR]                  = PROP_SETTING_FUNCTION(setBackgroundColor);
        s_functionMap[N_PROP_BACKGROUND_DISABLED_COLOR]         = NULL;
        s_functionMap[N_PROP_BACKGROUND_DISABLED_IMAGE]         = NULL;
        s_functionMap[N_PROP_BACKGROUND_FOCUSED_COLOR]          = NULL;
        s_functionMap[N_PROP_BACKGROUND_FOCUSED_IMAGE]          = NULL;
        s_functionMap[N_PROP_BACKGROUND_GRADIANT]               = NULL;
        s_functionMap[N_PROP_BACKGROUND_IMAGE]                  = NULL;
        s_functionMap[N_PROP_BACKGROUND_LEFT_CAP]               = NULL;
        s_functionMap[N_PROP_BACKGROUND_PADDING_BOTTOM]         = NULL;
        s_functionMap[N_PROP_BACKGROUND_PADDING_LEFT]           = NULL;
        s_functionMap[N_PROP_BACKGROUND_PADDING_RIGHT]          = NULL;
        s_functionMap[N_PROP_BACKGROUND_PADDING_TOP]            = NULL;
        s_functionMap[N_PROP_BACKGROUND_REPEAT]                 = NULL;
        s_functionMap[N_PROP_BACKGROUND_SELECTED_COLOR]         = NULL;
        s_functionMap[N_PROP_BACKGROUND_SELECTED_IMAGE]         = NULL;
        s_functionMap[N_PROP_BACKGROUND_TOP_CAP]                = NULL;
        s_functionMap[N_PROP_BORDER_COLOR]                      = NULL;
        s_functionMap[N_PROP_BORDER_RADIUS]                     = NULL;
        s_functionMap[N_PROP_BORDER_WIDTH]                      = NULL;
        s_functionMap[N_PROP_BOTTOM]                            = NULL;
        s_functionMap[N_PROP_CENTER]                            = NULL;
        s_functionMap[N_PROP_CHILDREN]                          = NULL;
        s_functionMap[N_PROP_COLOR]                             = PROP_SETTING_FUNCTION(setColor);
        s_functionMap[N_PROP_ELLIPSIZE]                         = NULL;
        s_functionMap[N_PROP_FOCUSABLE]                         = NULL;
        s_functionMap[N_PROP_FONT]                              = NULL;
        s_functionMap[N_PROP_HEIGHT]                            = NULL;
        s_functionMap[N_PROP_HIGHLIGHTED_COLOR]                 = NULL;
        s_functionMap[N_PROP_HINT_TEXT]                         = NULL;
        s_functionMap[N_PROP_HTML]                              = NULL;
        s_functionMap[N_PROP_IMAGE]                             = NULL;
        s_functionMap[N_PROP_KEEP_SCREEN_ON]                    = NULL;
        s_functionMap[N_PROP_LABEL]                             = PROP_SETTING_FUNCTION(setLabel);
        s_functionMap[N_PROP_LAYOUT]                            = NULL;
        s_functionMap[N_PROP_LEFT]                              = NULL;
        s_functionMap[N_PROP_MAX]                               = PROP_SETTING_FUNCTION(setMax);
        s_functionMap[N_PROP_MIN]                               = PROP_SETTING_FUNCTION(setMin);
        s_functionMap[N_PROP_MINIMUM_FONT_SIZE]                 = NULL;
        s_functionMap[N_PROP_OPACITY]                           = NULL;
        s_functionMap[N_PROP_RIGHT]                             = NULL;
        s_functionMap[N_PROP_SHADOW_COLOR]                      = NULL;
        s_functionMap[N_PROP_SHADOW_OFFSET]                     = NULL;
        s_functionMap[N_PROP_SIZE]                              = NULL;
        s_functionMap[N_PROP_SOFT_KEYBOARD_ON_FOCUS]            = NULL;
        s_functionMap[N_PROP_TEXT]                              = PROP_SETTING_FUNCTION(setText);
        s_functionMap[N_PROP_TEXT_ALIGN]                        = PROP_SETTING_FUNCTION(setTextAlign);
        s_functionMap[N_PROP_TEXT_ID]                           = NULL;
        s_functionMap[N_PROP_TITLE]                             = PROP_SETTING_FUNCTION(setTitle);
        s_functionMap[N_PROP_TOP]                               = PROP_SETTING_FUNCTION(setTop);
        s_functionMap[N_PROP_TOUCH_ENABLED]                     = NULL;
        s_functionMap[N_PROP_TRANSFORM]                         = NULL;
        s_functionMap[N_PROP_VALUE]                             = PROP_SETTING_FUNCTION(setValue);
        s_functionMap[N_PROP_VISIBLE]                           = PROP_SETTING_FUNCTION(setVisible);
        s_functionMap[N_PROP_WIDTH]                             = NULL;
        s_functionMap[N_PROP_WORD_WRAP]                         = NULL;
        s_functionMap[N_PROP_ZINDEX]                            = NULL;
    }
}


int NativeControlObject::setPropertyValue(size_t propertyNumber, TiObject* obj)
{
    if ((propertyNumber < 0) || (propertyNumber >= s_functionMap.size())
            || (s_functionMap[propertyNumber] == NULL))
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (s_functionMap[propertyNumber])(this, obj);
}

int NativeControlObject::getColorComponents(TiObject* obj, float* r, float* g, float* b, float* a)
{
    Handle<Value> value = obj->getValue();
    if ((value.IsEmpty()) || (!value->IsString()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<String> v8color = Handle<String>::Cast(value);
    String::Utf8Value v8colorString(v8color);
    if (!QColor::isValidColor(*v8colorString))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    QColor qcolor(*v8colorString);
    qreal qr, qg, qb, qa;
    qcolor.getRgbF(&qr, &qg, &qb, &qa);
    *r = qr;
    *g = qg;
    *b = qb;
    *a = qa;
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getBoolean(TiObject* obj, bool* value)
{
    Handle<Value> v8value = obj->getValue();
    if ((v8value.IsEmpty()) || ((!v8value->IsBoolean()) && (!v8value->IsBooleanObject())))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Boolean> b = v8value->ToBoolean();
    *value = b->Value();
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getString(TiObject* obj, QString& str)
{
    Handle<Value> value = obj->getValue();
    if ((value.IsEmpty()) || (!value->IsString()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<String> v8string = Handle<String>::Cast(value);
    String::Utf8Value v8UtfString(v8string);
    const char* cStr = *v8UtfString;
    str = cStr;
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getFloat(TiObject* obj, float* value)
{
    Handle<Value> v8value = obj->getValue();
    if ((v8value.IsEmpty()) || ((!v8value->IsNumber()) && (!v8value->IsNumberObject())))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Number> num = Handle<Number>::Cast(v8value);
    *value = (float)num->Value();
    return NATIVE_ERROR_OK;
}
