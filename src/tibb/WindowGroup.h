/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_WINDOW_GROUP_H
#define TI_WINDOW_GROUP_H

#include "Window.h"

namespace titanium {

class WindowGroup : public Window {
  public:
    WindowGroup();

    /**
     * Insert the window into the group and give it focus.
     * Returns true if the window was inserted, otherwise
     * false if the window is already part of the group.
     */
    bool insertWindow(Window* window);

    /**
     * Replaces an existing window in the group at the given stack index.
     * The index must be in the range 0 [bottom] to (count() - 1) [top].
     * If the existing window is in focus, it will be blurred
     * and the new window will gain focus.
     *
     * Returns true if existing window was replaced, otherwise false if not found.
     */
    bool replaceWindow(int existingWindowIndex, Window* newWindow);

    /**
     * Removes the window from the group.
     * If the window being removed is in focus, the next window in the stack will gain focus.
     *
     * Returns true if window was removed, otherwise false if not found.
     */
    bool removeWindow(Window* window);

    /**
     * Returns the window currently focused in the group.
     * If no windows are focused returns NULL.
     */
    Window* getFocusedWindow() const;

  protected:
    virtual void focus();
    virtual void blur();
};

} // namespace titanium

#endif
