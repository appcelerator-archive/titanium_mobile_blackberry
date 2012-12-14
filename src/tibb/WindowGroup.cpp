/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "WindowGroup.h"

#include <bb/cascades/AbsoluteLayout>

using namespace bb::cascades;

namespace titanium {

WindowGroup::WindowGroup() {
    // Windows groups use absolute layout for
    // positioning of windows inside the container.
    setLayout(new AbsoluteLayout());
}

bool WindowGroup::insertWindow(Window* window) {
    if (Container::indexOf(window) != -1) {
        // Fail if the window is already in this group.
        return false;
    }

    Window* focusedWindow = getFocusedWindow();
    if (focusedWindow != NULL) {
        focusedWindow->blur();
    }

    Container::add(window);

    window->focus();

    return true;
}

bool WindowGroup::replaceWindow(int existingWindowIndex, Window* newWindow) {
    return false;
}

bool WindowGroup::removeWindow(Window* window) {
    if (!Container::remove(window)) {
        // Fail if the window was not in this group.
        return false;
    }

    // Get the window now in focus after we have removed the
    // previously focused window from the group. Note this
    // may be NULL if the group is now empty.
    Window* focusedWindow = getFocusedWindow();

    window->blur();
    if (focusedWindow != NULL) {
        focusedWindow->focus();
    }

    return true;
}

Window* WindowGroup::getFocusedWindow() const {
    Control* control = Container::at(Container::count() - 1);
    if (control == NULL) {
        return NULL;
    }

    // TODO(josh): Could we do more to prevent this failure?
    //Q_ASSERT(control->inherits("Window"));
    return static_cast<Window*>(control);
}

void WindowGroup::focus() {
}

void WindowGroup::blur() {
}

} // namespace titanium

