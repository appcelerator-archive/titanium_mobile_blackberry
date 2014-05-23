/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiCompassSession.h"
#include "TiGeolocationModule.h"
#include <QtSensors/QCompassReading>

TiCompassSession::TiCompassSession(TiGeolocationModule* module) : _module(module) {

	_compass = new QCompass(this);
	_compass->setAxesOrientationMode(QCompass::FixedOrientation);

	QObject::connect(_compass,
						SIGNAL(readingChanged()),
						this,
						SLOT(onReadingChanged()));
	_compass->start();

}

TiCompassSession::~TiCompassSession() {
	// TODO Auto-generated destructor stub
}

void TiCompassSession::setCallbackFunction(Ti::TiValue value)
{
	_callbackFunction = Ti::TiValue(value.toJSValue());
}

void TiCompassSession::onReadingChanged()
{
	QCompassReading *reading = _compass->reading();
	Ti::TiEventParameters eventParams;
	eventParams.addParam("heading", (int)reading->azimuth());
	eventParams.addParam("calibration", (int)reading->calibrationLevel());
	_module->fireEvent("heading", eventParams);
	if(_callbackFunction.isValid())
	{
		_compass->stop();
		Ti::TiValue headingValue;
		headingValue.setNumber((int)reading->azimuth());

		Ti::TiValue calibrationValue;
		calibrationValue.setNumber((int)reading->calibrationLevel());

		QMap<QString, Ti::TiValue> map;
		map.insert("heading", headingValue);
		map.insert("calibration", calibrationValue);

		Ti::TiValue val;
		val.setMap(map);

		_callbackFunction.callFunction(_module, val);
		deleteLater();
	}
}
