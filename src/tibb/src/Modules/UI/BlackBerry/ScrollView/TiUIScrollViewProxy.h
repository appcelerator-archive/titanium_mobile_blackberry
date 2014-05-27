/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUISCROLLVIEWPROXY_H_
#define TI_TIUISCROLLVIEWPROXY_H_

#include <TiCore.h>

namespace bb
{
namespace cascades
{
class ScrollView;
}
}
namespace TiUI {
class TiUIScrollView;
class TiUIScrollViewProxy : public Ti::TiViewProxy
{
public:
	CREATE_PROXY(TiUIScrollViewProxy)
	TiUIScrollViewProxy(const char*);
	virtual ~TiUIScrollViewProxy();

	Ti::TiValue add(Ti::TiValue);
	void setLayout(Ti::TiValue);

	void onEventAdded(QString);

	Ti::TiValue scrollTo(Ti::TiValue);
	Ti::TiValue scrollToBottom(Ti::TiValue);
	virtual void initEnd();
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setCanCancelEvents, getCanCancelEvents);
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setContentHeight, getContentHeight);
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setContentOffset, getContentOffset);
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setContentWidth, getContentWidth);
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setDisableBounce, getDisableBounce);
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setHorizontalBounce, getHorizontalBounce);
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setMaxZoomScale, getMaxZoomScale);
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setMinZoomScale, getMinZoomScale);
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setOverScrollMode, getOverScrollMode);
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setScrollsToTop, getScrollsToTop);
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setScrollIndicatorStyle, getScrollIndicatorStyle);
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setScrollType, getScrollType);
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setScrollingEnabled, getScrollingEnabled);
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setShowHorizontalScrollIndicator, getShowHorizontalScrollIndicator);
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setShowVerticalScrollIndicator, getShowVerticalScrollIndicator);
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setVerticalBounce, getVerticalBounce);
	TI_CREATE_SETTER_GETTER(TiUIScrollViewProxy, setZoomScale, getZoomScale);

	EXPOSE_METHOD(TiUIScrollViewProxy, scrollTo)
	EXPOSE_METHOD(TiUIScrollViewProxy, scrollToBottom)

private:
	QString _layout;
	TiUIScrollView *_scrollView;
	bb::cascades::ScrollView* _nativeScrollView;
	bool _contentWidthSet;
	bool _contentHeightSet;
};

}
#endif /* TIUISCROLLVIEWPROXY_H_ */
