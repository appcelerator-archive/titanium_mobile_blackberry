/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiOrientation.h"

#include <bb/device/DisplayInfo>

#include "Scene.h"

using namespace bb::device;

namespace titanium {

Orientation::Type Orientation::fromDevice(DeviceOrientation::Type orientation) {
    // Device orientation is relative to the BlackBerry logo.
    // Determine if "portrait" is the device's natural orientation.
    static bool isPortrait = DisplayInfo().aspectType() ==
      DisplayAspectType::Portrait || DisplayAspectType::Square;

    // Convert the device orientation to Titanium's orientation
    // by using the natual orientation of the device to know if
    // it is being held in portrait or landscape.
    switch (orientation) {
      case DeviceOrientation::FaceUp:
        return FACE_UP;
      case DeviceOrientation::FaceDown:
        return FACE_DOWN;
      case DeviceOrientation::TopUp:
        return isPortrait ? PORTRAIT : LANDSCAPE_LEFT;
      case DeviceOrientation::LeftUp:
        return isPortrait ? LANDSCAPE_LEFT : PORTRAIT;
      case DeviceOrientation::RightUp:
        return isPortrait ? LANDSCAPE_RIGHT : UPSIDE_PORTRAIT;
      case DeviceOrientation::BottomUp:
        return isPortrait ? UPSIDE_PORTRAIT : LANDSCAPE_RIGHT;
      default:
        return UNKNOWN;
    }
}

int Orientation::toSceneMode(Orientation::Type orientation) {
    switch (orientation) {
      case PORTRAIT:
      case UPSIDE_PORTRAIT:
        return Scene::PORTRAIT;
      case LANDSCAPE_LEFT:
      case LANDSCAPE_RIGHT:
        return Scene::LANDSCAPE;
      default:
        return 0;
    }
}

}  // namespace titanium

