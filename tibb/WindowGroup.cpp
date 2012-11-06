/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "WindowGroup.h"

using namespace bb::cascades;

namespace titanium {

void WindowGroup::insertWindow(AbstractWindow* window) {
    // Get the currently focused window before we insert the new window.
    // We will need to blur it once the insert has completed.
    AbstractWindow* blurredWindow = getFocusedWindow();

    if (!Container::add(window)) {
        // Fail if the window is already in this group.
        return false;
    }

    if (blurredWindow != NULL) {
        blurredWindow->blur();
    }
    window->focus();

    return true;
}

bool WindowGroup::replaceWindow(int existingWindowIndex, AbstractWindow* newWindow) {
    return false;
}

bool WindowGroup::removeWindow(AbstractWindow* window) {
    if (!Container::remove(window)) {
        // Fail if the window was not in this group.
        return false;
    }

    // Get the window now in focus after we have removed the
    // previously focused window from the group. Note this
    // may be NULL if the group is now empty.
    AbstractWindow* focusedWindow = getFocusedWindow();

    window->blur();
    if (focusedWindow != NULL) {
        focusedWindow->focus();
    }

    return true;
}

AbstractWindow* WindowGroup::getFocusedWindow() const {
    Control* control = Container::at(Container::count() - 1);

    // TODO(josh): Could we do more to prevent this failure?
    Q_ASSERT(control->inherits("AbstractWindow"));
    return static_cast<AbstractWindow*>(control);
}

void WindowGroup::focus() {
}

void WindowGroup::blur() {
}

} // namespace titanium

