/*
 * TiScrollableView.cpp
 *
 *  Created on: Apr 23, 2013
 *      Author: penrique
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
//	for (int i = 0, len = this->views.size(); i < len; ++i) {
//		TiScrollableViewPage *page = this->views.at(i);
//		page = NULL;
//	}
// }

TiScrollableView::TiScrollableView() {
	this->startIndex = 0;
	this->contentOffsetX = 0;
	this->width = 0;
	this->currentIndex = 0;
	bb::cascades::ScrollViewProperties *scrollProps = this->scrollViewProperties();
	scrollProps->setScrollMode(bb::cascades::ScrollMode::Horizontal);

	this->contentView = bb::cascades::Container::create();
	this->contentView->setLayout(new bb::cascades::AbsoluteLayout());
	this->setContent(this->contentView);

	bb::cascades::LayoutUpdateHandler::create(this).onLayoutFrameChanged(this, SLOT(handleLayoutFrameUpdated(QRectF)));

	QObject::connect(this,SIGNAL(viewableAreaChanged(const QRectF &, float) ),this,SLOT(onScroll(const QRectF &, float)));
	QObject::connect(this,SIGNAL(viewableAreaChanging(const QRectF &, float) ),this,SLOT(onScrolling(const QRectF &, float)));


}

void TiScrollableView::startAt(int index) {
	this->startIndex = index;
}
void TiScrollableView::onScrolling(const QRectF & rect, float meh) {
	/*
	TiScrollableViewPage *item = this->views.at(3);
	std::cout << "Current is 0 " << item->getIsCurrentItem() << std::endl;
	*/
}

void TiScrollableView::onScroll(const QRectF & rect, float meh)
{
	// Avoid scrolling to "currentPage"
	this->startIndex = 0;
	float x = rect.x();
	float width = this->width;
	this->contentOffsetX = x;
	for (int i = 0, len = this->views.size(); i < len; ++i) {
		float currentX = this->width * i;
		if(x > currentX && x < currentX + width) {
			float diff1 = std::abs(currentX - x);
			float diff2 = std::abs(currentX + width - x);

			if(diff1 < diff2) {
				this->scrollToIndex(i, true);
			} else {
				this->scrollToIndex(i + 1, true);
			}
			break;
		}
	}
}

void TiScrollableView::scrollToIndex(int index, bool animated) {
	this->currentIndex = index;
	this->scrollToPoint(index * this->width, 0.0, animated ? bb::cascades::ScrollAnimation::Smooth : bb::cascades::ScrollAnimation::None );
	for (int i = 0, len = this->views.size(); i < len; ++i) {
		TiScrollableViewPage *item = this->views.at(i);
		item->setIsCurrentItem(i == index);
	}
}

void TiScrollableView::handleLayoutFrameUpdated(QRectF rect)
{
	this->width = rect.width();
	for (int i = 0, len = this->views.size(); i < len; ++i) {
		TiScrollableViewPage *item = this->views.at(i);
		item->setSize(rect.width(), rect.height());
	}
	this->arrangeViews();
}

void TiScrollableView::arrangeViews() {
	for (int i = 0, len = this->views.size(); i < len; ++i) {
		TiScrollableViewPage *item = this->views.at(i);
		item->setLeft(i * this->width);
	}

	if(this->startIndex > 0 && this->startIndex <= this->indexCount) {
		this->scrollToIndex(this->startIndex, false);
	}
}

void TiScrollableView::addView(bb::cascades::Container* view) {
	TiScrollableViewPage *item = new TiScrollableViewPage();
	item->addView(view);
	views.append(item);
	this->contentView->add(item);
	if(this->width != 0) {
		this->arrangeViews();
	}
	this->indexCount = views.size();
}
