/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIScrollViewProxy.h"
#include "TiUIScrollView.h"

#include <bb/cascades/ScrollView>
#include <bb/cascades/OverScrollEffectMode>
#include <bb/cascades/ScrollMode>
#include <bb/cascades/ScrollAnimation>

namespace TiUI {

TiUIScrollViewProxy::TiUIScrollViewProxy(const char* name) :
		Ti::TiViewProxy(name),
		_contentWidthSet(false),
		_contentHeightSet(false)

{
	createPropertySetterGetter("canCancelEvents", _setCanCancelEvents,  _getCanCancelEvents);
	createPropertySetterGetter("contentHeight", _setContentHeight,  _getContentHeight);
	createPropertySetterGetter("contentOffset", _setContentOffset,  _getContentOffset);
	createPropertySetterGetter("contentWidth", _setContentWidth,  _getContentWidth);
	createPropertySetterGetter("disableBounce", _setDisableBounce,  _getDisableBounce);
	createPropertySetterGetter("horizontalBounce", _setHorizontalBounce,  _getHorizontalBounce);
	createPropertySetterGetter("maxZoomScale", _setMaxZoomScale,  _getMaxZoomScale);
	createPropertySetterGetter("minZoomScale", _setMinZoomScale,  _getMinZoomScale);
	createPropertySetterGetter("overScrollMode", _setOverScrollMode,  _getOverScrollMode);
	createPropertySetterGetter("scrollsToTop", _setScrollsToTop,  _getScrollsToTop);
	createPropertySetterGetter("scrollIndicatorStyle", _setScrollIndicatorStyle,  _getScrollIndicatorStyle);
	createPropertySetterGetter("scrollType", _setScrollType,  _getScrollType);
	createPropertySetterGetter("scrollingEnabled", _setScrollingEnabled,  _getScrollingEnabled);
	createPropertySetterGetter("showHorizontalScrollIndicator", _setShowHorizontalScrollIndicator,  _getShowHorizontalScrollIndicator);
	createPropertySetterGetter("showVerticalScrollIndicator", _setShowVerticalScrollIndicator,  _getShowVerticalScrollIndicator);
	createPropertySetterGetter("verticalBounce", _setVerticalBounce,  _getVerticalBounce);
	createPropertySetterGetter("zoomScale", _setZoomScale,  _getZoomScale);

	createPropertyFunction("scrollTo", _scrollTo);
	createPropertyFunction("scrollToBottom", _scrollToBottom);

	_scrollView = new TiUIScrollView(this);
	_nativeScrollView = _scrollView->getScrollView();
	setView(_scrollView);

	_scrollView->childViews.append(_scrollView->getInnerView());
	_scrollView->viewLayout->addChild(_scrollView->getInnerView());
}

void TiUIScrollViewProxy::onEventAdded(QString eventName)
{
	if(eventName == "scroll")
	{
		_scrollView->setScrollEvent();
	}
	Ti::TiViewProxy::onEventAdded(eventName);
}


TiUIScrollViewProxy::~TiUIScrollViewProxy()
{
}

void TiUIScrollViewProxy::initEnd()
{
	if(!_layout.isEmpty()) {
		_scrollView->setLayout(_layout);

		if (_layout == Ti::TiConstants::LayoutVertical && !_contentHeightSet)
		{
			_scrollView->getInnerViewProxy()->view->_setHeight(Ti::TiConstants::SizeSIZE);
			_scrollView->getInnerViewProxy()->view->_setWidth(Ti::TiConstants::SizeFILL);
		}
		else if (_layout == Ti::TiConstants::LayoutHorizontal && !_contentWidthSet)
		{
			_scrollView->getInnerViewProxy()->view->_setWidth(Ti::TiConstants::SizeSIZE);
			_scrollView->getInnerViewProxy()->view->_setHeight(Ti::TiConstants::SizeFILL);
		}
	}
}
void TiUIScrollViewProxy::setLayout(Ti::TiValue val)
{
	_layout = val.toString();
}


void TiUIScrollViewProxy::setCanCancelEvents(Ti::TiValue)
{
}
void TiUIScrollViewProxy::setContentHeight(Ti::TiValue val)
{
	_contentHeightSet = true;
	_scrollView->getInnerViewProxy()->setHeight(val);
}
void TiUIScrollViewProxy::setContentOffset(Ti::TiValue arg)
{
	if(!arg.isList()) return;
	QList<Ti::TiValue> args = arg.toList();

	// Thanks for this ssaracut
	// https://github.com/appcelerator/titanium_mobile_blackberry/pull/217

	Ti::TiValue position = args.at(0);
	if(!position.isMap()) return;

	QMap<QString, Ti::TiValue> positionMap = position.toMap();
	Ti::TiValue xPos = positionMap.value(QString("x"));
	Ti::TiValue yPos = positionMap.value(QString("y"));
	float x = xPos.toNumber();
	float y = yPos.toNumber();
	bool isAnimated = true;

	if(args.size() > 1)
	{
		Ti::TiValue animated = args.at(1);
		if(animated.isMap())
		{
			QMap<QString, Ti::TiValue> animatedMap = animated.toMap();
			Ti::TiValue animatedValue = animatedMap.value(QString("animated"));
			isAnimated = animatedValue.toBool();
		}
	}



	_nativeScrollView->scrollToPoint((float)x, (float)y, isAnimated ? bb::cascades::ScrollAnimation::Default : bb::cascades::ScrollAnimation::None);
}
void TiUIScrollViewProxy::setContentWidth(Ti::TiValue val)
{
	_contentWidthSet = true;
	_scrollView->getInnerViewProxy()->setWidth(val);
}
void TiUIScrollViewProxy::setDisableBounce(Ti::TiValue val)
{
	if(val.toBool() == true)
	{
		_nativeScrollView->scrollViewProperties()->setOverScrollEffectMode(bb::cascades::OverScrollEffectMode::None);
	}
	else
	{
		_nativeScrollView->scrollViewProperties()->setOverScrollEffectMode(bb::cascades::OverScrollEffectMode::Default);
	}
}
void TiUIScrollViewProxy::setHorizontalBounce(Ti::TiValue)
{
}
void TiUIScrollViewProxy::setMaxZoomScale(Ti::TiValue)
{
}
void TiUIScrollViewProxy::setMinZoomScale(Ti::TiValue)
{
}
void TiUIScrollViewProxy::setOverScrollMode(Ti::TiValue val)
{
	_nativeScrollView->scrollViewProperties()->setOverScrollEffectMode((bb::cascades::OverScrollEffectMode::Type)val.toNumber());
}
void TiUIScrollViewProxy::setScrollsToTop(Ti::TiValue)
{
}
void TiUIScrollViewProxy::setScrollIndicatorStyle(Ti::TiValue)
{
}
void TiUIScrollViewProxy::setScrollType(Ti::TiValue val)
{
	if(val.toString() == "vertical")
	{
		_nativeScrollView->scrollViewProperties()->setScrollMode(bb::cascades::ScrollMode::Vertical);
	}
	else if(val.toString() == "horizontal")
	{
		_nativeScrollView->scrollViewProperties()->setScrollMode(bb::cascades::ScrollMode::Horizontal);
	}
}
void TiUIScrollViewProxy::setScrollingEnabled(Ti::TiValue val)
{
	if(val.toBool() == true)
	{
		// TODO: Come back to this
		_nativeScrollView->scrollViewProperties()->setScrollMode(bb::cascades::ScrollMode::Both);
	}
	else
	{
		_nativeScrollView->scrollViewProperties()->setScrollMode(bb::cascades::ScrollMode::None);
	}

}
void TiUIScrollViewProxy::setShowHorizontalScrollIndicator(Ti::TiValue)
{
}
void TiUIScrollViewProxy::setShowVerticalScrollIndicator(Ti::TiValue)
{
}
void TiUIScrollViewProxy::setVerticalBounce(Ti::TiValue)
{
}
void TiUIScrollViewProxy::setZoomScale(Ti::TiValue)
{
}

Ti::TiValue TiUIScrollViewProxy::getCanCancelEvents()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollViewProxy::getContentHeight()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollViewProxy::getContentOffset()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollViewProxy::getContentWidth()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollViewProxy::getDisableBounce()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollViewProxy::getHorizontalBounce()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollViewProxy::getMaxZoomScale()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollViewProxy::getMinZoomScale()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollViewProxy::getOverScrollMode()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollViewProxy::getScrollsToTop()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollViewProxy::getScrollIndicatorStyle()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollViewProxy::getScrollType()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollViewProxy::getScrollingEnabled()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollViewProxy::getShowHorizontalScrollIndicator()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollViewProxy::getShowVerticalScrollIndicator()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollViewProxy::getVerticalBounce()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollViewProxy::getZoomScale()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

Ti::TiValue TiUIScrollViewProxy::add(Ti::TiValue val)
{
	return _scrollView->getInnerViewProxy()->add(val);
}

Ti::TiValue TiUIScrollViewProxy::scrollTo(Ti::TiValue arg)
{
	if(!arg.isList()) return Ti::TiValue();
	QList<Ti::TiValue> array = arg.toList();
	if(array.size() < 2)  return Ti::TiValue();
	Ti::TiValue x = array.at(0);
	Ti::TiValue y = array.at(1);
	_nativeScrollView->scrollToPoint((float)x.toNumber(), (float)y.toNumber());
	return Ti::TiValue();
}

Ti::TiValue TiUIScrollViewProxy::scrollToBottom(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

}
