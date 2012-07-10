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
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/Color>
#include <bb/cascades/Container>
#include <qtgui/QColor>

#define PROP_SETGET_FUNCTION(NAME)      prop_##NAME

#define PROP_SETGET(NAME)               static int prop_##NAME(NativeControlObject* object, TiObject* obj) \
    {\
        return object->NAME(obj);\
    }

#define GET_ARRAY_SIZE(ARRAY)           (int)(sizeof(ARRAY)/sizeof(*(ARRAY)))

typedef int (*NATIVE_PROPSETGET_CALLBACK)(NativeControlObject*, TiObject*);

struct NATIVE_PROPSETGET_SETTING
{
    NATIVE_PROP propNumber;
    NATIVE_PROPSETGET_CALLBACK setter;
    NATIVE_PROPSETGET_CALLBACK getter;
};

class SetGetProperties
{
public:
    SetGetProperties(const NATIVE_PROPSETGET_SETTING* map, int mapEntries)
    {
        setters_ = new NATIVE_PROPSETGET_CALLBACK[N_PROP_LAST];
        memset(setters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_PROP_LAST);
        getters_ = new NATIVE_PROPSETGET_CALLBACK[N_PROP_LAST];
        memset(getters_, 0, sizeof(NATIVE_PROPSETGET_CALLBACK) * N_PROP_LAST);
        for (int i = 0; i < mapEntries; i++)
        {
            setters_[map[i].propNumber] = map[i].setter;
            getters_[map[i].propNumber] = map[i].getter;
        }
    }
    ~SetGetProperties()
    {
        if (setters_ != NULL)
        {
            delete[] setters_;
            setters_ = NULL;
        }
        if (getters_ != NULL)
        {
            delete[] getters_;
            getters_ = NULL;
        }
    }
    NATIVE_PROPSETGET_CALLBACK GetSetterCallback(size_t prop)
    {
        if (prop >= (std::size_t)N_PROP_LAST)
        {
            return NULL;
        }
        return setters_[prop];
    }
    NATIVE_PROPSETGET_CALLBACK GetGetterCallback(size_t prop)
    {
        if (prop >= (std::size_t)N_PROP_LAST)
        {
            return NULL;
        }
        return getters_[prop];
    }
private:
    // Disabled default and copy constructors
    SetGetProperties();
    SetGetProperties(const SetGetProperties& prop);
    // Disabled assignment operator
    const SetGetProperties& operator = (const SetGetProperties& prop);
    NATIVE_PROPSETGET_CALLBACK* setters_;
    NATIVE_PROPSETGET_CALLBACK* getters_;
};

// Unit types
struct UnitTypeData
{
    UnitType unitType;
    const char* postfix;
};

const static UnitTypeData g_unitTypes[] =
{
    {UnitTypePixels, "px"},
    {UnitTypePercent, "%"},
    {UnitTypeDIP, "dip"},
    {UnitTypeInches, "in"},
    {UnitTypeMM, "mm"},
    {UnitTypeCM, "cm"},
    {UnitTypePT, "pt"}
};

NativeControlObject::NativeControlObject() :
    container_(NULL),
    control_(NULL),
    layout_(NULL),
    left_(0),
    top_(0),
    nextEventId_(1)
{
}

NativeControlObject::~NativeControlObject()
{
}

NAHANDLE NativeControlObject::getNativeHandle() const
{
    return container_;
}

void NativeControlObject::setControl(bb::cascades::Control* control)
{
    if (container_ == NULL)
    {
        container_ = bb::cascades::Container::create();
        container_->setLayout(new bb::cascades::AbsoluteLayout());
        layout_ = new bb::cascades::AbsoluteLayoutProperties;
        container_->setLayoutProperties(layout_);
    }
    container_->add(control);
    control_ = control;
}

int NativeControlObject::getNextEventId()
{
    // Account for overflow.
    if (nextEventId_ < 1)
    {
        // This event id must start at 1 because 0 is reserved. Since
        // V8 will always cast a value of undefined to zero.
        nextEventId_ = 1;
    }
    return nextEventId_++;
}

