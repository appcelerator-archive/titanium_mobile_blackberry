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
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/Color>
#include <qtgui/QColor>

#define PROP_SETTING_FUNCTION(NAME)     prop_##NAME

#define PROP_SETTER(NAME)               static int prop_##NAME(NativeControlObject* object, TiObject* obj) \
    {\
        return object->NAME(obj);\
    }

typedef int (*NATIVE_PROPSET_CALLBACK)(NativeControlObject*, TiObject*);

// Prototypes
static vector<NATIVE_PROPSET_CALLBACK> initFunctionMap();

// Statics
static const vector<NATIVE_PROPSET_CALLBACK> s_functionMap = initFunctionMap();


NativeControlObject::NativeControlObject()
{
    control_ = NULL;
    left_ = 0;
    top_ = 0;
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

PROP_SETTER(setBottom)
int NativeControlObject::setBottom(TiObject* obj)
{
    float bottom;
    int error = getFloat(obj, &bottom);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    ((bb::cascades::Control*)getNativeHandle())->setBottomMargin(bottom);
    return NATIVE_ERROR_OK;
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

PROP_SETTER(setLeft)
int NativeControlObject::setLeft(TiObject* obj)
{
    float left;
    int error = getFloat(obj, &left);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    ((bb::cascades::Control*)getNativeHandle())->setLeftMargin(left);
    return NATIVE_ERROR_OK;
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

PROP_SETTER(setRight)
int NativeControlObject::setRight(TiObject* obj)
{
    float right;
    int error = getFloat(obj, &right);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    ((bb::cascades::Control*)getNativeHandle())->setRightMargin(right);
    return NATIVE_ERROR_OK;
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
    float value = 0;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    bb::cascades::AbsoluteLayoutProperties* pProp = new bb::cascades::AbsoluteLayoutProperties;
    pProp->setPositionY(value);
    pProp->setPositionX(left_);
    control_->setLayoutProperties(pProp);

    return NATIVE_ERROR_OK;
}

PROP_SETTER(setValue)
int NativeControlObject::setValue(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setMinDate)
int NativeControlObject::setMinDate(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setMaxDate)
int NativeControlObject::setMaxDate(TiObject* obj)
{
	return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setData)
int NativeControlObject::setData(TiObject* obj)
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

PROP_SETTER(setOptions)
int NativeControlObject::setOptions(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setSelectedIndex)
int NativeControlObject::setSelectedIndex(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setImage)
int NativeControlObject::setImage(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setFont)
int NativeControlObject::setFont(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setWidth)
int NativeControlObject::setWidth(TiObject* obj)
{
    float width = 0;
    int error = NativeControlObject::getFloat(obj, &width);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    control_->setMinWidth(width);
    control_->setMaxWidth(width);
    return NATIVE_ERROR_OK;
}

PROP_SETTER(setHeight)
int NativeControlObject::setHeight(TiObject* obj)
{
    float height = 0;
    int error = NativeControlObject::getFloat(obj, &height);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    control_->setMinHeight(height);
    control_->setMaxHeight(height);
    return NATIVE_ERROR_OK;
}

PROP_SETTER(setHintText)
int NativeControlObject::setHintText(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setType)
int NativeControlObject::setType(TiObject* obj)
{
   return NATIVE_ERROR_NOTSUPPORTED;
}

// PROP_SETTING_FUNCTION resolves the static name of the function, e.g.,
// PROP_SETTING_FUNCTION(setBackgroundColor) resolves to "prop_setBackgroundColor"

static vector<NATIVE_PROPSET_CALLBACK> initFunctionMap()
{
    vector<NATIVE_PROPSET_CALLBACK> vect;
    vect.resize(N_PROP_LAST);

    vect[N_PROP_UNDEFINED]                         = NULL;
    vect[N_PROP_ANCHOR_POINT]                      = NULL;
    vect[N_PROP_ANIMATED_CENTER_POINT]             = NULL;
    vect[N_PROP_AUTO_LINK]                         = NULL;
    vect[N_PROP_BACKGROUND_COLOR]                  = PROP_SETTING_FUNCTION(setBackgroundColor);
    vect[N_PROP_BACKGROUND_DISABLED_COLOR]         = NULL;
    vect[N_PROP_BACKGROUND_DISABLED_IMAGE]         = NULL;
    vect[N_PROP_BACKGROUND_FOCUSED_COLOR]          = NULL;
    vect[N_PROP_BACKGROUND_FOCUSED_IMAGE]          = NULL;
    vect[N_PROP_BACKGROUND_GRADIANT]               = NULL;
    vect[N_PROP_BACKGROUND_IMAGE]                  = NULL;
    vect[N_PROP_BACKGROUND_LEFT_CAP]               = NULL;
    vect[N_PROP_BACKGROUND_PADDING_BOTTOM]         = NULL;
    vect[N_PROP_BACKGROUND_PADDING_LEFT]           = NULL;
    vect[N_PROP_BACKGROUND_PADDING_RIGHT]          = NULL;
    vect[N_PROP_BACKGROUND_PADDING_TOP]            = NULL;
    vect[N_PROP_BACKGROUND_REPEAT]                 = NULL;
    vect[N_PROP_BACKGROUND_SELECTED_COLOR]         = NULL;
    vect[N_PROP_BACKGROUND_SELECTED_IMAGE]         = NULL;
    vect[N_PROP_BACKGROUND_TOP_CAP]                = NULL;
    vect[N_PROP_BORDER_COLOR]                      = NULL;
    vect[N_PROP_BORDER_RADIUS]                     = NULL;
    vect[N_PROP_BORDER_WIDTH]                      = NULL;
    vect[N_PROP_BOTTOM]                            = PROP_SETTING_FUNCTION(setBottom);
    vect[N_PROP_CENTER]                            = NULL;
    vect[N_PROP_CHILDREN]                          = NULL;
    vect[N_PROP_COLOR]                             = PROP_SETTING_FUNCTION(setColor);
    vect[N_PROP_ELLIPSIZE]                         = NULL;
    vect[N_PROP_FOCUSABLE]                         = NULL;
    vect[N_PROP_FONT]                              = PROP_SETTING_FUNCTION(setFont);
    vect[N_PROP_HEIGHT]                            = PROP_SETTING_FUNCTION(setHeight);
    vect[N_PROP_HIGHLIGHTED_COLOR]                 = NULL;
    vect[N_PROP_HINT_TEXT]                         = PROP_SETTING_FUNCTION(setHintText);
    vect[N_PROP_HTML]                              = NULL;
    vect[N_PROP_IMAGE]                             = PROP_SETTING_FUNCTION(setImage);
    vect[N_PROP_KEEP_SCREEN_ON]                    = NULL;
    vect[N_PROP_LABEL]                             = PROP_SETTING_FUNCTION(setLabel);
    vect[N_PROP_LAYOUT]                            = NULL;
    vect[N_PROP_LEFT]                              = PROP_SETTING_FUNCTION(setLeft);
    vect[N_PROP_MAX]                               = PROP_SETTING_FUNCTION(setMax);
    vect[N_PROP_MIN]                               = PROP_SETTING_FUNCTION(setMin);
    vect[N_PROP_MAXDATE]                           = PROP_SETTING_FUNCTION(setMaxDate);
    vect[N_PROP_MINDATE]                           = PROP_SETTING_FUNCTION(setMinDate);
    vect[N_PROP_MINIMUM_FONT_SIZE]                 = NULL;
    vect[N_PROP_OPACITY]                           = NULL;
    vect[N_PROP_OPTIONS]                           = PROP_SETTING_FUNCTION(setOptions);
    vect[N_PROP_RIGHT]                             = NULL;
    vect[N_PROP_SELECTED_INDEX]                    = PROP_SETTING_FUNCTION(setSelectedIndex);
    vect[N_PROP_SHADOW_COLOR]                      = NULL;
    vect[N_PROP_SHADOW_OFFSET]                     = NULL;
    vect[N_PROP_SIZE]                              = NULL;
    vect[N_PROP_SOFT_KEYBOARD_ON_FOCUS]            = NULL;
    vect[N_PROP_TEXT]                              = PROP_SETTING_FUNCTION(setText);
    vect[N_PROP_TEXT_ALIGN]                        = PROP_SETTING_FUNCTION(setTextAlign);
    vect[N_PROP_TEXT_ID]                           = NULL;
    vect[N_PROP_TITLE]                             = PROP_SETTING_FUNCTION(setTitle);
    vect[N_PROP_TOP]                               = PROP_SETTING_FUNCTION(setTop);
    vect[N_PROP_TYPE]                              = PROP_SETTING_FUNCTION(setType);
    vect[N_PROP_TOUCH_ENABLED]                     = NULL;
    vect[N_PROP_TRANSFORM]                         = NULL;
    vect[N_PROP_VALUE]                             = PROP_SETTING_FUNCTION(setValue);
    vect[N_PROP_VISIBLE]                           = PROP_SETTING_FUNCTION(setVisible);
    vect[N_PROP_WIDTH]                             = PROP_SETTING_FUNCTION(setWidth);
    vect[N_PROP_WORD_WRAP]                         = NULL;
    vect[N_PROP_ZINDEX]                            = NULL;
    vect[N_PROP_DATA]                              = PROP_SETTING_FUNCTION(setData);
    return vect;
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

int NativeControlObject::getInteger(TiObject* obj, int* value)
{
    Handle<Value> v8value = obj->getValue();
    if ((v8value.IsEmpty()) || ((!v8value->IsNumber()) && (!v8value->IsNumberObject()) && (!v8value->IsInt32())))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Number> num = Handle<Number>::Cast(v8value);
    *value = (int)num->Value();
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getStringArray(TiObject* obj, QVector<QString>& value)
{
    Handle<Value> v8value = obj->getValue();
    if (v8value.IsEmpty() || !v8value->IsArray())
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Array> array = Handle<Array>::Cast(v8value);
    unsigned int uiLength = array->Length();
    for (unsigned int i = 0; i < uiLength; ++i)
    {
        Handle<Value> item = array->Get(Integer::New(i));
        if (item.IsEmpty() || ((!item->IsString()) && (!item->IsStringObject())))
        {
            return NATIVE_ERROR_INVALID_ARG;
        }
        String::Utf8Value v8UtfString(Handle<String>::Cast(item));
        const char* cStr = *v8UtfString;
        value.append(cStr);
    }
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getMapObject(TiObject* obj, QMap<QString, QString>& props)
{
    Handle<Value> v8value = obj->getValue();
    if (v8value.IsEmpty() || !v8value->IsObject())
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Object> object = Handle<Object>::Cast(v8value);
    Handle<Array> keys = object->GetPropertyNames();

    for (unsigned int i = 0; i < keys->Length(); i++)
    {
        v8::Handle<v8::String> key = keys->Get(v8::Integer::New(i))->ToString();
        v8::String::Utf8Value keyStr(key);
        v8::Handle<v8::String> value = object->Get(key)->ToString();
        v8::String::Utf8Value valueStr(value);
        QString strKey = QString::fromUtf8(*keyStr);
        QString strValue = QString::fromUtf8(*valueStr);

        props.insert(strKey, strValue);
    }

    return NATIVE_ERROR_OK;
}

int NativeControlObject::getDictionaryData(TiObject* obj, QVector<QPair<QString, QString> >& dictionary)
{
    Handle<Value> value = obj->getValue();
    if (value.IsEmpty() || (!value->IsArray()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }

    Handle<Array> array = Handle<Array>::Cast(value);
    uint32_t length = array->Length();
    dictionary.reserve(length);
    //traverse through the dictionary elements
    for (uint32_t i = 0; i < length; ++i)
    {
        Local<Value> el = array->Get(i);
        if (el->IsObject())
        {
            Local<Array> propAr = el->ToObject()->GetPropertyNames();
            uint32_t arLenght = propAr->Length();
            for (uint32_t j = 0; j < arLenght; ++j)
            {
                Handle<String> propString = Handle<String>::Cast(propAr->Get(j));
                String::Utf8Value propNameUTF(propString);
                QString key = QString::fromUtf8(*propNameUTF);
                Local<Value> propValue = el->ToObject()->Get(propString);
                Local<String> valueStr = propValue->ToString();
                String::Utf8Value valueUTF(valueStr);
                QString val = QString::fromUtf8(*valueUTF);
                dictionary.push_back(QPair<QString, QString>(key, val));
            }
        }
        else
        {
            //if the element of the dictionary is not object, it means dictionary contains invalid data
            return NATIVE_ERROR_INVALID_ARG;
        }
    }
    return NATIVE_ERROR_OK;
}
