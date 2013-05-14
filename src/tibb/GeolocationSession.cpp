/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "GeolocationSession.h"

#include <QVariant>

#include <v8.h>

#include "TiEventContainer.h"

using namespace QtMobilitySubset;
using namespace v8;

GeolocationSession::GeolocationSession(TiEventContainer* container)
  : source_(QGeoPositionInfoSource::createDefaultSource(this))
  , container_(container) {
    Q_ASSERT(source_);
    connect(source_,
            SIGNAL(positionUpdated(const QGeoPositionInfo &)),
            SLOT(positionUpdated(const QGeoPositionInfo &)));
}

void GeolocationSession::enableUpdates(bool enable) {
    if (enable) {
        source_->startUpdates();
    } else {
        source_->stopUpdates();
    }
}

bool GeolocationSession::isLocationServicesEnabled() const {
    return source_->property("locationServicesEnabled").toBool();
}

void GeolocationSession::positionUpdated(const QGeoPositionInfo& update) {
    HandleScope scope;

    Local<Object> coords = Object::New();
    QGeoCoordinate coord = update.coordinate();
    coords->Set(String::NewSymbol("latitude"), Number::New(coord.latitude()));
    coords->Set(String::NewSymbol("longitude"), Number::New(coord.longitude()));

    container_->setV8ValueProperty("coords", coords);
    container_->fireEvent();
}

void GeolocationSession::updateTimeout() {
}

