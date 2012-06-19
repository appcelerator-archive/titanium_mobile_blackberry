/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "ConversionHelper.h"

#include "TiObject.h"

void ConversionHelper::V8ToNative::
retrieveDate(v8::Handle<v8::Value>& value, QDateTime& dt)
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
