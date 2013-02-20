/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_PAGE_SCENE_H
#define TI_PAGE_SCENE_H

#include "Scene.h"

namespace titanium {

class Window;

class PageScene : public Scene {
    Q_OBJECT

public:
    PageScene();

    // Returns the main window for this scene.
    Window* mainWindow() const {
        return window_;
    }

    void addAction(bb::cascades::ActionItem* item);

private:
    Window* window_;
};

} // namespace titanium

#endif
