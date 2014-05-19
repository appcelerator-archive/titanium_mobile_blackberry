/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiGeolocationSession.h"
#include "TiGeolocationModule.h"
static QMap<QString, float> _lastGeoloc;

QMap<QString, float> TiGeolocationSession::getLastGeoloc()
{
	return _lastGeoloc;
}

TiGeolocationSession::TiGeolocationSession(TiGeolocationModule* module) :
		_module(module)
{
	_source = QtMobilitySubset::QGeoPositionInfoSource::createDefaultSource(NULL);
	_source->setParent(this);
	QObject::connect(_source,
		            SIGNAL(positionUpdated(const QGeoPositionInfo &)),
		            this,
		            SLOT(onPositionUpdated(const QGeoPositionInfo &)));
	_source->startUpdates();
}
TiGeolocationSession::~TiGeolocationSession()
{
}

void TiGeolocationSession::setCallbackFunction(Ti::TiValue value)
{
	_callbackFunction = Ti::TiValue(value.toJSValue());
}

void TiGeolocationSession::setAccuracy(float acc)
{
	_source->setProperty( "accuracy", acc);
}
void TiGeolocationSession::setFrequency(int freq)
{
	_source->setUpdateInterval(freq);
}
void TiGeolocationSession::setPreferredProvider(QGeoPositionInfoSource::PositioningMethod method)
{
	_source->setPreferredPositioningMethods(method);
}

void TiGeolocationSession::onPositionUpdated(const QGeoPositionInfo & position)
{
	QtMobilitySubset::QGeoCoordinate coords = position.coordinate();

	Ti::TiEventParameters eventParams;

	eventParams.addParam("latitude", coords.latitude());
	eventParams.addParam("longitude", coords.longitude());
	eventParams.addParam("altitude", coords.altitude());
	eventParams.addParam("direction", position.attribute(QtMobilitySubset::QGeoPositionInfo::Direction));
	eventParams.addParam("speed", position.attribute(QtMobilitySubset::QGeoPositionInfo::GroundSpeed));
	eventParams.addParam("groundSpeed", position.attribute(QtMobilitySubset::QGeoPositionInfo::GroundSpeed));
	eventParams.addParam("verticalSpeed", position.attribute(QtMobilitySubset::QGeoPositionInfo::VerticalSpeed));
	eventParams.addParam("magneticVariation", position.attribute(QtMobilitySubset::QGeoPositionInfo::MagneticVariation));
	eventParams.addParam("heading", position.attribute(QtMobilitySubset::QGeoPositionInfo::MagneticVariation));
	eventParams.addParam("horizontalAccuracy", position.attribute(QtMobilitySubset::QGeoPositionInfo::HorizontalAccuracy));
	eventParams.addParam("verticalAccuracy", position.attribute(QtMobilitySubset::QGeoPositionInfo::VerticalAccuracy));
	eventParams.addParam("accuracy", position.attribute(QtMobilitySubset::QGeoPositionInfo::HorizontalAccuracy));
	eventParams.addParam("altitudeAccuracy", position.attribute(QtMobilitySubset::QGeoPositionInfo::VerticalAccuracy));
	eventParams.addParam("timestamp", (int)position.timestamp().currentMSecsSinceEpoch());

	_module->fireEvent("location", eventParams);

	_lastGeoloc.clear();
	_lastGeoloc.insert("latitude", (float)coords.latitude());
	_lastGeoloc.insert("longitude", (float)coords.longitude());
	_lastGeoloc.insert("altitude", (float)coords.altitude());
	_lastGeoloc.insert("direction", (float)position.attribute(QtMobilitySubset::QGeoPositionInfo::Direction));
	_lastGeoloc.insert("speed", (float)position.attribute(QtMobilitySubset::QGeoPositionInfo::GroundSpeed));
	_lastGeoloc.insert("groundSpeed", (float)position.attribute(QtMobilitySubset::QGeoPositionInfo::GroundSpeed));
	_lastGeoloc.insert("verticalSpeed", (float)position.attribute(QtMobilitySubset::QGeoPositionInfo::VerticalSpeed));
	_lastGeoloc.insert("magneticVariation", (float)position.attribute(QtMobilitySubset::QGeoPositionInfo::MagneticVariation));
	_lastGeoloc.insert("heading", (float)position.attribute(QtMobilitySubset::QGeoPositionInfo::MagneticVariation));
	_lastGeoloc.insert("horizontalAccuracy", (float)position.attribute(QtMobilitySubset::QGeoPositionInfo::HorizontalAccuracy));
	_lastGeoloc.insert("verticalAccuracy", (float)position.attribute(QtMobilitySubset::QGeoPositionInfo::VerticalAccuracy));
	_lastGeoloc.insert("accuracy", (float)position.attribute(QtMobilitySubset::QGeoPositionInfo::HorizontalAccuracy));
	_lastGeoloc.insert("altitudeAccuracy", (float)position.attribute(QtMobilitySubset::QGeoPositionInfo::VerticalAccuracy));
	_lastGeoloc.insert("timestamp", (float)position.timestamp().currentMSecsSinceEpoch());

	if(_callbackFunction.isValid())
	{
		_source->stopUpdates();
		_callbackFunction.callFunction(_module, _module->getLastGeolocation());
		deleteLater();
	}
}
