/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiGeolocationModule.h"
#include "TiGeolocationSession.h"
#include "TiCompassSession.h"

static QList<TiGeolocationSession*> _geolocationSessions;
static QList<TiCompassSession*> _compassSessions;


TiGeolocationModule::TiGeolocationModule(const char* name) :
		Ti::TiModule(name),
		_accuracy(-1),
		_frequency(-1),
		_preferedProvider(QGeoPositionInfoSource::AllPositioningMethods)
{

	createPropertyGetter("hasCompass", _getHasCompass);
	createPropertyGetter("locationServicesEnabled", _getLocationServicesEnabled);
	createPropertyGetter("lastGeolocation", _getLastGeolocation);

	createPropertySetterGetter("accuracy", _setAccuracy,  _getAccuracy);
	createPropertySetterGetter("distanceFilter", _setDistanceFilter,  _getDistanceFilter);
	createPropertySetterGetter("frequency", _setFrequency,  _getFrequency);
	createPropertySetterGetter("headingFilter", _setHeadingFilter,  _getHeadingFilter);
	createPropertySetterGetter("locationServicesAuthorization", _setLocationServicesAuthorization,  _getLocationServicesAuthorization);
	createPropertySetterGetter("preferredProvider", _setPreferredProvider,  _getPreferredProvider);
	createPropertySetterGetter("purpose", _setPurpose,  _getPurpose);
	createPropertySetterGetter("showCalibration", _setShowCalibration,  _getShowCalibration);
	createPropertySetterGetter("trackSignificantLocationChange", _setTrackSignificantLocationChange,  _getTrackSignificantLocationChange);
	createPropertySetterGetter("activityType", _setActivityType,  _getActivityType);
	createPropertySetterGetter("pauseLocationUpdateAutomatically", _setPauseLocationUpdateAutomatically,  _getPauseLocationUpdateAutomatically);

	createPropertyFunction("forwardGeocoder", _forwardGeocoder);
	createPropertyFunction("getCurrentHeading", _getCurrentHeading);
	createPropertyFunction("getCurrentPosition", _getCurrentPosition);
	createPropertyFunction("reverseGeocoder", _reverseGeocoder);

	addNumber("ACCURACY_BEST", 0);
	addNumber("ACCURACY_HUNDRED_METERS", 100);
	addNumber("ACCURACY_KILOMETER", 1000);
	addNumber("ACCURACY_NEAREST_TEN_METERS", 10);
	addNumber("ACCURACY_THREE_KILOMETERS", 3000);
	addNumber("ACCURACY_HIGH", 0);
	addNumber("ACCURACY_BEST_FOR_NAVIGATION", 0);
	addNumber("ACCURACY_LOW", 1000);
	addNumber("AUTHORIZATION_AUTHORIZED", 0);
	addNumber("AUTHORIZATION_DENIED", 0);
	addNumber("AUTHORIZATION_RESTRICTED", 0);
	addNumber("AUTHORIZATION_UNKNOWN", 0);
	addNumber("ERROR_DENIED", 0);
	addNumber("ERROR_HEADING_FAILURE", 0);
	addNumber("ERROR_LOCATION_UNKNOWN", 0);
	addNumber("ERROR_NETWORK", 0);
	addNumber("ERROR_REGION_MONITORING_DELAYED", 0);
	addNumber("ERROR_REGION_MONITORING_DENIED", 0);
	addNumber("ERROR_REGION_MONITORING_FAILURE", 0);
	addNumber("ERROR_TIMEOUT", 0);
	addNumber("PROVIDER_GPS", QGeoPositionInfoSource::SatellitePositioningMethods);
	addNumber("PROVIDER_NETWORK", QGeoPositionInfoSource::NonSatellitePositioningMethods);
	addNumber("PROVIDER_PASSIVE", QGeoPositionInfoSource::AllPositioningMethods);
	addNumber("ACTIVITYTYPE_OTHER", 0);
	addNumber("ACTIVITYTYPE_AUTOMOTIVE_NAVIGATION", 0);
	addNumber("ACTIVITYTYPE_FITNESS", 0);
	addNumber("ACTIVITYTYPE_OTHER_NAVIGATION", 0);

}

TiGeolocationModule::~TiGeolocationModule()
{
}

