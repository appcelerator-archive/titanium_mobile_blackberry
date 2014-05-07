/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIScrollableViewProxy.h"
#include "TiUIScrollableView.h"

#define TI_SCROLLABLEVIEW_NOT_IMPLEMENTED Ti::TiHelper::Log("[ScrollableView] Ti.UI.ScrollableView " + QString(__func__) + " not Implemented yet");

namespace TiUI {

TiUIScrollableViewProxy::TiUIScrollableViewProxy(const char* name) : Ti::TiViewProxy(name)
{

	createPropertySetterGetter("cacheSize", _setCacheSize,  _getCacheSize);
	createPropertySetterGetter("currentPage", _setCurrentPage,  _getCurrentPage);
	createPropertySetterGetter("disableBounce", _setDisableBounce,  _getDisableBounce);
	createPropertySetterGetter("overScrollMode", _setOverScrollMode,  _getOverScrollMode);
	createPropertySetterGetter("pagingControlColor", _setPagingControlColor,  _getPagingControlColor);
	createPropertySetterGetter("pagingControlHeight", _setPagingControlHeight,  _getPagingControlHeight);
	createPropertySetterGetter("showPagingControl", _setShowPagingControl,  _getShowPagingControl);
	createPropertySetterGetter("pagingControlTimeout", _setPagingControlTimeout,  _getPagingControlTimeout);
	createPropertySetterGetter("pagingControlAlpha", _setPagingControlAlpha,  _getPagingControlAlpha);
	createPropertySetterGetter("pagingControlOnTop", _setPagingControlOnTop,  _getPagingControlOnTop);
	createPropertySetterGetter("overlayEnabled", _setOverlayEnabled,  _getOverlayEnabled);
	createPropertySetterGetter("scrollingEnabled", _setScrollingEnabled,  _getScrollingEnabled);
	createPropertySetterGetter("views", _setViews,  _getViews);
	createPropertySetterGetter("clipViews", _setClipViews,  _getClipViews);
	createPropertySetterGetter("hitRect", _setHitRect,  _getHitRect);

	createPropertyFunction("addView", _addView);
	createPropertyFunction("moveNext", _moveNext);
	createPropertyFunction("movePrevious", _movePrevious);
	createPropertyFunction("removeView", _removeView);
	createPropertyFunction("scrollToView", _scrollToView);
	TiUIScrollableView *v = new TiUIScrollableView(this);
	_nativeScrollableView = v->getNative();
	setView(v);
}

TiUIScrollableViewProxy::~TiUIScrollableViewProxy()
{
	foreach(Ti::TiViewProxy* p, _allViews)
	{
		p->makeWeak();
	}
}
void TiUIScrollableViewProxy::setCacheSize(Ti::TiValue)
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
}
void TiUIScrollableViewProxy::setCurrentPage(Ti::TiValue value)
{
	scrollToView(value);
}
void TiUIScrollableViewProxy::setDisableBounce(Ti::TiValue)
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
}
void TiUIScrollableViewProxy::setOverScrollMode(Ti::TiValue)
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
}
void TiUIScrollableViewProxy::setPagingControlColor(Ti::TiValue)
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
}
void TiUIScrollableViewProxy::setPagingControlHeight(Ti::TiValue)
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
}
void TiUIScrollableViewProxy::setShowPagingControl(Ti::TiValue)
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
}
void TiUIScrollableViewProxy::setPagingControlTimeout(Ti::TiValue)
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
}
void TiUIScrollableViewProxy::setPagingControlAlpha(Ti::TiValue)
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
}
void TiUIScrollableViewProxy::setPagingControlOnTop(Ti::TiValue)
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
}
void TiUIScrollableViewProxy::setOverlayEnabled(Ti::TiValue)
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
}
void TiUIScrollableViewProxy::setScrollingEnabled(Ti::TiValue)
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
}
void TiUIScrollableViewProxy::setViews(Ti::TiValue value)
{
	if(!value.isList()) return;
	QList<Ti::TiValue> allValues = value.toList();

	foreach(Ti::TiViewProxy *p, _allViews)
	{
		removeView(Ti::TiValue(p->_jsObject));
	}

	foreach(Ti::TiValue currentValue, allValues)
	{
		if(currentValue.isProxy())
		{
			addView(currentValue);
		}
		else
		{
			Ti::TiViewProxy* v = Ti::TiViewProxy::CreateProxy();
			v->add(currentValue);
			addView(Ti::TiValue(v->_jsObject));
		}
	}
}
void TiUIScrollableViewProxy::setClipViews(Ti::TiValue)
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
}
void TiUIScrollableViewProxy::setHitRect(Ti::TiValue)
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
}

