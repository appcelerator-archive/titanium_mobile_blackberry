/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUISCROLLABLEVIEWPROXY_H_
#define TI_TIUISCROLLABLEVIEWPROXY_H_

#include <TiCore.h>
#include "ScrollableView.h"

namespace TiUI {
class TiUIScrollableView;
class TiUIScrollableViewProxy : public Ti::TiViewProxy
{
public:
	CREATE_PROXY(TiUIScrollableViewProxy)
	TiUIScrollableViewProxy(const char*);
	virtual ~TiUIScrollableViewProxy();

	void setCacheSize(Ti::TiValue);
	void setCurrentPage(Ti::TiValue);
	void setDisableBounce(Ti::TiValue);
	void setOverScrollMode(Ti::TiValue);
	void setPagingControlColor(Ti::TiValue);
	void setPagingControlHeight(Ti::TiValue);
	void setShowPagingControl(Ti::TiValue);
	void setPagingControlTimeout(Ti::TiValue);
	void setPagingControlAlpha(Ti::TiValue);
	void setPagingControlOnTop(Ti::TiValue);
	void setOverlayEnabled(Ti::TiValue);
	void setScrollingEnabled(Ti::TiValue);
	void setViews(Ti::TiValue);
	void setClipViews(Ti::TiValue);
	void setHitRect(Ti::TiValue);

	Ti::TiValue getCacheSize();
	Ti::TiValue getCurrentPage();
	Ti::TiValue getDisableBounce();
	Ti::TiValue getOverScrollMode();
	Ti::TiValue getPagingControlColor();
	Ti::TiValue getPagingControlHeight();
	Ti::TiValue getShowPagingControl();
	Ti::TiValue getPagingControlTimeout();
	Ti::TiValue getPagingControlAlpha();
	Ti::TiValue getPagingControlOnTop();
	Ti::TiValue getOverlayEnabled();
	Ti::TiValue getScrollingEnabled();
	Ti::TiValue getViews();
	Ti::TiValue getClipViews();
	Ti::TiValue getHitRect();

	Ti::TiValue addView(Ti::TiValue);
	Ti::TiValue moveNext(Ti::TiValue);
	Ti::TiValue movePrevious(Ti::TiValue);
	Ti::TiValue removeView(Ti::TiValue);
	Ti::TiValue scrollToView(Ti::TiValue);

	Ti::TiViewProxy *getProxyAt(int);

	EXPOSE_SETTER(TiUIScrollableViewProxy, setCacheSize)
	EXPOSE_SETTER(TiUIScrollableViewProxy, setCurrentPage)
	EXPOSE_SETTER(TiUIScrollableViewProxy, setDisableBounce)
	EXPOSE_SETTER(TiUIScrollableViewProxy, setOverScrollMode)
	EXPOSE_SETTER(TiUIScrollableViewProxy, setPagingControlColor)
	EXPOSE_SETTER(TiUIScrollableViewProxy, setPagingControlHeight)
	EXPOSE_SETTER(TiUIScrollableViewProxy, setShowPagingControl)
	EXPOSE_SETTER(TiUIScrollableViewProxy, setPagingControlTimeout)
	EXPOSE_SETTER(TiUIScrollableViewProxy, setPagingControlAlpha)
	EXPOSE_SETTER(TiUIScrollableViewProxy, setPagingControlOnTop)
	EXPOSE_SETTER(TiUIScrollableViewProxy, setOverlayEnabled)
	EXPOSE_SETTER(TiUIScrollableViewProxy, setScrollingEnabled)
	EXPOSE_SETTER(TiUIScrollableViewProxy, setViews)
	EXPOSE_SETTER(TiUIScrollableViewProxy, setClipViews)
	EXPOSE_SETTER(TiUIScrollableViewProxy, setHitRect)

	EXPOSE_GETTER(TiUIScrollableViewProxy, getCacheSize)
	EXPOSE_GETTER(TiUIScrollableViewProxy, getCurrentPage)
	EXPOSE_GETTER(TiUIScrollableViewProxy, getDisableBounce)
	EXPOSE_GETTER(TiUIScrollableViewProxy, getOverScrollMode)
	EXPOSE_GETTER(TiUIScrollableViewProxy, getPagingControlColor)
	EXPOSE_GETTER(TiUIScrollableViewProxy, getPagingControlHeight)
	EXPOSE_GETTER(TiUIScrollableViewProxy, getShowPagingControl)
	EXPOSE_GETTER(TiUIScrollableViewProxy, getPagingControlTimeout)
	EXPOSE_GETTER(TiUIScrollableViewProxy, getPagingControlAlpha)
	EXPOSE_GETTER(TiUIScrollableViewProxy, getPagingControlOnTop)
	EXPOSE_GETTER(TiUIScrollableViewProxy, getOverlayEnabled)
	EXPOSE_GETTER(TiUIScrollableViewProxy, getScrollingEnabled)
	EXPOSE_GETTER(TiUIScrollableViewProxy, getViews)
	EXPOSE_GETTER(TiUIScrollableViewProxy, getClipViews)
	EXPOSE_GETTER(TiUIScrollableViewProxy, getHitRect)

	EXPOSE_METHOD(TiUIScrollableViewProxy, addView)
	EXPOSE_METHOD(TiUIScrollableViewProxy, moveNext)
	EXPOSE_METHOD(TiUIScrollableViewProxy, movePrevious)
	EXPOSE_METHOD(TiUIScrollableViewProxy, removeView)
	EXPOSE_METHOD(TiUIScrollableViewProxy, scrollToView)
private:
	ScrollableView *_nativeScrollableView;
	QList<TiViewProxy*> _allViews;
};

}
#endif /* TIUISCROLLABLEVIEWPROXY_H_ */