int NativeControlObject::setVisibility(bool visible)
{
    container_->setVisible(visible);
    return NATIVE_ERROR_OK;
}


// PROP_SETTER creates a static version of functions which
// calls the non-static on method on the NativeControlObject
// class.

PROP_SETGET(setAnchorPoint)
int NativeControlObject::setAnchorPoint(TiObject* obj)
{
    float x;
    float y;
    int error = NativeControlObject::getPoint(obj, &x, &y);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    container_->setPivotX(x);
    container_->setPivotY(y);
    return NATIVE_ERROR_OK;
}


PROP_SETGET(setBackgroundColor)
int NativeControlObject::setBackgroundColor(TiObject* obj)
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
    backgroundColor_ = bb::cascades::Color::fromRGBA(r, g, b, a);
    if (container_->isEnabled())
    {
        container_->setBackground(backgroundColor_);
    }
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setBackgroundDisableColor)
int NativeControlObject::setBackgroundDisableColor(TiObject* obj)
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
    disabledBackgroundColor_ = bb::cascades::Color::fromRGBA(r, g, b, a);
    if (!container_->isEnabled())
    {
        container_->setBackground(disabledBackgroundColor_);
    }
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setColor)
int NativeControlObject::setColor(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setData)
int NativeControlObject::setData(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setEnabled)
int NativeControlObject::setEnabled(TiObject* obj)
{
    bool enabled;
    int error = getBoolean(obj, &enabled);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    container_->setEnabled(enabled);
    if (enabled)
    {
        if (backgroundColor_.isValid())
        {
            container_->setBackground(backgroundColor_);
        }
    }
    else
    {
        if (disabledBackgroundColor_.isValid())
        {
            container_->setBackground(disabledBackgroundColor_);
        }
    }
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setFont)
int NativeControlObject::setFont(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setHeight)
int NativeControlObject::setHeight(TiObject* obj)
{
    float height;
    int error = getFloat(obj, &height);
    if (error != NATIVE_ERROR_OK)
    {
        Handle<String> v8str = obj->getValue()->ToString();
        if (v8str.IsEmpty())
        {
            return NATIVE_ERROR_INVALID_ARG;
        }
        // TODO: parse height string, e.g., height='100%' height='22px' etc...
        return NATIVE_ERROR_INVALID_ARG;
    }
    container_->setMaxHeight(height);
    container_->setMinHeight(height);
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setHintText)
int NativeControlObject::setHintText(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setImage)
int NativeControlObject::setImage(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setLabel)
int NativeControlObject::setLabel(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setLeft)
int NativeControlObject::setLeft(TiObject* obj)
{
    float value = 0;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    layout_->setPositionX(value);
    container_->setLayoutProperties(layout_);
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setMax)
int NativeControlObject::setMax(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setMinDate)
int NativeControlObject::setMinDate(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setMaxDate)
int NativeControlObject::setMaxDate(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setMin)
int NativeControlObject::setMin(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setOpacity)
int NativeControlObject::setOpacity(TiObject* obj)
{
    float value = 0;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    if ((value < 0.0f) || (value > 1.0f))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    control_->setOpacity(value);
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setOptions)
int NativeControlObject::setOptions(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setSelectedIndex)
int NativeControlObject::setSelectedIndex(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setText)
int NativeControlObject::setText(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setTextAlign)
int NativeControlObject::setTextAlign(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setTitle)
int NativeControlObject::setTitle(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setTop)
int NativeControlObject::setTop(TiObject* obj)
{
    float value = 0;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    layout_->setPositionY(value);
    container_->setLayoutProperties(layout_);
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setValue)
int NativeControlObject::setValue(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setVisible)
int NativeControlObject::setVisible(TiObject* obj)
{
    bool visible;
    int error = getBoolean(obj, &visible);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    return setVisibility(visible);
}

