/*
 * TiEventParameters.cpp
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "Ti_EventParameters.h"
#include "Ti_Helper.h"

Ti::TiEventParameters::TiEventParameters() {
	// TODO Auto-generated constructor stub

}

Ti::TiEventParameters::~TiEventParameters() {
	// Ti::TiHelper::Log("Ti::TiEventParameters destroyed!");
}

bool Ti::TiEventParameters::contains(QString key)
{
	return stringMap.contains(key) ||
			numberMap.contains(key) ||
			proxyMap.contains(key) ||
			objectMap.contains(key);

}
void Ti::TiEventParameters::addParam(QString key, QString value)
{
	stringMap[key] = value;
}
void Ti::TiEventParameters::addParam(QString key, int value)
{
	numberMap[key] = (double)value;
}
void Ti::TiEventParameters::addParam(QString key, double value)
{
	numberMap[key] = value;
}
void Ti::TiEventParameters::addParam(QString key, Ti::TiProxy* value)
{
	proxyMap[key] = value;
}

void Ti::TiEventParameters::addParam(QString key, TiEventParameters value)
{
	objectMap[key] = value;
}

QString Ti::TiEventParameters::toJsonQString()
{
	QString json = "{";

	foreach(QString key, stringMap.keys())
	{
		// "key":"value",
		json.append("\"").append(key).append("\":\"").append(stringMap[key]).append("\",");
	}

	foreach(QString key, numberMap.keys())
	{
		// "key":"value",
		json.append("\"").append(key).append("\":\"").append(QString::number(numberMap[key])).append("\",");
	}

	foreach(QString key, proxyMap.keys())
	{
		json.append("\"").append(key).append("\":\"").append(proxyMap[key]->getProxyName()).append("\",");
	}

	foreach(QString key, objectMap.keys())
	{
		json.append("\"").append(key).append("\":").append(
				objectMap[key].toJsonQString()
		).append(",");
	}

	/*
	foreach(QString key, arrayMap.keys())
	{
		json.append("\"").append(key).append("\":");
		json.append("[");
		foreach(TiEventParameters params, arrayMap[key])
		{
			json.append(params.toJsonQString()).append(",");
		}
		if(json.endsWith(","))
		{
			json.chop(1);
		}
		json.append("],");
	}
	*/
	if(json.endsWith(","))
	{
		json.chop(1);
	}
	json.append("}");

	qDebug() << "[TiEventParameters]" << json;

	return json;
}

void Ti::TiEventParameters::addParametersToObject(Ti::TiEventParameters* parameters, Handle<Object> object)
{

	foreach(QString key, parameters->stringMap.keys())
	{
		object->Set(Ti::TiHelper::ValueFromQString(key), String::New(Ti::TiHelper::QStringToChar(parameters->stringMap[key])));
	}

	foreach(QString key, parameters->numberMap.keys())
	{
		object->Set(Ti::TiHelper::ValueFromQString(key), Number::New(parameters->numberMap[key]));
	}

	foreach(QString key, parameters->proxyMap.keys())
	{
		object->Set(Ti::TiHelper::ValueFromQString(key), parameters->proxyMap[key]->_jsObject);
	}

	foreach(QString key, parameters->objectMap.keys())
	{
		Handle<Object> newObject = Object::New();
		addParametersToObject(&parameters->objectMap[key], newObject);
		object->Set(Ti::TiHelper::ValueFromQString(key), newObject);
	}

}

Ti::TiPoint::TiPoint(double x, double y)
{
	_x = x;
	_y = y;
}
Ti::TiPoint::TiPoint() :
		_x(-1),
		_y(-1)
{

}
double Ti::TiPoint::getX(){
	return _x;
}
double Ti::TiPoint::getY()
{
	return _y;
}

Handle<Object> Ti::TiPoint::getJSObject()
{
	HandleScope scope;
	Handle<Object> obj = Object::New();
	obj->Set(String::New("toString"), FunctionTemplate::New(Ti::TiPoint::_toString)->GetFunction());
	obj->Set(String::New("x"), Number::New(_x));
	obj->Set(String::New("y"), Number::New(_y));
	return obj;
}
Handle<Value> Ti::TiPoint::_toString(const Arguments&)
{
	HandleScope scope;
	return String::New("[object TiPoint]");
}

Ti::TiRect::TiRect(double width, double height, double x, double y)
{
	_width = width;
	_height = height;
	_y = y;
	_x = x;
}
Ti::TiRect::TiRect() :
		_x(-1),
		_y(-1),
		_width(-1),
		_height(-1)
{

}
Handle<Object> Ti::TiRect::getJSObject()
{
	HandleScope scope;
	Handle<Object> obj = Object::New();
	obj->Set(String::New("toString"), FunctionTemplate::New(Ti::TiRect::_toString)->GetFunction());
	obj->Set(String::New("x"), Number::New(_x));
	obj->Set(String::New("y"), Number::New(_y));
	obj->Set(String::New("width"), Number::New(_width));
	obj->Set(String::New("height"), Number::New(_height));
	return obj;
}
Handle<Value> Ti::TiRect::_toString(const Arguments&)
{
	HandleScope scope;
	return String::New("[object TiRect]");
}

Ti::TiPoint Ti::TiRect::getPoint()
{
	return Ti::TiPoint(_x, _y);
}
double Ti::TiRect::getWidth()
{
	return _width;
}
double Ti::TiRect::getHeight()
{
	return _height;
}
double Ti::TiRect::getX()
{
	return _x;
}
double Ti::TiRect::getY()
{
	return _y;
}