Ti::TiValue TiUIScrollableViewProxy::getCacheSize()
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::getCurrentPage()
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::getDisableBounce()
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::getOverScrollMode()
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::getPagingControlColor()
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::getPagingControlHeight()
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::getShowPagingControl()
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::getPagingControlTimeout()
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::getPagingControlAlpha()
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::getPagingControlOnTop()
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::getOverlayEnabled()
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::getScrollingEnabled()
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::getViews()
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::getClipViews()
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::getHitRect()
{
	TI_SCROLLABLEVIEW_NOT_IMPLEMENTED
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

Ti::TiValue TiUIScrollableViewProxy::addView(Ti::TiValue value)
{
	Ti::TiValue val;
	val.setUndefined();

	Ti::TiViewProxy* viewProxy;
	if(!value.isProxy())
	{
		viewProxy = Ti::TiViewProxy::CreateProxy();
		viewProxy->add(Ti::TiValue(value.toJSValue()));
	}
	else
	{
		viewProxy = static_cast<Ti::TiViewProxy*>(value.toProxy());
	}
	viewProxy->clearWeak();
	_nativeScrollableView->addView(viewProxy->view);
	view->viewLayout->addChild(viewProxy->view);
	_allViews.append(viewProxy);
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::moveNext(Ti::TiValue)
{
	int index = _nativeScrollableView->getCurrentIndex();
	if(index < _nativeScrollableView->getIndexCount() - 1) index++;
	_nativeScrollableView->scrollToIndexAnimated(index, true);
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::movePrevious(Ti::TiValue)
{
	int index = _nativeScrollableView->getCurrentIndex();
	if(index > 1) index--;
	_nativeScrollableView->scrollToIndexAnimated(index, true);
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIScrollableViewProxy::removeView(Ti::TiValue val)
{
	if(val.isProxy())
	{
		Ti::TiViewProxy * p = static_cast<Ti::TiViewProxy*>(val.toProxy());
		if(_allViews.contains(p))
		{
			_nativeScrollableView->removeView(p->view);
			view->viewLayout->removeChild(p->view);
			p->makeWeak();
			_allViews.removeOne(p);
		}
	}
	else
	{
		foreach(Ti::TiViewProxy* p, _allViews)
		{
			if(p->_jsObject == val.toJSValue())
			{
				removeView(Ti::TiValue(p->_jsObject));
			}
		}
	}
	return Ti::TiValue();
}
Ti::TiValue TiUIScrollableViewProxy::scrollToView(Ti::TiValue value)
{
	Ti::TiValue indexValue;
	bool animated = true;
	if(value.isList())
	{
		QList<Ti::TiValue> obj = value.toList();
		indexValue = obj.at(0);

		Ti::TiValue an = obj.at(1);
		animated = an.toBool();
	}
	else
	{
		indexValue = value;
	}

	if(indexValue.isNumber())
	{
		double num = value.toNumber();
		int index = round(indexValue.toNumber());
		int count = _nativeScrollableView->getIndexCount();

		if(index > -1 && index < count + 1)
		{
			_nativeScrollableView->scrollToIndexAnimated(index, animated);
		}
	}
	else if(indexValue.isProxy())
	{
		Ti::TiViewProxy *viewProxy = static_cast<Ti::TiViewProxy*>(indexValue.toProxy());
		_nativeScrollableView->scrollToViewAnimated(viewProxy->view, animated);
	}
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

}
