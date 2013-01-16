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
        page_ = bb::cascades::Page::create();
        setPane(page_);

        // The content of the page is the window group container.
        windowGroup_ = new WindowGroup(this);
        page_->setContent(windowGroup_);
    }

    virtual WindowGroup* windowGroup() const {
        return windowGroup_;
    }

    virtual void addAction(bb::cascades::ActionItem* item) {
        // TODO(josh): expose setting placement of action item.
        page_->addAction(item, bb::cascades::ActionBarPlacement::OnBar);
    }

private:
    WindowGroup* windowGroup_;
    bb::cascades::Page* page_;
};

} // namespace titanium

#endif
