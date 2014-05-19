/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIGEOLOCATIONSESSION_H_
#define TIGEOLOCATIONSESSION_H_

#include <TiCore.h>
#include <QObject>
#include <QtLocationSubset/QGeoPositionInfo>
#include <QtLocationSubset/QGeoPositionInfoSource>
using namespace QtMobilitySubset;

class TiGeolocationModule;
class TiGeolocationSession : public QObject
{
	Q_OBJECT;
public:
	TiGeolocationSession(TiGeolocationModule* module);
	virtual ~TiGeolocationSession();
	void setAccuracy(float);
	void setFrequency(int);
	void setPreferredProvider(QGeoPositionInfoSource::PositioningMethod);
	void setCallbackFunction(Ti::TiValue);
	static QMap<QString, float> getLastGeoloc();

public slots:
	void onPositionUpdated(const QGeoPositionInfo &);

private:
	TiGeolocationModule* _module;
	QGeoPositionInfoSource *_source;
	Ti::TiValue _callbackFunction;
};

#endif /* TIGEOLOCATIONSESSION_H_ */