PROP_SETGET(getVisible)
int NativeControlObject::getVisible(TiObject* obj)
{
    obj->setValue(Boolean::New(container_->isVisible()));
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setWidth)
int NativeControlObject::setWidth(TiObject* obj)
{
    float width;
    // TODO: get the current width of the parent control
    float max = 1024.0f; // TODO: Remove this
    int error = getMeasurementInfo(obj, max, &width);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    container_->setMaxWidth(width);
    container_->setMinWidth(width);
    return NATIVE_ERROR_OK;
}

PROP_SETGET(setType)
int NativeControlObject::setType(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setRight)
int NativeControlObject::setRight(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setWindow)
int NativeControlObject::setWindow(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETGET(setIcon)
int NativeControlObject::setIcon(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

// PROP_SETTING_FUNCTION resolves the static name of the function, e.g.,
// PROP_SETTING_FUNCTION(setBackgroundColor) resolves to "prop_setBackgroundColor"

const static NATIVE_PROPSETGET_SETTING g_propSetGet[] =
{
    {N_PROP_ANCHOR_POINT, PROP_SETGET_FUNCTION(setAnchorPoint), NULL},
    {N_PROP_BACKGROUND_COLOR, PROP_SETGET_FUNCTION(setBackgroundColor), NULL},
    {N_PROP_BACKGROUND_DISABLED_COLOR, PROP_SETGET_FUNCTION(setBackgroundDisableColor), NULL},
    {N_PROP_COLOR, PROP_SETGET_FUNCTION(setColor), NULL},
    {N_PROP_DATA, PROP_SETGET_FUNCTION(setData), NULL},
    {N_PROP_ENABLED, PROP_SETGET_FUNCTION(setEnabled), NULL},
    {N_PROP_FONT, PROP_SETGET_FUNCTION(setFont), NULL},
    {N_PROP_HEIGHT, PROP_SETGET_FUNCTION(setHeight), NULL},
    {N_PROP_HINT_TEXT, PROP_SETGET_FUNCTION(setHintText), NULL},
    {N_PROP_ICON, PROP_SETGET_FUNCTION(setIcon), NULL},
    {N_PROP_IMAGE, PROP_SETGET_FUNCTION(setImage), NULL},
    {N_PROP_LABEL, PROP_SETGET_FUNCTION(setLabel), NULL},
    {N_PROP_LEFT, PROP_SETGET_FUNCTION(setLeft), NULL},
    {N_PROP_MAX, PROP_SETGET_FUNCTION(setMax), NULL},
    {N_PROP_MAXDATE, PROP_SETGET_FUNCTION(setMaxDate), NULL},
    {N_PROP_MIN, PROP_SETGET_FUNCTION(setMin), NULL},
    {N_PROP_MINDATE, PROP_SETGET_FUNCTION(setMinDate), NULL},
    {N_PROP_OPACITY, PROP_SETGET_FUNCTION(setOpacity), NULL},
    {N_PROP_OPTIONS, PROP_SETGET_FUNCTION(setOptions), NULL},
    {N_PROP_SELECTED_INDEX, PROP_SETGET_FUNCTION(setSelectedIndex), NULL},
    {N_PROP_TEXT, PROP_SETGET_FUNCTION(setText), NULL},
    {N_PROP_TEXT_ALIGN, PROP_SETGET_FUNCTION(setTextAlign), NULL},
    {N_PROP_TITLE, PROP_SETGET_FUNCTION(setTitle), NULL},
    {N_PROP_TOP, PROP_SETGET_FUNCTION(setTop), NULL},
    {N_PROP_TYPE, PROP_SETGET_FUNCTION(setType), NULL},
    {N_PROP_VALUE, PROP_SETGET_FUNCTION(setValue), NULL},
    {N_PROP_VISIBLE, PROP_SETGET_FUNCTION(setVisible), PROP_SETGET_FUNCTION(getVisible)},
    {N_PROP_WIDTH, PROP_SETGET_FUNCTION(setWidth), NULL},
    {N_PROP_WINDOW, PROP_SETGET_FUNCTION(setWindow), NULL}
};

static SetGetProperties g_props(g_propSetGet, GET_ARRAY_SIZE(g_propSetGet));


int NativeControlObject::setPropertyValue(size_t propertyNumber, TiObject* obj)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_props.GetSetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj);
}

