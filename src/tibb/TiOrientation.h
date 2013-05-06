/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_ORIENTATION_H
#define TI_ORIENTATION_H

#include <bb/device/DeviceOrientation>

namespace titanium {

class Orientation {
public:
    enum Type {
        PORTRAIT,
        UPSIDE_PORTRAIT,
        LANDSCAPE_LEFT,
        LANDSCAPE_RIGHT,
        FACE_UP,
        FACE_DOWN,
        UNKNOWN
    };

    // BlackBerry device orientation to Titanium orientation.
    static Type fromDevice(bb::device::DeviceOrientation::Type orientation);

    // Convert Titanium orientation into a scene orientation mode flag.
    static int toSceneMode(Type orientation);
};

}  // namespace titanium

#endif

