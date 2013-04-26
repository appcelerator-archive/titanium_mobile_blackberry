/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiScrollableView.h"
#include "TiScrollableViewPage.h"
#include <bb/cascades/ScrollViewProperties>
#include <bb/cascades/ScrollAnimation>
#include <bb/cascades/LayoutUpdateHandler>
#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <iostream>

TiScrollableView::~TiScrollableView() { }

TiScrollableView::TiScrollableView()
{
    startIndex = 0;
    contentOffsetX = 0;
    width = 0;
    currentIndex = 0;
    bb::cascades::ScrollViewProperties *scrollProps = scrollViewProperties();
    scrollProps->setScrollMode(bb::cascades::ScrollMode::Horizontal);

    contentView = bb::cascades::Container::create();
    contentView->setLayout(new bb::cascades::AbsoluteLayout());
    setContent(contentView);

    bb::cascades::LayoutUpdateHandler::create(this).onLayoutFrameChanged(this, SLOT(handleLayoutFrameUpdated(QRectF)));

    QObject::connect(this,SIGNAL(viewableAreaChanged(const QRectF &, float) ),this,SLOT(onScroll(const QRectF &, float)));
    QObject::connect(this,SIGNAL(viewableAreaChanging(const QRectF &, float) ),this,SLOT(onScrolling(const QRectF &, float)));
}

void TiScrollableView::handleLayoutFrameUpdated(QRectF rect)
{
    width = rect.width();
    for (int i = 0, len = views.size(); i < len; ++i) {
        TiScrollableViewPage *item = views.at(i);
        item->setSize(rect.width(), rect.height());
    }
    arrangeViews();
}

void TiScrollableView::startAt(int index)
{
    startIndex = index;
}

void TiScrollableView::onScrolling(const QRectF & rect, float meh)
{
    // TODO something useful
}

void TiScrollableView::onScroll(const QRectF & rect, float meh)
{
    // Avoid scrolling to "currentPage"
    startIndex = 0;
    float x = rect.x();
    float width = width;
    contentOffsetX = x;
    for (int i = 0, len = views.size(); i < len; ++i) {
        float currentX = width * i;
        if(x > currentX && x < currentX + width) {
            float diff1 = std::abs(currentX - x);
            float diff2 = std::abs(currentX + width - x);

            if(diff1 < diff2) {
                scrollToIndex(i, true);
            } else {
                scrollToIndex(i + 1, true);
            }
            break;
        }
    }
}

void TiScrollableView::scrollToIndex(int index, bool animated)
{
    currentIndex = index;
    scrollToPoint(index * width, 0.0, animated ? bb::cascades::ScrollAnimation::Smooth : bb::cascades::ScrollAnimation::None );
    for (int i = 0, len = views.size(); i < len; ++i) {
        TiScrollableViewPage *item = views.at(i);
        item->setIsCurrentItem(i == index);
    }
}

void TiScrollableView::arrangeViews() {
    for (int i = 0, len = views.size(); i < len; ++i) {
        TiScrollableViewPage *item = views.at(i);
        item->setLeft(i * width);
    }

    if(startIndex > 0 && startIndex <= indexCount) {
        scrollToIndex(startIndex, false);
    }
}

void TiScrollableView::addView(bb::cascades::Container* view) {
    TiScrollableViewPage *item = new TiScrollableViewPage();
    item->addView(view);
    views.append(item);
    contentView->add(item);
    if(width != 0) {
        arrangeViews();
    }
    indexCount = views.size();
}
