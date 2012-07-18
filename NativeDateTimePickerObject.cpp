/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeDateTimePickerObject.h"

#include "NativeLoggerObject.h"
#include "NativeMessageStrings.h"
#include "TiConstants.h"
#include "TiEventContainerFactory.h"
#include <bb/cascades/DateTimePicker>
#include <QDateTime>

NativeDateTimePickerObject::NativeDateTimePickerObject() :
    dateTimePicker_(NULL),
    left_(0),
    top_(0)
{
}

NativeDateTimePickerObject::~NativeDateTimePickerObject()
{
    delete dateTimePicker_;
    dateTimePicker_ = NULL;
}

NativeDateTimePickerObject* NativeDateTimePickerObject::createDateTimePicker()
{
    return new NativeDateTimePickerObject;
}

int NativeDateTimePickerObject::initialize(TiEventContainerFactory* containerFactory)
{
    dateTimePicker_ = bb::cascades::DateTimePicker::create();
    setControl(dateTimePicker_);
    TiEventContainer* eventChange = containerFactory->createEventContainer();
    eventChange->setDataProperty("type", tetCHANGE);
    events_.insert(tetCHANGE, new EventPair(eventChange, new DateTimePickerEventHandler(eventChange)));
    QObject::connect(dateTimePicker_, SIGNAL(valueChanged(QDateTime)), events_[tetCHANGE]->handler, SLOT(setValue(QDateTime)));
    return NATIVE_ERROR_OK;
}

int NativeDateTimePickerObject::setValue(TiObject* obj)
{
    QDateTime dateTime;
    int error = NativeControlObject::getDateTime(obj, dateTime);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    dateTimePicker_->setValue(dateTime);
    return NATIVE_ERROR_OK;
}

int NativeDateTimePickerObject::setMinDate(TiObject* obj)
{
    QDateTime dateTime;
    int error = NativeControlObject::getDateTime(obj, dateTime);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    dateTimePicker_->setMinimum(dateTime);
    return NATIVE_ERROR_OK;
}

int NativeDateTimePickerObject::setMaxDate(TiObject* obj)
{
    QDateTime dateTime;
    int error = NativeControlObject::getDateTime(obj, dateTime);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }

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
        N_DEBUG(Native::Msg::Unknown_value_received << ": " << value);
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
