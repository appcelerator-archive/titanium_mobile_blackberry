/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiScrollableViewPage.h"

#include <bb/cascades/DockLayout>
#include <bb/cascades/AbsoluteLayoutProperties>

TiScrollableViewPage::TiScrollableViewPage() {
    bb::cascades::AbsoluteLayoutProperties *layoutProps = new bb::cascades::AbsoluteLayoutProperties();
    setLayoutProperties(layoutProps);
    setLayout(new bb::cascades::DockLayout());
    _isCurrentItem = false;
    _left = 0;
    _index = 0;
}
TiScrollableViewPage::~TiScrollableViewPage() { }

void TiScrollableViewPage::setIndex(int index) {
    _index = index;
}
int TiScrollableViewPage::getIndex() {
    return  _index;
}
void TiScrollableViewPage::setLeft(float left) {
    _left = left;
    bb::cascades::AbsoluteLayoutProperties* props = (bb::cascades::AbsoluteLayoutProperties*)layoutProperties();
    props->setPositionX(left);
}

float TiScrollableViewPage::getLeft() {
    return _left;
}

void TiScrollableViewPage::setIsCurrentItem(bool isCurrent) {
    _isCurrentItem = isCurrent;
}

bool TiScrollableViewPage::getIsCurrentItem() {
    return _isCurrentItem;
}

void TiScrollableViewPage::setSize(float width, float height) {
    setPreferredSize(width, height);
    setMinHeight(height);
    setMaxHeight(height);
    setMinWidth(width);
    setMaxWidth(width);
}

void TiScrollableViewPage::addView(bb::cascades::Control *control) {
    control->setHorizontalAlignment(bb::cascades::HorizontalAlignment::Fill);
    control->setVerticalAlignment(bb::cascades::VerticalAlignment::Fill);
    add(control);
}
