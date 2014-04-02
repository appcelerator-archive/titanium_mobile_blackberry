/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUtils.h"
#include "V8Utils.h"
#include "Layout/ParseProperty.h"
#include <QString>
#include <bb/device/DisplayInfo>
#include <math.h>
#include <QColor>
#include "TiCore.h"

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
	return Ti::Layout::ParseProperty::getDimensionValue(str.toUtf8().constData(), ppi_);
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

// TiUtils::createProxyFromString("{title:'meh'};");
Handle<Value> TiUtils::createV8HandleFromString(QString _string)
{
	HandleScope scope;
	Handle<Script> script = Script::Compile(String::New(_string.toLocal8Bit().data()));
	return scope.Close(script->Run());
}

bb::cascades::Color TiUtils::colorFromTiObject(TiObject *obj)
{

    QString qcolorString = titanium::V8ValueToQString(obj->getValue());
    if (!QColor::isValidColor(qcolorString))
    {
        return bb::cascades::Color::Yellow;
    }
    QColor qcolor(qcolorString);
    qreal qr, qg, qb, qa;
    qcolor.getRgbF(&qr, &qg, &qb, &qa);
    float r = qr;
    float g = qg;
    float b = qb;
    float a = qa;

	return bb::cascades::Color::fromRGBA(r, g, b, a);

}
