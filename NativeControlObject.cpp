/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeControlObject.h"

#define PROP_SETTING_FUNCTION(NAME)     prop_##NAME
#define PROP_SETTER(NAME)               static int prop_##NAME(NativeControlObject* object,const char* value) \
{\
    return object->NAME(value);\
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

PROP_SETTER(setBackgroundColor)
int NativeControlObject::setBackgroundColor(const char* text)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setText)
int NativeControlObject::setText(const char* text)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setTextAlign)
int NativeControlObject::setTextAlign(const char* align)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

const static NATIVE_PROPSET_CALLBACK g_functionMap[] = {NULL,                                    // N_PROP_SET_UNDEFINED
        NULL,                                          // N_PROP_SET_ANCHOR_POINT
        NULL,                                          // N_PROP_SET_ANIMATED_CENTER_POINT
        PROP_SETTING_FUNCTION(setBackgroundColor),     // N_PROP_SET_BACKGROUND_COLOR
        NULL,                                          // N_PROP_SET_BACKGROUND_DISABLED_COLOR
        NULL,                                          // N_PROP_SET_BACKGROUND_DISABLED_IMAGE
        NULL,                                          // N_PROP_SET_BACKGROUND_FOCUSED_COLOR
        PROP_SETTING_FUNCTION(setText),                // N_PROP_SET_TEXT
        PROP_SETTING_FUNCTION(setTextAlign)};

int NativeControlObject::setPropertyValue(int propertyNumber, const char* value)
{
    if ((propertyNumber < 0) || (propertyNumber >= (int) (sizeof(g_functionMap) / sizeof(*g_functionMap)))
        || (g_functionMap[propertyNumber] == NULL))
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (g_functionMap[propertyNumber])(this, value);
}
