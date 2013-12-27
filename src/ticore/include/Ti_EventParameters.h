/*
 * TiEventParameters.h
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIEVENTPARAMETERS_H_
#define TI_TIEVENTPARAMETERS_H_

#include "Ti_Proxy.h"
#include <QString>
#include <QMap>
#include <v8.h>

using namespace v8;
namespace Ti
{
class TiRect;
class TiPoint;
class TiEventParameters {
public:
	TiEventParameters();
	virtual ~TiEventParameters();
	void addParam(QString, QString);
	void addParam(QString, int);
	void addParam(QString, double);
	void addParam(QString, TiProxy*);
	void addParam(QString, TiEventParameters);
	bool contains(QString);

	QString toJsonQString();

	static void addParametersToObject(Ti::TiEventParameters*, Handle<Object>);
private:
	QMap<QString, QString> stringMap;
	QMap<QString, double> numberMap;
	QMap<QString, Ti::TiProxy*> proxyMap;
	QMap<QString, TiEventParameters> objectMap;

};

class TiPoint
{
public:
	TiPoint(double x, double y);
	TiPoint();
	double getX();
	double getY();
	Handle<Object> getJSObject();
private:
	static Handle<Value> _toString(const Arguments& args);
	double _x;
	double _y;
};

class TiRect
{
public:
	TiRect(double width, double height, double x, double y);
	TiRect();
	TiPoint getPoint();
	double getWidth();
	double getHeight();
	double getX();
	double getY();
	Handle<Object> getJSObject();
private:
	static Handle<Value> _toString(const Arguments& args);
	double _x;
	double _y;
	double _width;
	double _height;
};

}
#endif /* TIEVENTPARAMETERS_H_ */
