/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeDateTimePickerObject.h"

#include "ConversionHelper.h"
#include "TiConstants.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/DateTimePIcker>
#include <QDateTime>

NativeDateTimePickerObject::NativeDateTimePickerObject() :
    dateTimePicker_(NULL),
    eventChange_(NULL),
    eventHandler_(NULL),
    left_(0),
    top_(0)
{
}

NativeDateTimePickerObject::~NativeDateTimePickerObject()
{
    delete dateTimePicker_;
    dateTimePicker_ = NULL;
    delete eventChange_;
    eventChange_ = NULL;
    delete eventHandler_;
    eventHandler_ = NULL;
}

NativeDateTimePickerObject* NativeDateTimePickerObject::createDateTimePicker()
{
    return new NativeDateTimePickerObject;
}

int NativeDateTimePickerObject::initialize(TiEventContainerFactory* containerFactory)
{
    dateTimePicker_ = bb::cascades::DateTimePicker::create();
    setControl(dateTimePicker_);
    eventChange_ = containerFactory->createEventContainer();
    eventChange_->setDataProperty("type", "change");
    eventHandler_ = new DateTimePickerEventHandler(eventChange_);
    return NATIVE_ERROR_OK;
}

int NativeDateTimePickerObject::setValue(TiObject* obj)
{
    Handle<Value> value = obj->getValue();
    if ((value.IsEmpty()) || (!value->IsDate()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }

    QDateTime dateTime;
    ConversionHelper::V8ToNative::retrieveDate(value, dateTime);

    dateTimePicker_->setValue(dateTime);

    return NATIVE_ERROR_OK;
}

int NativeDateTimePickerObject::setMinDate(TiObject* obj)
{
    Handle<Value> value = obj->getValue();
    if ((value.IsEmpty()) || (!value->IsDate()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }

    QDateTime dateTime;
    ConversionHelper::V8ToNative::retrieveDate(value, dateTime);

    dateTimePicker_->setMinimum(dateTime);

    return NATIVE_ERROR_OK;
}

int NativeDateTimePickerObject::setMaxDate(TiObject* obj)
{
    Handle<Value> value = obj->getValue();
    if ((value.IsEmpty()) || (!value->IsDate()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }

    QDateTime dateTime;
    ConversionHelper::V8ToNative::retrieveDate(value, dateTime);

    dateTimePicker_->setMaximum(dateTime);
    return NATIVE_ERROR_OK;
}

int NativeDateTimePickerObject::setType(TiObject* obj)
{
    int value;
    int error = NativeControlObject::getInteger(obj, &value);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }

    //TODO: add picker type as a member, so that we can get it with getType
    switch (value)
    {
    case Ti::UI::PICKER_TYPE_DATE:
        dateTimePicker_->setMode(bb::cascades::DateTimePickerMode::Date);
        break;
    case Ti::UI::PICKER_TYPE_TIME:
        dateTimePicker_->setMode(bb::cascades::DateTimePickerMode::Time);
        break;
    case Ti::UI::PICKER_TYPE_DATE_AND_TIME:
        dateTimePicker_->setMode(bb::cascades::DateTimePickerMode::DateTime);
        break;
    case Ti::UI::PICKER_TYPE_PLAIN:
    case Ti::UI::PICKER_TYPE_COUNT_DOWN_TIMER:
        //for other (not supported by bb) values default to Date picker
        dateTimePicker_->setMode(bb::cascades::DateTimePickerMode::Date);
        break;
    default:
        Ti_DEBUG("Unknown value received:  ", value);
        return NATIVE_ERROR_NOTSUPPORTED;
    }

    return NATIVE_ERROR_OK;
}

int NativeDateTimePickerObject::getObjectType() const
{
    return N_TYPE_DATE_TIME_PICKER;
}

NAHANDLE NativeDateTimePickerObject::getNativeHandle() const
{
    return dateTimePicker_;
}

void NativeDateTimePickerObject::completeInitialization()
{
    NativeControlObject::completeInitialization();
    QObject::connect(dateTimePicker_, SIGNAL(valueChanged(QDateTime)), eventHandler_, SLOT(setValue(QDateTime)));
}

int NativeDateTimePickerObject::setEventHandler(const char* eventName, TiEvent* event)
{
    if (strcmp(eventName, "change") == 0)
    {
        if (eventChange_)
        {
            eventChange_->addListener(event);
        }
    }
    return NATIVE_ERROR_OK;
}
