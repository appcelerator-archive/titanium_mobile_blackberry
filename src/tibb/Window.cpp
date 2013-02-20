/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "Window.h"

#include "Scene.h"

using namespace bb::cascades;

namespace titanium {

Window::Window(Scene* scene)
    : scene_(scene) {
}

void Window::focus() {
    emit onFocus();
}

void Window::blur() {
    emit onBlur();
}

} // namespace titanium

