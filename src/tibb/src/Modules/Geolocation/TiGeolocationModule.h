/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIGEOLOCATIONMODULE_H_
#define TIGEOLOCATIONMODULE_H_

#include <TiCore.h>
#include <QtLocationSubset/QGeoPositionInfo>
#include <QtLocationSubset/QGeoPositionInfoSource>
using namespace QtMobilitySubset;

class TiGeolocationSession;
class TiGeolocationModule : public Ti::TiModule
{

public:
	CREATE_MODULE(TiGeolocationModule)
	TiGeolocationModule(const char*);
	virtual ~TiGeolocationModule();

	virtual void onEventAdded(QString);
	virtual void onEventRemoved(QString);

	void setAccuracy(Ti::TiValue);
	void setDistanceFilter(Ti::TiValue);
	void setFrequency(Ti::TiValue);
	void setHeadingFilter(Ti::TiValue);
	void setLocationServicesAuthorization(Ti::TiValue);
	void setPreferredProvider(Ti::TiValue);
	void setPurpose(Ti::TiValue);
	void setShowCalibration(Ti::TiValue);
	void setTrackSignificantLocationChange(Ti::TiValue);
	void setActivityType(Ti::TiValue);
	void setPauseLocationUpdateAutomatically(Ti::TiValue);

	Ti::TiValue getAccuracy();
	Ti::TiValue getDistanceFilter();
	Ti::TiValue getFrequency();
	Ti::TiValue getHasCompass();
	Ti::TiValue getHeadingFilter();
	Ti::TiValue getLocationServicesAuthorization();
	Ti::TiValue getLocationServicesEnabled();
	Ti::TiValue getPreferredProvider();
	Ti::TiValue getPurpose();
	Ti::TiValue getShowCalibration();
	Ti::TiValue getTrackSignificantLocationChange();
	Ti::TiValue getActivityType();
	Ti::TiValue getPauseLocationUpdateAutomatically();
	Ti::TiValue getLastGeolocation();

	Ti::TiValue forwardGeocoder(Ti::TiValue);
	Ti::TiValue getCurrentHeading(Ti::TiValue);
	Ti::TiValue getCurrentPosition(Ti::TiValue);
	Ti::TiValue reverseGeocoder(Ti::TiValue);


	EXPOSE_SETTER(TiGeolocationModule, setAccuracy)
	EXPOSE_SETTER(TiGeolocationModule, setDistanceFilter)
	EXPOSE_SETTER(TiGeolocationModule, setFrequency)
	EXPOSE_SETTER(TiGeolocationModule, setHeadingFilter)
	EXPOSE_SETTER(TiGeolocationModule, setLocationServicesAuthorization)
	EXPOSE_SETTER(TiGeolocationModule, setPreferredProvider)
	EXPOSE_SETTER(TiGeolocationModule, setPurpose)
	EXPOSE_SETTER(TiGeolocationModule, setShowCalibration)
	EXPOSE_SETTER(TiGeolocationModule, setTrackSignificantLocationChange)
	EXPOSE_SETTER(TiGeolocationModule, setActivityType)
	EXPOSE_SETTER(TiGeolocationModule, setPauseLocationUpdateAutomatically)

	EXPOSE_GETTER(TiGeolocationModule, getAccuracy)
	EXPOSE_GETTER(TiGeolocationModule, getDistanceFilter)
	EXPOSE_GETTER(TiGeolocationModule, getFrequency)
	EXPOSE_GETTER(TiGeolocationModule, getHasCompass)
	EXPOSE_GETTER(TiGeolocationModule, getHeadingFilter)
	EXPOSE_GETTER(TiGeolocationModule, getLocationServicesAuthorization)
	EXPOSE_GETTER(TiGeolocationModule, getLocationServicesEnabled)
	EXPOSE_GETTER(TiGeolocationModule, getPreferredProvider)
	EXPOSE_GETTER(TiGeolocationModule, getPurpose)
	EXPOSE_GETTER(TiGeolocationModule, getShowCalibration)
	EXPOSE_GETTER(TiGeolocationModule, getTrackSignificantLocationChange)
	EXPOSE_GETTER(TiGeolocationModule, getActivityType)
	EXPOSE_GETTER(TiGeolocationModule, getPauseLocationUpdateAutomatically)
	EXPOSE_GETTER(TiGeolocationModule, getLastGeolocation)

	EXPOSE_METHOD(TiGeolocationModule, forwardGeocoder)
	EXPOSE_METHOD(TiGeolocationModule, getCurrentHeading)
	EXPOSE_METHOD(TiGeolocationModule, getCurrentPosition)
	EXPOSE_METHOD(TiGeolocationModule, reverseGeocoder)
private:
	float _accuracy;
	int _frequency;
	QGeoPositionInfoSource::PositioningMethod _preferedProvider;
};

#endif /* TIGEOLOCATIONMODULE_H_ */
