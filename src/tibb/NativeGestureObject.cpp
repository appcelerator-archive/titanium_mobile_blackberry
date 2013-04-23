/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeGestureObject.h"

#include <bb/device/DeviceInfo>
#include <bb/device/DisplayInfo>

#include "EventHandler.h"
#include "TiEventContainerFactory.h"
#include "TiOrientation.h"

using namespace bb::device;
using namespace titanium;

static NativeGestureObject::PropertyInfo properties[] = {
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

#include "NativeGestureObject.moc"

NativeGestureObject::NativeGestureObject(TiObject* obj)
  : NativeProxyObject(obj)
  , PropertyDelegateBase<NativeGestureObject>(this, properties, propertyCount) {
}

NativeGestureObject* NativeGestureObject::createGesture(TiObject* obj) {
    return new NativeGestureObject(obj);
}

void NativeGestureObject::setupEvents(TiEventContainerFactory* containerFactory) {
    TiEventContainer* orientationChange = containerFactory->createEventContainer();
    orientationChange->setDataProperty("type", "orientationchange");
    GestureEventHandler* handler = new GestureEventHandler(orientationChange);
    events_.insert("orientationchange", EventPairSmartPtr(orientationChange, handler));
}

