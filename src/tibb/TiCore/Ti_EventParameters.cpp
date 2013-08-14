/*
 * TiEventParameters.cpp
 *
 *  Created on: Jul 13, 2013
 *      Author: penrique
 */

#include "Ti_EventParameters.h"
#include "Ti_Helper.h"

Ti::TiEventParameters::TiEventParameters() {
	// TODO Auto-generated constructor stub

}

Ti::TiEventParameters::~TiEventParameters() {
	// Ti::TiHelper::Log("Ti::TiEventParameters destroyed!");
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

void Ti::TiEventParameters::addParametersToObject(Ti::TiEventParameters* parameters, Handle<Object> object)
{
	QMap<QString, QString> stringMap = parameters->stringMap;
	QMap<QString, double> numberMap = parameters->numberMap;
	QMap<QString, Ti::TiProxy*> proxyMap = parameters->proxyMap;

	foreach(QString key, stringMap.keys())
	{
		object->Set(Ti::TiHelper::ValueFromQString(key), String::New(Ti::TiHelper::QStringToChar(stringMap[key])));
	}

	foreach(QString key, numberMap.keys())
	{
		object->Set(Ti::TiHelper::ValueFromQString(key), Number::New(numberMap[key]));
	}

	foreach(QString key, proxyMap.keys())
	{
		object->Set(Ti::TiHelper::ValueFromQString(key), proxyMap[key]->realJSObject);
	}

}
