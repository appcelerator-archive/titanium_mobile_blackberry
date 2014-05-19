/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TICOMPASSSESSION_H_
#define TICOMPASSSESSION_H_

#include <QObject>
#include <QtSensors/QCompass>
#include <TiCore.h>

using namespace QtMobility;

class TiGeolocationModule;
class TiCompassSession : public QObject
{
	Q_OBJECT;
public:
	TiCompassSession(TiGeolocationModule*);
	virtual ~TiCompassSession();
	void setCallbackFunction(Ti::TiValue);
public slots:
	void onReadingChanged();
private:
	QCompass* _compass;
	TiGeolocationModule *_module;
	Ti::TiValue _callbackFunction;
};

#endif /* TICOMPASSSESSION_H_ */
