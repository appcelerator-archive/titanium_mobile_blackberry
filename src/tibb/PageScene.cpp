/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "PageScene.h"

#include <bb/cascades/Page>

#include "Window.h"

using namespace bb::cascades;

namespace titanium {

PageScene::PageScene()
    : Scene(new Page())
    , window_(new Window(this)) {
    static_cast<Page*>(pane())->setContent(window_);
}

void PageScene::addAction(ActionItem* item) {
    // TODO(josh): expose setting placement of action item.
    static_cast<Page*>(pane())->addAction(item, ActionBarPlacement::OnBar);
}

TitleBar* PageScene::titleBar() {
    Page* page = static_cast<Page*>(pane());
    TitleBar* titleBar = page->titleBar();
    if (!titleBar) {
        titleBar = new TitleBar();
        page->setTitleBar(titleBar);
    }
    return titleBar;
}

} // namespace titanium

