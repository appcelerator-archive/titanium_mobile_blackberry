/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "WindowGroup.h"

#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/LayoutUpdateHandler>

#include "SceneManager.h"

using namespace bb::cascades;

namespace titanium {

WindowGroup::WindowGroup(Scene* scene)
    : Window(NULL)
    , scene_(scene) {
    nodeInitialize(&node_);

    LayoutUpdateHandler::create(this)
        .onLayoutFrameChanged(this, SLOT(layoutFrameChanged(QRectF)));

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
    nodeAddChild(&node_, window->layoutNode());
    nodeLayout(&node_);

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

    window->blur();

    // Focus the next window in the group. If the group is
    // now empty, the scene hosting it will be removed.
    Window* focusedWindow = getFocusedWindow();
    if (focusedWindow) {
        focusedWindow->focus();
    } else {
        SceneManager::instance()->removeScene(scene_);
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

void WindowGroup::layoutFrameChanged(const QRectF& frame) {
    fprintf(stderr, "layoutFrameChanged()\n");
    node_.element._measuredWidth = frame.width();
    node_.element._measuredHeight = frame.height();
    nodeLayout(&node_);
}

} // namespace titanium

