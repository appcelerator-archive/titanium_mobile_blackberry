/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIScrollView.h"
#include "ScrollViewContentView.h"
#include <bb/cascades/ScrollView>
#include <bb/cascades/Control>
#include <bb/cascades/DockLayout>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/LayoutUpdateHandler>
#include <bb/cascades/ScrollViewProperties>
#include <bb/cascades/ScrollMode>
#include <bb/cascades/Color>
namespace TiUI {



TiUIScrollView::TiUIScrollView(Ti::TiViewProxy* proxy) :
		Ti::TiView(proxy),
		_hasScrollEvent(false)
{
	_contentSize = QSize(0,0);
	_viewSize = QSize(0,0);

	_innerViewProxy = ScrollViewContentViewProxy::CreateProxy();
	_innerViewProxy->clearWeak();
	_innerView = _innerViewProxy->getView();

	static_cast<ScrollViewContentView*>(_innerView)->setScrollView(this);

	_innerView->setParentView(this);
	_scrollView = new bb::cascades::ScrollView();
	QObject::connect(_scrollView, SIGNAL(viewableAreaChanging(const QRectF&, float)), this, SLOT(onScroll(const QRectF&, float)));
	setChildControl(_scrollView);
	_scrollView->setContent(_innerView);
}

bool TiUIScrollView::ingoreWidth()
{
	return false;
}
bool TiUIScrollView::ingoreHeight()
{
	return false;
}
QString TiUIScrollView::defaultWidth()
{
	return Ti::TiConstants::SizeFILL;
}
QString TiUIScrollView::defaultHeight()
{
	return Ti::TiConstants::SizeFILL;
}

void TiUIScrollView::onScroll(const QRectF & rect, float)
{
	if(_hasScrollEvent)
	{
		Ti::TiEventParameters eventParams;

		Ti::TiEventParameters contentOffsetParams;
		contentOffsetParams.addParam("x", Ti::TiHelper::PixelsToDP(rect.x()));
		contentOffsetParams.addParam("y",  Ti::TiHelper::PixelsToDP(rect.y()));

		Ti::TiEventParameters contentSizeParams;
		contentSizeParams.addParam("width",  Ti::TiHelper::PixelsToDP(rect.width()));
		contentSizeParams.addParam("height",  Ti::TiHelper::PixelsToDP(rect.height()));

		eventParams.addParam("contentOffset", contentOffsetParams);
		eventParams.addParam("contentSize", contentSizeParams);
		eventParams.addParam("x", Ti::TiHelper::PixelsToDP(rect.x()));
		eventParams.addParam("y",  Ti::TiHelper::PixelsToDP(rect.y()));

		getProxy()->fireEvent("scroll", eventParams);
	}
}
void TiUIScrollView::updateContentSize(QRectF rect)
{
	if(_contentSize == rect.size()) return;
	_contentSize = rect.size();

	bb::cascades::ScrollViewProperties* scrollViewProperties = _scrollView->scrollViewProperties();

    if(_contentSize.width() > _viewSize.width() && _contentSize.height() <= _viewSize.height())
    {
    	_innerView->viewLayout->_setHeight(Ti::TiConstants::SizeFILL);
    	scrollViewProperties->setScrollMode(bb::cascades::ScrollMode::Horizontal);
    }
    else if(_contentSize.height() > _viewSize.height() && _contentSize.width() <= _viewSize.width())
    {
    	_innerView->viewLayout->_setWidth(Ti::TiConstants::SizeFILL);
    	scrollViewProperties->setScrollMode(bb::cascades::ScrollMode::Vertical);
    }
    else if(_contentSize.width() <= _viewSize.width() && _contentSize.height() <= _viewSize.height())
    {
    	_innerView->viewLayout->_setHeight(Ti::TiConstants::SizeFILL);
    	_innerView->viewLayout->_setWidth(Ti::TiConstants::SizeFILL);
    	scrollViewProperties->setScrollMode(bb::cascades::ScrollMode::None);
    }
    else
    {
    	scrollViewProperties->setScrollMode(bb::cascades::ScrollMode::Both);
   	}

}

void TiUIScrollView::setScrollEvent()
{
	_hasScrollEvent = true;
}
void TiUIScrollView::onRelayout(QRectF rect)
{
	Ti::TiView::onRelayout(rect);
	if(_viewSize == rect.size()) return;
	_viewSize = rect.size();
}
TiUIScrollView::~TiUIScrollView()
{
	_innerViewProxy->makeWeak();
}

void TiUIScrollView::setLayout(QString str)
{
	_innerView->_setLayout(str);
}

bb::cascades::ScrollView* TiUIScrollView::getScrollView()
{
	return _scrollView;
}
Ti::TiView * TiUIScrollView::getInnerView()
{
	return _innerView;
}
Ti::TiViewProxy *TiUIScrollView::getInnerViewProxy()
{
	return _innerViewProxy;
}

}
