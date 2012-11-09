/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_PAGE_SCENE_H
#define TI_PAGE_SCENE_H

#include <bb/cascades/Page>

#include "Scene.h"
#include "WindowGroup.h"

namespace titanium {

class PageScene : public Scene {
    Q_OBJECT

public:
    PageScene() {
        bb::cascades::Page* page = bb::cascades::Page::create();
        setPane(page);

        // The content of the page is the window group container.
        windowGroup_ = new WindowGroup();
        page->setContent(windowGroup_);
    }

    virtual WindowGroup* windowGroup() const {
        return windowGroup_;
    }

private:
    WindowGroup* windowGroup_;
};

} // namespace titanium

#endif
