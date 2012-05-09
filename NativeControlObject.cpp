/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeControlObject.h"
#include <stdlib.h>
#include <string.h>

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

#define PROP_SETTER_BOOL(NAME)          static int prop_##NAME(NativeControlObject* object,const char* value) \
    {\
        bool b=false;\
        if((stricmp(value,"true")==0)||(atoi(value)!=0)) \
        {\
            b=true;\
        }\
        return object->NAME(b);\
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

PROP_SETTER_CSTRING(setColor)
int NativeControlObject::setColor(const char* color)
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

PROP_SETTER_BOOL(setVisible)
int NativeControlObject::setVisible(bool visible)
{
    NAHANDLE value = getNativeHandle();
    if (value == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    ((bb::cascades::Control*)value)->setVisible(visible);
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
    PROP_SETTING_FUNCTION(setTop),                 // N_PROP_TOP
    NULL,                                          // N_PROP_TOUCH_ENABLED
    NULL,                                          // N_PROP_TRANSFORM
    PROP_SETTING_FUNCTION(setValue),               // N_PROP_VALUE
    PROP_SETTING_FUNCTION(setVisible),             // N_PROP_VISIBLE
    NULL,                                          // N_PROP_WIDTH
    NULL,                                          // N_PROP_WORD_WRAP
    NULL                                           // N_PROP_ZINDEX
};

int NativeControlObject::setPropertyValue(int propertyNumber, const char* value)
{
    if ((propertyNumber < 0) || (propertyNumber >= (int)(sizeof(g_functionMap) / sizeof(*g_functionMap)))
            || (g_functionMap[propertyNumber] == NULL))
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (g_functionMap[propertyNumber])(this, value);
}
