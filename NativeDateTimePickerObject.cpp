/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/DateTimePIcker>
#include <qdatetime.h>
#include "NativeDateTimePickerObject.h"
#include "TiConstants.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"

NativeDateTimePickerObject::NativeDateTimePickerObject()
{
    dateTimePicker_ = NULL;
    top_ = 0;
    left_ = 0;
}

NativeDateTimePickerObject::~NativeDateTimePickerObject()
{
}

NativeDateTimePickerObject* NativeDateTimePickerObject::createDateTimePicker()
{
    return new NativeDateTimePickerObject;
}

int NativeDateTimePickerObject::initialize(TiEventContainerFactory* containerFactory)
{
    dateTimePicker_ = bb::cascades::DateTimePicker::create();
    eventChange_ = containerFactory->createEventContainer();
    eventChange_->setDataProperty("type", "change");
    eventHandler_ = new DateTimePickerEventHandler(eventChange_);
    return NATIVE_ERROR_OK;
}

int NativeDateTimePickerObject::setWidth(TiObject* obj)
{
    float width;
    int error = NativeControlObject::getFloat(obj, &width);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    dateTimePicker_->setMaxWidth(width);
    dateTimePicker_->setMinWidth(width);
    return NATIVE_ERROR_OK;
}

int NativeDateTimePickerObject::setLeft(TiObject* obj)
{
    bb::cascades::AbsoluteLayoutProperties* pProp = new bb::cascades::AbsoluteLayoutProperties;
    float left;
    int error = NativeControlObject::getFloat(obj, &left);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    left_ = left;
    pProp->setPositionX(left_);
    pProp->setPositionY(top_);
    dateTimePicker_->setLayoutProperties(pProp);
    return NATIVE_ERROR_OK;
}

int NativeDateTimePickerObject::setTop(TiObject* obj)
{
    bb::cascades::AbsoluteLayoutProperties* pProp = new bb::cascades::AbsoluteLayoutProperties;
    float top;
    int error = NativeControlObject::getFloat(obj, &top);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    top_ = top;
    pProp->setPositionX(left_);
    pProp->setPositionY(top_);
    dateTimePicker_->setLayoutProperties(pProp);
    return NATIVE_ERROR_OK;
}

void NativeDateTimePickerObject::retrieveDate(Handle<Value>& value, QDateTime& dt)
{
   unsigned int year = 0, month = 0, day = 0;

   Local<Object> object = Object::Cast(*value);

   // Get year from date
   Local<Value> getYear_prop = (object->Get(String::New("getFullYear")));
   if (getYear_prop->IsFunction())
   {
      Local<Function> getYear_func = Function::Cast(*getYear_prop);
      Local<Value> yearValue = getYear_func->Call(object, 0, NULL);
      year = yearValue->NumberValue();
   }

   // Get month from date
   Local<Value> getMonth_prop = (object->Get(String::New("getMonth")));
   if (getMonth_prop->IsFunction())
   {
      Local<Function> getMonth_func = Function::Cast(*getMonth_prop);
      Local<Value> monthValue = getMonth_func->Call(object, 0, NULL);
      month = monthValue->NumberValue();
   }

   // Get day property
   Local<Value> getDay_prop = (object->Get(String::New("getDate")));
   if (getDay_prop->IsFunction())
   {
      Local<Function> getDay_func = Function::Cast(*getDay_prop);
      Local<Value> dayValue = getDay_func->Call(object, 0, NULL);
      day = dayValue->NumberValue();
   }

   dt.setDate(QDate(year, month, day));
}

int NativeDateTimePickerObject::setValue(TiObject* obj)
{
   Handle<Value> value = obj->getValue();
   if ((value.IsEmpty()) || (!value->IsDate()))
   {
       return NATIVE_ERROR_INVALID_ARG;
   }

   QDateTime dateTime;
   retrieveDate(value, dateTime);

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
   retrieveDate(value, dateTime);

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
   retrieveDate(value, dateTime);

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
    	//for other (not supported by bb) values default to Date and Time picker
        dateTimePicker_->setMode(bb::cascades::DateTimePickerMode::DateTime);
    	break;
    default:
        Ti_DEBUG("Unknown value received:  ", value);
        break;
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
    QObject::connect(dateTimePicker_, SIGNAL(valueChanged(QDateTime)), eventHandler_, SLOT(valueChanged(QDateTime)));
}

int NativeDateTimePickerObject::setEventHandler(const char* eventName, TiEvent* event)
{
    if (strcmp(eventName, "change") == 0)
    {
    	eventChange_->addListener(event);
    }
    return NATIVE_ERROR_OK;
}
