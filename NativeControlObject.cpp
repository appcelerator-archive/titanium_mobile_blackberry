/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeControlObject.h"
#include <stdlib.h>
#include <string.h>
#include "TiObject.h"
#include <bb/cascades/Color>
#include <qtgui/QColor>

#define PROP_SETTING_FUNCTION(NAME)     prop_##NAME

#define PROP_SETTER(NAME)               static int prop_##NAME(NativeControlObject* object, TiObject* obj) \
    {\
        return object->NAME(obj);\
    }

#define GET_ARRAY_SIZE(T)               ((int)(sizeof(T) / sizeof(*T)))

typedef int (*NATIVE_PROPSET_CALLBACK)(NativeControlObject*, TiObject*);

NativeControlObject::NativeControlObject()
{
    control_ = NULL;
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
// NOTE: These must be in order of the property index.

const static NATIVE_PROPSET_CALLBACK g_functionMap[] =
{
    NULL,                                          // N_PROP_UNDEFINED
    NULL,                                          // N_PROP_ANCHOR_POINT
    NULL,                                          // N_PROP_ANIMATED_CENTER_POINT
    NULL,                                          // N_PROP_AUTO_LINK
    PROP_SETTING_FUNCTION(setBackgroundColor),     // N_PROP_BACKGROUND_COLOR
    NULL,                                          // N_PROP_BACKGROUND_DISABLED_COLOR
    NULL,                                          // N_PROP_BACKGROUND_DISABLED_IMAGE
    NULL,                                          // N_PROP_BACKGROUND_FOCUSED_COLOR
    NULL,                                          // N_PROP_BACKGROUND_FOCUSED_IMAGE
    NULL,                                          // N_PROP_BACKGROUND_GRADIANT
    NULL,                                          // N_PROP_BACKGROUND_IMAGE
    NULL,                                          // N_PROP_BACKGROUND_LEFT_CAP
    NULL,                                          // N_PROP_BACKGROUND_PADDING_BOTTOM
    NULL,                                          // N_PROP_BACKGROUND_PADDING_LEFT
    NULL,                                          // N_PROP_BACKGROUND_PADDING_RIGHT
    NULL,                                          // N_PROP_BACKGROUND_PADDING_TOP
    NULL,                                          // N_PROP_BACKGROUND_REPEAT
    NULL,                                          // N_PROP_BACKGROUND_SELECTED_COLOR
    NULL,                                          // N_PROP_BACKGROUND_SELECTED_IMAGE
    NULL,                                          // N_PROP_BACKGROUND_TOP_CAP
    NULL,                                          // N_PROP_BORDER_COLOR
    NULL,                                          // N_PROP_BORDER_RADIUS
    NULL,                                          // N_PROP_BORDER_WIDTH
    NULL,                                          // N_PROP_BOTTOM
    NULL,                                          // N_PROP_CENTER
    NULL,                                          // N_PROP_CHILDREN
    PROP_SETTING_FUNCTION(setColor),               // N_PROP_COLOR
    NULL,                                          // N_PROP_ELLIPSIZE
    NULL,                                          // N_PROP_FOCUSABLE
    NULL,                                          // N_PROP_FONT
    NULL,                                          // N_PROP_HEIGHT
    NULL,                                          // N_PROP_HIGHLIGHTED_COLOR
    NULL,                                          // N_PROP_HTML
    NULL,                                          // N_PROP_KEEP_SCREEN_ON
    PROP_SETTING_FUNCTION(setLabel),               // N_PROP_LABEL
    NULL,                                          // N_PROP_LAYOUT
    NULL,                                          // N_PROP_LEFT
    PROP_SETTING_FUNCTION(setMax),                 // N_PROP_MAX
    PROP_SETTING_FUNCTION(setMin),                 // N_PROP_MIN
    NULL,                                          // N_PROP_MINIMUM_FONT_SIZE
    NULL,                                          // N_PROP_OPACITY
    NULL,                                          // N_PROP_RIGHT
    NULL,                                          // N_PROP_SHADOW_COLOR
    NULL,                                          // N_PROP_SHADOW_OFFSET
    NULL,                                          // N_PROP_SIZE
    NULL,                                          // N_PROP_SOFT_KEYBOARD_ON_FOCUS
    PROP_SETTING_FUNCTION(setText),                // N_PROP_TEXT
    PROP_SETTING_FUNCTION(setTextAlign),           // N_PROP_TEXT_ALIGN
    NULL,                                          // N_PROP_TEXT_ID
    PROP_SETTING_FUNCTION(setTitle),               // N_PROP_TITLE
    PROP_SETTING_FUNCTION(setTop),                 // N_PROP_TOP
    NULL,                                          // N_PROP_TOUCH_ENABLED
    NULL,                                          // N_PROP_TRANSFORM
    PROP_SETTING_FUNCTION(setValue),               // N_PROP_VALUE
    PROP_SETTING_FUNCTION(setVisible),             // N_PROP_VISIBLE
    NULL,                                          // N_PROP_WIDTH
    NULL,                                          // N_PROP_WORD_WRAP
    NULL                                           // N_PROP_ZINDEX
};

int NativeControlObject::setPropertyValue(int propertyNumber, TiObject* obj)
{
    if ((propertyNumber < 0) || (propertyNumber >= GET_ARRAY_SIZE(g_functionMap))
            || (g_functionMap[propertyNumber] == NULL))
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (g_functionMap[propertyNumber])(this, obj);
}

int NativeControlObject::getColorComponents(TiObject* obj, float* r, float* g, float* b, float* a)
{
    if(obj == NULL)
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Value> value = obj->getValue();
    if ((value.IsEmpty()) || (!value->IsString()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<String> v8color = Handle<String>::Cast(value);
    String::Utf8Value v8colorString(v8color);
    if(!QColor::isValidColor(*v8colorString))
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
    if(obj == NULL)
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
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
    if(obj == NULL)
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
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
    if(obj == NULL)
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Value> v8value = obj->getValue();
    if ((v8value.IsEmpty()) || ((!v8value->IsNumber()) && (!v8value->IsNumberObject())))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Number> num = Handle<Number>::Cast(v8value);
    *value = (float)num->Value();
    return NATIVE_ERROR_OK;
}
