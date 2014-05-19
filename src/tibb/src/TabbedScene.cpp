/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2012-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TabbedScene.h"

#include <bb/cascades/TabbedPane>

using namespace bb::cascades;

namespace titanium {

TabbedScene::TabbedScene()
    : Scene(new TabbedPane()) {
}

} // namespace titanium

