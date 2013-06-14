/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUtils.h"
#include "Layout/ParseProperty.h"
#include <QString>
#include <bb/device/DisplayInfo>
#include <math.h>

static TiUtils* sharedInstance = NULL;

TiUtils::TiUtils()
{

	const float MMPERINCH = 25.4f;

	bb::device::DisplayInfo display;
	QSize pixelSize = display.pixelSize();
	QSizeF physicalSize = display.physicalSize();

	const float physicalWidth = physicalSize.width();
	const float physicalHeight = physicalSize.height();
	const float pixelWidth = pixelSize.width();
	const float pixelHeight = pixelSize.height();

	// Calculate pixels density
	const float diagonalWidth = sqrtf(physicalWidth * physicalWidth + physicalHeight * physicalHeight) / MMPERINCH;
	const float diagonalPixels = sqrtf(pixelWidth * pixelWidth + pixelHeight * pixelHeight);

	ppi_ = diagonalPixels / diagonalWidth;
}

TiUtils::~TiUtils()
{

}

float TiUtils::getPPI()
{
	return ppi_;
}

float TiUtils::getCalculatedDimension(QString str)
{
	return getDimensionValue(str.toUtf8().constData(), ppi_);
}

TiUtils* TiUtils::getInstance()
{
	if(sharedInstance == NULL)
		sharedInstance = new TiUtils();
	return sharedInstance;
}

int TiUtils::getDateTime(TiObject* obj, QDateTime& dt)
{
	return TiUtils::getDateTime(obj->getValue(), dt);
}

int TiUtils::getDateTime(Handle<Value> value, QDateTime& dt)
{
    if ((value.IsEmpty()) || (!value->IsDate()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }

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
    return NATIVE_ERROR_OK;
}

