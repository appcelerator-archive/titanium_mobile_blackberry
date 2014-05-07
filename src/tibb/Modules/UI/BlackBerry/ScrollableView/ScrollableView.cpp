/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "ScrollableView.h"
#include <bb/cascades/StackListLayout>
#include <bb/cascades/SnapMode>
#include <bb/cascades/FlickMode>
#include <bb/cascades/ScrollIndicatorMode>
#include <bb/cascades/ArrayDataModel>
#include <bb/cascades/ListScrollStateHandler>
#include <bb/cascades/Color>
#include <bb/cascades/ScrollAnimation>

#include "ScrollableViewPage.h"

namespace TiUI
{

ScrollableItemProvider::ScrollableItemProvider()
{

}

bb::cascades::VisualNode * ScrollableItemProvider::createItem(bb::cascades::ListView*, const QString &)
{
	return new ScrollableViewPage();
}
void ScrollableItemProvider::updateItem(bb::cascades::ListView*,
									bb::cascades::VisualNode *control,
									const QString &,
									const QVariantList &,
									const QVariant &data)
{
	PageContainer* container = qvariant_cast<PageContainer*>(data);
	ScrollableViewPage *page = static_cast<ScrollableViewPage*>(control);
	page->replaceView(container->view);

};

ScrollableView::ScrollableView() :
		_tiView(NULL),
		_currentIndex(0),
		_indexCount(0)
{
	_listView = new bb::cascades::ListView();

	bb::cascades::StackListLayout* layout = static_cast<bb::cascades::StackListLayout*>(_listView->layout());

	layout->setOrientation(bb::cascades::LayoutOrientation::LeftToRight);

	_listView->setSnapMode(bb::cascades::SnapMode::LeadingEdge);
	_listView->setFlickMode(bb::cascades::FlickMode::SingleItem);
	_listView->setScrollIndicatorMode(bb::cascades::ScrollIndicatorMode::None);
	_listView->setListItemProvider(new ScrollableItemProvider());
	_listView->setDataModel(new bb::cascades::ArrayDataModel());

	bb::cascades::ListScrollStateHandler::create(_listView)
		.onFirstVisibleItemChanged(this, SLOT(onItemChanged(QVariantList)));

	setRoot(_listView);
}

ScrollableView::~ScrollableView() {
	// TODO Auto-generated destructor stub
}
int ScrollableView::getIndexCount()
{
	return _indexCount;
}
int ScrollableView::getCurrentIndex()
{
	return _currentIndex;
}
void ScrollableView::onItemChanged(QVariantList item)
{
	if(item.size() < 1) return;
	QVariant index = item[0];
	bool success;
	if(_tiView != NULL)
	{
		int i = index.toInt(&success);
		_tiView->onPageChange(i);
		_currentIndex = i;
	}
}

void ScrollableView::setTiView(TiUIScrollableView* v)
{
	_tiView = v;
}
void ScrollableView::addView(Ti::TiView *view)
{
	bb::cascades::ArrayDataModel* model = static_cast<bb::cascades::ArrayDataModel*>(_listView->dataModel());
	PageContainer* page = new PageContainer(view);
	model->append(QVariant::fromValue(page));
	_indexCount = model->size();
}
void ScrollableView::removeView(Ti::TiView* view)
{
	bb::cascades::ArrayDataModel* model = static_cast<bb::cascades::ArrayDataModel*>(_listView->dataModel());

	for(int i = 0, len = model->size(); i < len; i++)
	{
		QVariant val = model->value(i);
		PageContainer* page = val.value<PageContainer*>();
		if(page == NULL) continue;
		if(page->view == view)
		{
			model->removeAt(i);
		}
	}
	_indexCount = model->size();
}

void ScrollableView::scrollToViewAnimated(Ti::TiView* view, bool animated)
{
	bb::cascades::ArrayDataModel* model = static_cast<bb::cascades::ArrayDataModel*>(_listView->dataModel());
	for(int i = 0; i < _indexCount; i++) {
		QVariant row = model->value(i);
		PageContainer* container = row.value<PageContainer*>();
		if(container->view == view)
		{
			scrollToIndexAnimated(i, animated);
			return;
		}
	}
}

void ScrollableView::scrollToIndexAnimated(int index, bool animated) {
	QVariantList list = QVariantList() << index;
	_listView->scrollToItem(list, animated ? bb::cascades::ScrollAnimation::Smooth : bb::cascades::ScrollAnimation::None);
	_currentIndex = index;
}

}
