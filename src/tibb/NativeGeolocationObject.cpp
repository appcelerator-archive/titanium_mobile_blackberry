/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeGeolocationObject.h"

#include "GeolocationSession.h"
#include "TiObject.h"

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
  , locationListenerCount_(0) {
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
    }
}

int NativeGeolocationObject::removeEventHandler(const char* eventName, int eventId) {
    NativeProxyObject::removeEventHandler(eventName, eventId);

    if (strcmp("location", eventName) == 0) {
        locationListenerCount_--;
        if (locationListenerCount_ == 0) {
            session_->enableUpdates(false);
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
}

