/*
 * TiHelper.cpp
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "Ti_Helper.h"

#include <bb/system/SystemDialog>
#include <iostream>

Handle<Value> Ti::TiHelper::Log(const Arguments &args)
{
    HandleScope scope;
    if(args.Length() > 0)
    {
    	Ti::TiHelper::Log(args[0]);
    }
    return scope.Close(Undefined());

}

void Ti::TiHelper::Log(QString str)
{
    std::cout << "[INFO] " << str.toLocal8Bit().data() << std::endl;

}

Handle<Value> Ti::TiHelper::Log(Handle<Value> arg)
{
    std::cout << "[INFO] " << *String::Utf8Value(arg) << std::endl;
    return Undefined();
}

Handle<Value> Ti::TiHelper::Alert(const Arguments &args)
{
    HandleScope scope;
    if(args.Length() > 0)
    {
    	bb::system::SystemDialog* alert = new bb::system::SystemDialog("OK");
    	alert->setTitle(QString("Alert"));
    	alert->setBody(QString(*String::Utf8Value(args[0])));
    	alert->show();
//    	alert->deleteLater();
    }
    return scope.Close(Undefined());

}

char* Ti::TiHelper::QStringToChar(QString str)
{
	return str.toLocal8Bit().data();
}

Handle<Value> Ti::TiHelper::ValueFromQString(QString str)
{
	return String::New(str.toLocal8Bit().constData());
}

QString Ti::TiHelper::QStringFromValue(Handle<Value> val)
{
	String::Utf8Value value(val);
	return QString(*value);
}

float Ti::TiHelper::FloatFromValue(Handle<Value> val)
{
	if(!val->IsNumber())
		return 0;
	Local<Number> num = val->ToNumber();
	return (float)num->Value();
}

bb::cascades::Color Ti::TiHelper::ColorFromObject(Handle<Value> obj)
{

    QString qcolorString = Ti::TiHelper::QStringFromValue(obj);
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