void TiGeolocationModule::onEventAdded(QString eventName)
{
	if(eventName == "location") {
		TiGeolocationSession *session = new TiGeolocationSession(this);
		if(_accuracy != -1)
		{
			session->setAccuracy(_accuracy);
		}
		if(_frequency != -1)
		{
			session->setFrequency(_frequency);
		}
		session->setPreferredProvider(_preferedProvider);
		_geolocationSessions.append(session);
	}

	if(eventName == "heading") {
		TiCompassSession *session = new TiCompassSession(this);
		_compassSessions.append(session);
	}
	Ti::TiModule::onEventAdded(eventName);
}

void TiGeolocationModule::onEventRemoved(QString eventName)
{
	if(eventName == "location") {
		delete _geolocationSessions.last();
		_geolocationSessions.removeLast();
	}
	if(eventName == "heading") {
		delete _compassSessions.last();
		_compassSessions.removeLast();
	}
}

void TiGeolocationModule::setAccuracy(Ti::TiValue val)
{
	_accuracy = (float)val.toNumber();
	foreach(TiGeolocationSession *session, _geolocationSessions)
	{
		session->setAccuracy(_accuracy);
	}
}
void TiGeolocationModule::setDistanceFilter(Ti::TiValue val)
{
	setAccuracy(val);
}
void TiGeolocationModule::setFrequency(Ti::TiValue val)
{
	_frequency = (int)val.toNumber();
	foreach(TiGeolocationSession *session, _geolocationSessions)
	{
		session->setFrequency(_frequency);
	}
}
void TiGeolocationModule::setHeadingFilter(Ti::TiValue)
{
}
void TiGeolocationModule::setLocationServicesAuthorization(Ti::TiValue)
{
}
void TiGeolocationModule::setPreferredProvider(Ti::TiValue val)
{
	_preferedProvider = (QGeoPositionInfoSource::PositioningMethod)val.toNumber();
	foreach(TiGeolocationSession *session, _geolocationSessions)
	{
		session->setPreferredProvider(_preferedProvider);
	}
}
void TiGeolocationModule::setPurpose(Ti::TiValue)
{
}
void TiGeolocationModule::setShowCalibration(Ti::TiValue)
{
}
void TiGeolocationModule::setTrackSignificantLocationChange(Ti::TiValue)
{
}
void TiGeolocationModule::setActivityType(Ti::TiValue)
{
}
void TiGeolocationModule::setPauseLocationUpdateAutomatically(Ti::TiValue)
{
}


Ti::TiValue TiGeolocationModule::getAccuracy()
{
	Ti::TiValue val;
	val.setNumber(_accuracy);
	return val;
}
Ti::TiValue TiGeolocationModule::getDistanceFilter()
{
	return getAccuracy();
}
Ti::TiValue TiGeolocationModule::getFrequency()
{
	Ti::TiValue val;
	val.setNumber(_frequency);
	return val;
}
Ti::TiValue TiGeolocationModule::getHasCompass()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiGeolocationModule::getHeadingFilter()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiGeolocationModule::getLocationServicesAuthorization()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiGeolocationModule::getLocationServicesEnabled()
{
	QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(0);
	Ti::TiValue val;
	val.setBool(source->property("locationServicesEnabled").toBool());
	delete source;
	return val;
}
Ti::TiValue TiGeolocationModule::getPreferredProvider()
{
	Ti::TiValue val;
	val.setNumber(_preferedProvider);
	return val;
}
Ti::TiValue TiGeolocationModule::getPurpose()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiGeolocationModule::getShowCalibration()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiGeolocationModule::getTrackSignificantLocationChange()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiGeolocationModule::getActivityType()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiGeolocationModule::getPauseLocationUpdateAutomatically()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiGeolocationModule::getLastGeolocation()
{
	QMap<QString, Ti::TiValue> map;
	foreach(QString value, TiGeolocationSession::getLastGeoloc().keys())
	{
		Ti::TiValue current;
		current.setNumber(TiGeolocationSession::getLastGeoloc().value(value));
		map.insert(value, current);
	}
	Ti::TiValue val;
	val.setMap(map);
	return val;
}

Ti::TiValue TiGeolocationModule::forwardGeocoder(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiGeolocationModule::getCurrentHeading(Ti::TiValue value)
{
	if(value.isFunction())
	{
		TiCompassSession *session = new TiCompassSession(this);
		session->setCallbackFunction(value);
	}
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiGeolocationModule::getCurrentPosition(Ti::TiValue value)
{
	if(value.isFunction())
	{
		TiGeolocationSession *session = new TiGeolocationSession(this);
		session->setAccuracy(0);
		session->setFrequency(1);
		session->setPreferredProvider(_preferedProvider);
		session->setCallbackFunction(value);
	}

	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiGeolocationModule::reverseGeocoder(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
