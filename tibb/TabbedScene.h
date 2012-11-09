/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TABBED_SCENE_H
#define TI_TABBED_SCENE_H

#include <bb/cascades/Page>
#include <bb/cascades/TabbedPane>

#include "Scene.h"
#include "WindowGroup.h"

namespace titanium {

class TabbedScene : public Scene {
    Q_OBJECT

public:
    TabbedScene() {
        bb::cascades::TabbedPane* tabbedPane = new bb::cascades::TabbedPane();
        setPane(tabbedPane);

        bb::cascades::Page* activePane = new bb::cascades::Page();
        tabbedPane->setActivePane(activePane);

        windowGroup_ = new WindowGroup();
        activePane->setContent(windowGroup_);
    }

    virtual WindowGroup* windowGroup() const {
        return windowGroup_;
    }

private:
    WindowGroup* windowGroup_;
};

} // namespace titanium

#endif
