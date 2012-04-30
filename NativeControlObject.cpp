/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeControlObject.h"
#include <stdlib.h>

#define PROP_SETTING_FUNCTION(NAME)     prop_##NAME
#define PROP_SETTER_CSTRING(NAME)       static int prop_##NAME(NativeControlObject* object,const char* value) \
{\
    return object->NAME(value);\
}
#define PROP_SETTER_INT(NAME)           static int prop_##NAME(NativeControlObject* object,const char* value) \
{\
    return object->NAME(atoi(value));\
}

#define PROP_SETTER_FLOAT(NAME)         static int prop_##NAME(NativeControlObject* object,const char* value) \
{\
    return object->NAME(atof(value));\
}

typedef int (*NATIVE_PROPSET_CALLBACK)(NativeControlObject*, const char*);

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

PROP_SETTER_CSTRING(setBackgroundColor)
int NativeControlObject::setBackgroundColor(const char* text)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER_CSTRING(setLabel)
int NativeControlObject::setLabel(const char* text)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER_FLOAT(setMax)
int NativeControlObject::setMax(float max)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER_FLOAT(setMin)
int NativeControlObject::setMin(float min)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER_CSTRING(setText)
int NativeControlObject::setText(const char* text)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER_CSTRING(setTextAlign)
int NativeControlObject::setTextAlign(const char* align)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER_FLOAT(setTop)
int NativeControlObject::setTop(float top)
{
    control_->setTopMargin(top);
    return NATIVE_ERROR_OK;
}

PROP_SETTER_FLOAT(setValue)
int NativeControlObject::setValue(float value)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER_FLOAT(setWidth)
int NativeControlObject::setWidth(float width)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER_FLOAT(setHeight)
int NativeControlObject::setHeight(float height)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER_FLOAT(setLeft)
int NativeControlObject::setLeft(float left)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER_CSTRING(setHintText)
int NativeControlObject::setHintText(const char* hint)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

// PROP_SETTING_FUNCTION resolves the static name of the function, e.g.,
// PROP_SETTING_FUNCTION(setBackgroundColor) resolves to "prop_setBackgroundColor"

const static NATIVE_PROPSET_CALLBACK g_functionMap[] =
        {
                NULL,                                          // N_PROP_SET_UNDEFINED
                NULL,                                          // N_PROP_SET_ANCHOR_POINT
                NULL,                                          // N_PROP_SET_ANIMATED_CENTER_POINT
                PROP_SETTING_FUNCTION(setBackgroundColor),     // N_PROP_SET_BACKGROUND_COLOR
                NULL,                                          // N_PROP_SET_BACKGROUND_DISABLED_COLOR
                NULL,                                          // N_PROP_SET_BACKGROUND_DISABLED_IMAGE
                NULL,                                          // N_PROP_SET_BACKGROUND_FOCUSED_COLOR
                PROP_SETTING_FUNCTION(setLabel),               // N_PROP_SET_LABEL
                PROP_SETTING_FUNCTION(setMax),                 // N_PROP_SET_MAX
                PROP_SETTING_FUNCTION(setMin),                 // N_PROP_SET_MIN
                PROP_SETTING_FUNCTION(setText),                // N_PROP_SET_TEXT
                PROP_SETTING_FUNCTION(setTextAlign),           // N_PROP_SET_TEXT_ALIGN
                PROP_SETTING_FUNCTION(setTop),                 // N_PROP_SET_TOP
                PROP_SETTING_FUNCTION(setValue),               // N_PROP_SET_VALUE
                PROP_SETTING_FUNCTION(setLeft),                // N_PROP_SET_LEFT
                PROP_SETTING_FUNCTION(setWidth),               // N_PROP_SET_WIDTH
                PROP_SETTING_FUNCTION(setHeight),              // N_PROP_SET_HEIGHT
                PROP_SETTING_FUNCTION(setHintText)             // N_RROP_HINT_TEXT
        };

int NativeControlObject::setPropertyValue(int propertyNumber, const char* value)
{
    if ((propertyNumber < 0) || (propertyNumber >= (int) (sizeof(g_functionMap) / sizeof(*g_functionMap)))
            || (g_functionMap[propertyNumber] == NULL))
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (g_functionMap[propertyNumber])(this, value);
}
