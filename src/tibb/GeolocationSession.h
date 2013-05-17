/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_GEOLOCATION_SESSION_H
#define TI_GEOLOCATION_SESSION_H

#include <QObject>

#include <QtLocationSubset/QGeoPositionInfo>
#include <QtLocationSubset/QGeoPositionInfoSource>

using namespace QtMobilitySubset;

class TiEventContainer;

class GeolocationSession : public QObject {
    Q_OBJECT

public:
    GeolocationSession(TiEventContainer* container);

    void enableUpdates(bool enable);

    bool isLocationServicesEnabled() const;

private slots:
    void positionUpdated(const QGeoPositionInfo& update);
    void updateTimeout();

private:
    QtMobilitySubset::QGeoPositionInfoSource* source_;
    TiEventContainer* container_;
};

#endif
