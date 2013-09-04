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
class TiEventParameters {
public:
	TiEventParameters();
	virtual ~TiEventParameters();
	void addParam(QString, QString);
	void addParam(QString, int);
	void addParam(QString, double);
	void addParam(QString, TiProxy*);

	static void addParametersToObject(Ti::TiEventParameters*, Handle<Object>);
private:
	QMap<QString, QString> stringMap;
	QMap<QString, double> numberMap;
	QMap<QString, Ti::TiProxy*> proxyMap;

};
}
#endif /* TIEVENTPARAMETERS_H_ */