int NativeControlObject::getPropertyValue(size_t propertyNumber, TiObject* obj)
{
    NATIVE_PROPSETGET_CALLBACK cb = g_props.GetGetterCallback(propertyNumber);
    if (cb == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (cb)(this, obj);
}

int NativeControlObject::getColorComponents(TiObject* obj, float* r, float* g, float* b, float* a)
{
    QString qcolorString;
    int error = getString(obj, qcolorString);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    if (!QColor::isValidColor(qcolorString))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    QColor qcolor(qcolorString);
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
    if (value.IsEmpty())
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    if (!value->IsString())
    {
        value = obj->getValue()->ToString();
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

int NativeControlObject::getPoint(TiObject* obj, float* x, float* y)
{
    Handle<Value> v8value = obj->getValue();
    if ((v8value.IsEmpty()) || (!v8value->IsObject()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Object> v8obj = Handle<Object>::Cast(v8value);
    Handle<Value> v8x = v8obj->Get(String::New("x"));
    if ((v8x.IsEmpty()) || (!v8x->IsNumber()) || (!v8x->IsNumberObject()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Value> v8y = v8obj->Get(String::New("y"));
    if ((v8y.IsEmpty()) || (!v8y->IsNumber()) || (!v8y->IsNumberObject()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    if (x != NULL)
    {
        *x = (float)v8x->ToNumber()->Value();
    }
    if (y != NULL)
    {
        *y = (float)v8y->ToNumber()->Value();
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

int NativeControlObject::getMeasurementInfo(TiObject* obj, float max,
        float* calculatedValue)
{
    UnitType unitType = UnitTypeDefault;
    if ((!obj->getValue()->IsString()) && (!obj->getValue()->IsStringObject()))
    {
        float value;
        int error = getFloat(obj, &value);
        if (error != NATIVE_ERROR_OK)
        {
            return error;
        }
        if (value < 0.0f)
        {
            value = 0.0f;
        }
        else if (value > max)
        {
            value = max;
        }
        *calculatedValue = value;
        return NATIVE_ERROR_OK;
    }
    v8::String::Utf8Value myString(obj->getValue()->ToString());
    QString measurement = (const char*)(*myString);
    float numberPart = (float)atof(*myString);
    for (int i = 0; i < GET_ARRAY_SIZE(g_unitTypes); i++)
    {
        if (measurement.endsWith(QString(g_unitTypes[i].postfix)))
        {
            unitType = g_unitTypes[i].unitType;
        }
    }
    if (unitType == UnitTypeDefault)
    {
        // Default to 'pixels'
        unitType = UnitTypePixels;
    }
    switch (unitType)
    {
    case UnitTypePixels:
        if (numberPart < 0.0f)
        {
            numberPart = 0.0f;
        }
        else if (numberPart > max)
        {
            numberPart = max;
        }
        *calculatedValue = numberPart;
        break;
    case UnitTypePercent:
        if (numberPart < 0.0f)
        {
            numberPart = 0.0f;
        }
        else if (numberPart > 100.0f)
        {
            numberPart = 100.0f;
        }
        if (max <= 0.0f)
        {
            *calculatedValue = 0;
        }
        else
        {
            *calculatedValue = max * numberPart / 100;
        }
        break;
    case UnitTypeDIP:
        // TODO: complete (NOTE: DPI is required)
        break;
    case UnitTypeInches:
        // TODO: complete (NOTE: DPI is required)
        break;
    case UnitTypeMM:
        // TODO: complete (NOTE: DPI is required)
        break;
    case UnitTypeCM:
        // TODO: complete (NOTE: DPI is required)
        break;
    case UnitTypePT:
        // TODO: complete (NOTE: DPI is required)
        break;
    default:
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return NATIVE_ERROR_OK;
}
