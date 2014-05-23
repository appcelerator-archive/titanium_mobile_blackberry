/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeAccelerometerObject.h"

#include <QtSensors/QAccelerometer>

#include "EventHandler.h"
#include "TiEventContainer.h"
#include "TiEventContainerFactory.h"

using namespace titanium;
using namespace QtMobility;

class AccelerometerEventHandler : public EventHandler {
    Q_OBJECT

public:
    explicit AccelerometerEventHandler(TiEventContainer* container)
      : EventHandler(container) {
        connect(&sensor_, SIGNAL(readingChanged()), SLOT(readingChanged()));

        sensor_.setAccelerationMode(QAccelerometer::User);
    }

    void enable(bool on) {
        if (on)
            sensor_.start();
        else
            sensor_.stop();
    }

private slots:
    void readingChanged() {
        QAccelerometerReading* reading = sensor_.reading();

        TiEventContainer* container = getEventContainer();
        container->setDataProperty("x", (float) reading->x());
        container->setDataProperty("y", (float) reading->y());
        container->setDataProperty("z", (float) reading->z());
        container->fireEvent();
    }

private:
    QAccelerometer sensor_;
};

#include "NativeAccelerometerObject.moc"

NativeAccelerometerObject::NativeAccelerometerObject(TiObject* obj)
  : NativeProxyObject(obj)
  , listenerCount_(0) {
}

NativeAccelerometerObject::~NativeAccelerometerObject() {
}

int NativeAccelerometerObject::setEventHandler(const char* eventName, TiEvent* event) {
    NativeProxyObject::setEventHandler(eventName, event);

    if (strcmp("update", eventName) == 0) {
        listenerCount_++;
        if (listenerCount_ == 1) {
            accelerometerHandler_->enable(true);
        }
    }
}

int NativeAccelerometerObject::removeEventHandler(const char* eventName, int eventId) {
    NativeProxyObject::removeEventHandler(eventName, eventId);

    if (strcmp("update", eventName) == 0) {
        listenerCount_--;
        if (listenerCount_ == 0) {
            accelerometerHandler_->enable(false);
        }
    }
}

void NativeAccelerometerObject::setupEvents(TiEventContainerFactory* containerFactory) {
    TiEventContainer* container = containerFactory->createEventContainer();
    container->setDataProperty("type", "update");
    accelerometerHandler_ = new AccelerometerEventHandler(container);
    events_.insert("update", EventPairSmartPtr(container, accelerometerHandler_));
}

