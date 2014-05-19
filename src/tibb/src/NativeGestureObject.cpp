/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeGestureObject.h"

#include <bb/device/DeviceInfo>
#include <bb/device/DisplayInfo>

#include <QDateTime>
#include <QtSensors/QAccelerometer>
#include <QtSensors/QAccelerometerFilter>
#include <QtSensors/QAccelerometerReading>

#include "EventHandler.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "TiOrientation.h"

using namespace bb::device;
using namespace titanium;
using namespace QtMobility;

static NativeGestureObject::PropertyInfo properties[] = {
    { N_GESTURE_PROP_ORIENTATION, &NativeGestureObject::getOrientation, 0}
};
static const int propertyCount = sizeof(properties) / sizeof(properties[0]);

class GestureEventHandler : public EventHandler {
    Q_OBJECT

public:
    explicit GestureEventHandler(TiEventContainer* container)
      : EventHandler(container) {
        DisplayInfo displayInfo;
        aspectType_ = displayInfo.aspectType();

        connect(&deviceInfo_,
                SIGNAL(orientationChanged(bb::device::DeviceOrientation::Type)),
                SLOT(orientationChanged(bb::device::DeviceOrientation::Type)));
    }

private slots:
    void orientationChanged(bb::device::DeviceOrientation::Type orientation) {
        TiEventContainer* container = getEventContainer();
        container->setDataProperty("orientation",
                                   Orientation::fromDevice(orientation));
        container->fireEvent();
    }

private:
    DeviceInfo deviceInfo_;
    DisplayAspectType::Type aspectType_;
};

class ShakeEventHandler : public EventHandler,
                          public QAccelerometerFilter {
    Q_OBJECT

public:
    enum Sensitivity {
        Low = 20,
        Medium = 30,
        High = 40
    };

    // Create a shake event handler with a default
    // sensitivity of Medium and interval of 500 ms.
    explicit ShakeEventHandler(TiEventContainer* container)
      : EventHandler(container)
      , sensitivity_(Medium)
      , interval_(500)
      , lastShake_(0) {
        connect(&sensor_, SIGNAL(readingChanged()), SLOT(shake()));

        sensor_.setAccelerationMode(QAccelerometer::User);
        sensor_.addFilter(this);
    }

    void enable(bool on) {
        if (on)
            sensor_.start();
        else
            sensor_.stop();
    }

    void setSensitivity(Sensitivity sensitivity) {
        sensitivity_ = sensitivity;
    }

    void setInterval(qint64 interval) {
        interval_ = interval;
    }

    virtual bool filter(QAccelerometerReading* reading) {
        // Compute the time since the last shake event.
        qint64 now = QDateTime::currentMSecsSinceEpoch(),
               diff = now - lastShake_;

        // Compute how much force the device was shaken.
        // Note the force value is left squared.
        float x = reading->x(),
              y = reading->y(),
              z = reading->z(),
              force = (x * x) + (y * y) + (z * z);

        // If user shakes the device with enough force
        // and the interval of time between shake events
        // has been reached we will fire a shake event.
        if (force > (sensitivity_ * sensitivity_) && diff > interval_) {
            lastShake_ = now;
            return true;
        }

        return false;
    }

private slots:
    // A shake was detected and a new sensor reading is ready.
    void shake() {
        QAccelerometerReading* reading = sensor_.reading();

        TiEventContainer* container = getEventContainer();
        container->setDataProperty("x", (float) reading->x());
        container->setDataProperty("y", (float) reading->y());
        container->setDataProperty("z", (float) reading->z());
        container->fireEvent();
    }

private:
    float sensitivity_;
    qint64 interval_;
    qint64 lastShake_;
    QAccelerometer sensor_;
};

#include "NativeGestureObject.moc"

NativeGestureObject::NativeGestureObject(TiObject* obj)
  : NativeProxyObject(obj)
  , PropertyDelegateBase<NativeGestureObject>(this, properties, propertyCount)
  , shakeListenerCount_(0) {
}

NativeGestureObject* NativeGestureObject::createGesture(TiObject* obj) {
    return new NativeGestureObject(obj);
}

int NativeGestureObject::setPropertyValue(size_t propertyNumber, TiObject* obj) {
    return setProperty(propertyNumber, obj);
}

int NativeGestureObject::getPropertyValue(size_t propertyNumber, TiObject* obj) {
    return getProperty(propertyNumber, obj);
}

int NativeGestureObject::setEventHandler(const char* eventName, TiEvent* event) {
    NativeProxyObject::setEventHandler(eventName, event);

    if (strcmp("shake", eventName) == 0) {
        shakeListenerCount_++;
        if (shakeListenerCount_ == 1) {
            shakeHandler_->enable(true);
        }
    }
}

int NativeGestureObject::removeEventHandler(const char* eventName, int eventId) {
    NativeProxyObject::removeEventHandler(eventName, eventId);

    if (strcmp("shake", eventName) == 0) {
        shakeListenerCount_--;
        if (shakeListenerCount_ == 0) {
            shakeHandler_->enable(false);
        }
    }
}

int NativeGestureObject::getOrientation(TiObject* value) {
    DeviceInfo info;
    int orientation = Orientation::fromDevice(info.orientation());
    value->setValue(Integer::New(orientation));
    return NATIVE_ERROR_OK;
}

void NativeGestureObject::setupEvents(TiEventContainerFactory* containerFactory) {
    TiEventContainer* orientationContainer = containerFactory->createEventContainer();
    orientationContainer->setDataProperty("type", "orientationchange");
    GestureEventHandler* orientationHandler =
        new GestureEventHandler(orientationContainer);
    events_.insert("orientationchange",
                   EventPairSmartPtr(orientationContainer, orientationHandler));

    TiEventContainer* shakeContainer = containerFactory->createEventContainer();
    shakeContainer->setDataProperty("type", "shake");
    shakeHandler_ = new ShakeEventHandler(shakeContainer);
    events_.insert("shake", EventPairSmartPtr(shakeContainer, shakeHandler_));
}

