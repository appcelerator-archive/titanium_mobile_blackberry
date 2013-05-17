/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeGeolocationObject.h"

#include <QtSensors/QCompass>
#include <QtSensors/QCompassReading>

#include "EventHandler.h"
#include "GeolocationSession.h"
#include "TiObject.h"

using namespace QtMobility;
using namespace titanium;

class CompassEventHandler : public EventHandler {
    Q_OBJECT

public:
    explicit CompassEventHandler(TiEventContainer* container)
      : EventHandler(container)
      , compass_(this) {
        connect(&compass_, SIGNAL(readingChanged()), SLOT(headingChanged()));
    }

    void enableUpdates(bool enable) {
        if (enable)
            compass_.start();
        else
            compass_.stop();
    }

private slots:
    void headingChanged() {
        HandleScope scope;

        QCompassReading* reading = compass_.reading();
        Local<Object> heading = Object::New();
        heading->Set(String::NewSymbol("accuracy"),
                     Number::New(reading->calibrationLevel()));
        heading->Set(String::NewSymbol("magneticHeading"),
                     Number::New(reading->azimuth()));

        TiEventContainer* container = getEventContainer();
        container->setV8ValueProperty("heading", heading);
        container->fireEvent();
    }

private:
    QCompass compass_;
};

#include "NativeGeolocationObject.moc"

static NativeGeolocationObject::PropertyInfo properties[] = {
    {
        N_GEOLOCATION_PROP_LOCATION_SERVICES_ENABLED,
        &NativeGeolocationObject::isLocationServicesEnabled,
        0
    }
};

static const int propertyCount = sizeof(properties) / sizeof(properties[0]);

NativeGeolocationObject::NativeGeolocationObject(TiObject* obj)
  : NativeProxyObject(obj)
  , PropertyDelegateBase<NativeGeolocationObject>(this, properties, propertyCount)
  , locationListenerCount_(0)
  , headingListenerCount_(0) {
}

int NativeGeolocationObject::setPropertyValue(size_t propertyNumber, TiObject* obj) {
    return setProperty(propertyNumber, obj);
}

int NativeGeolocationObject::getPropertyValue(size_t propertyNumber, TiObject* obj) {
    return getProperty(propertyNumber, obj);
}

int NativeGeolocationObject::setEventHandler(const char* eventName, TiEvent* event) {
    NativeProxyObject::setEventHandler(eventName, event);

    if (strcmp("location", eventName) == 0) {
        locationListenerCount_++;
        if (locationListenerCount_ == 1) {
            session_->enableUpdates(true);
        }
    } else if (strcmp("heading", eventName) == 0) {
        headingListenerCount_++;
        if (headingListenerCount_ == 1) {
            compass_->enableUpdates(true);
        }
    }
}

int NativeGeolocationObject::removeEventHandler(const char* eventName, int eventId) {
    NativeProxyObject::removeEventHandler(eventName, eventId);

    if (strcmp("location", eventName) == 0) {
        locationListenerCount_--;
        if (locationListenerCount_ == 0) {
            session_->enableUpdates(false);
        }
    } else if (strcmp("heading", eventName) == 0) {
        headingListenerCount_--;
        if (headingListenerCount_ == 0) {
            compass_->enableUpdates(false);
        }
    }
}

int NativeGeolocationObject::isLocationServicesEnabled(TiObject* value) {
    bool enabled = session_->isLocationServicesEnabled();
    value->setValue(Boolean::New(enabled));
    return NATIVE_ERROR_OK;
}

void NativeGeolocationObject::setupEvents(TiEventContainerFactory* containerFactory) {
    TiEventContainer* container;

    container = containerFactory->createEventContainer();
    container->setDataProperty("type", "location");
    session_.reset(new GeolocationSession(container));
    events_.insert("location", EventPairSmartPtr(container, session_.data()));

    container = containerFactory->createEventContainer();
    container->setDataProperty("type", "heading");
    compass_.reset(new CompassEventHandler(container));
    events_.insert("heading", EventPairSmartPtr(container, compass_.data()));
}

