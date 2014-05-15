/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIVIEWPROXY_H_
#define TIVIEWPROXY_H_

#include "Ti_Proxy.h"
#include <QObject>
#include <v8.h>

using namespace v8;

namespace bb
{
namespace cascades
{
class Control;
}
}
namespace Ti
{
class TiView;
class TiValue;
class TiViewProxy: public TiProxy
{
public:
	TiViewProxy(const char*);
	virtual ~TiViewProxy();
	virtual TiView* getView();
	CREATE_PROXY(TiViewProxy)

	virtual void onEventAdded(QString);

	virtual void setAccessibilityHidden(Ti::TiValue);
	virtual void setAccessibilityHint(Ti::TiValue);
	virtual void setAccessibilityLabel(Ti::TiValue);
	virtual void setAccessibilityValue(Ti::TiValue);
	virtual void setAnchorPoint(Ti::TiValue);
	virtual void setBackgroundColor(Ti::TiValue);
	virtual void setBackgroundDisabledColor(Ti::TiValue);
	virtual void setBackgroundDisabledImage(Ti::TiValue);
	virtual void setBackgroundFocusedColor(Ti::TiValue);
	virtual void setBackgroundFocusedImage(Ti::TiValue);
	virtual void setBackgroundGradient(Ti::TiValue);
	virtual void setBackgroundImage(Ti::TiValue);
	virtual void setBackgroundRepeat(Ti::TiValue);
	virtual void setBackgroundLeftCap(Ti::TiValue);
	virtual void setBackgroundSelectedColor(Ti::TiValue);
	virtual void setBackgroundSelectedImage(Ti::TiValue);
	virtual void setBackgroundTopCap(Ti::TiValue);
	virtual void setBorderColor(Ti::TiValue);
	virtual void setBorderRadius(Ti::TiValue);
	virtual void setBorderWidth(Ti::TiValue);
	virtual void setBottom(Ti::TiValue);
	virtual void setCenter(Ti::TiValue);
	virtual void setEnabled(Ti::TiValue);
	virtual void setFocusable(Ti::TiValue);
	virtual void setHeight(Ti::TiValue);
	virtual void setLeft(Ti::TiValue);
	virtual void setLayout(Ti::TiValue);
	virtual void setOpacity(Ti::TiValue);
	virtual void setRight(Ti::TiValue);
	virtual void setSoftKeyboardOnFocus(Ti::TiValue);
	virtual void setTop(Ti::TiValue);
	virtual void setTouchEnabled(Ti::TiValue);
	virtual void setTransform(Ti::TiValue);
	virtual void setVisible(Ti::TiValue);
	virtual void setWidth(Ti::TiValue);
	virtual void setHorizontalWrap(Ti::TiValue);
	virtual void setZIndex(Ti::TiValue);
	virtual void setKeepScreenOn(Ti::TiValue);
	virtual void setContextMenus(Ti::TiValue);

	virtual Ti::TiValue getAccessibilityHidden();
	virtual Ti::TiValue getAccessibilityHint();
	virtual Ti::TiValue getAccessibilityLabel();
	virtual Ti::TiValue getAccessibilityValue();
	virtual Ti::TiValue getAnchorPoint();
	virtual Ti::TiValue getAnimatedCenter();
	virtual Ti::TiValue getBackgroundColor();
	virtual Ti::TiValue getBackgroundDisabledColor();
	virtual Ti::TiValue getBackgroundDisabledImage();
	virtual Ti::TiValue getBackgroundFocusedColor();
	virtual Ti::TiValue getBackgroundFocusedImage();
	virtual Ti::TiValue getBackgroundGradient();
	virtual Ti::TiValue getBackgroundImage();
	virtual Ti::TiValue getBackgroundRepeat();
	virtual Ti::TiValue getBackgroundLeftCap();
	virtual Ti::TiValue getBackgroundSelectedColor();
	virtual Ti::TiValue getBackgroundSelectedImage();
	virtual Ti::TiValue getBackgroundTopCap();
	virtual Ti::TiValue getBorderColor();
	virtual Ti::TiValue getBorderRadius();
	virtual Ti::TiValue getBorderWidth();
	virtual Ti::TiValue getBottom();
	virtual Ti::TiValue getCenter();
	virtual Ti::TiValue getChildren();
	virtual Ti::TiValue getEnabled();
	virtual Ti::TiValue getFocusable();
	virtual Ti::TiValue getHeight();
	virtual Ti::TiValue getLeft();
	virtual Ti::TiValue getLayout();
	virtual Ti::TiValue getOpacity();
	virtual Ti::TiValue getRight();
	virtual Ti::TiValue getRect();
	virtual Ti::TiValue getSize();
	virtual Ti::TiValue getSoftKeyboardOnFocus();
	virtual Ti::TiValue getTop();
	virtual Ti::TiValue getTouchEnabled();
	virtual Ti::TiValue getTransform();
	virtual Ti::TiValue getVisible();
	virtual Ti::TiValue getWidth();
	virtual Ti::TiValue getHorizontalWrap();
	virtual Ti::TiValue getZIndex();
	virtual Ti::TiValue getKeepScreenOn();
	virtual Ti::TiValue getContextMenus();
	virtual Ti::TiValue getTiParent();

	virtual Ti::TiValue add(Ti::TiValue);
	virtual Ti::TiValue animate(Ti::TiValue);
	virtual Ti::TiValue finishLayout(Ti::TiValue);
	virtual Ti::TiValue hide(Ti::TiValue);
	virtual Ti::TiValue remove(Ti::TiValue);
	virtual Ti::TiValue removeAllChildren(Ti::TiValue);
	virtual Ti::TiValue show(Ti::TiValue);
	virtual Ti::TiValue startLayout(Ti::TiValue);
	virtual Ti::TiValue toImage(Ti::TiValue);
	virtual Ti::TiValue updateLayout(Ti::TiValue);
	virtual Ti::TiValue convertPointToView(Ti::TiValue);


	EXPOSE_SETTER(TiViewProxy, setAccessibilityHidden)
	EXPOSE_SETTER(TiViewProxy, setAccessibilityHint)
	EXPOSE_SETTER(TiViewProxy, setAccessibilityLabel)
	EXPOSE_SETTER(TiViewProxy, setAccessibilityValue)
	EXPOSE_SETTER(TiViewProxy, setAnchorPoint)
	EXPOSE_SETTER(TiViewProxy, setBackgroundColor)
	EXPOSE_SETTER(TiViewProxy, setBackgroundDisabledColor)
	EXPOSE_SETTER(TiViewProxy, setBackgroundDisabledImage)
	EXPOSE_SETTER(TiViewProxy, setBackgroundFocusedColor)
	EXPOSE_SETTER(TiViewProxy, setBackgroundFocusedImage)
	EXPOSE_SETTER(TiViewProxy, setBackgroundGradient)
	EXPOSE_SETTER(TiViewProxy, setBackgroundImage)
	EXPOSE_SETTER(TiViewProxy, setBackgroundRepeat)
	EXPOSE_SETTER(TiViewProxy, setBackgroundLeftCap)
	EXPOSE_SETTER(TiViewProxy, setBackgroundSelectedColor)
	EXPOSE_SETTER(TiViewProxy, setBackgroundSelectedImage)
	EXPOSE_SETTER(TiViewProxy, setBackgroundTopCap)
	EXPOSE_SETTER(TiViewProxy, setBorderColor)
	EXPOSE_SETTER(TiViewProxy, setBorderRadius)
	EXPOSE_SETTER(TiViewProxy, setBorderWidth)
	EXPOSE_SETTER(TiViewProxy, setBottom)
	EXPOSE_SETTER(TiViewProxy, setCenter)
	EXPOSE_SETTER(TiViewProxy, setEnabled)
	EXPOSE_SETTER(TiViewProxy, setFocusable)
	EXPOSE_SETTER(TiViewProxy, setHeight)
	EXPOSE_SETTER(TiViewProxy, setLeft)
	EXPOSE_SETTER(TiViewProxy, setLayout)
	EXPOSE_SETTER(TiViewProxy, setOpacity)
	EXPOSE_SETTER(TiViewProxy, setRight)
	EXPOSE_SETTER(TiViewProxy, setSoftKeyboardOnFocus)
	EXPOSE_SETTER(TiViewProxy, setTop)
	EXPOSE_SETTER(TiViewProxy, setTouchEnabled)
	EXPOSE_SETTER(TiViewProxy, setTransform)
	EXPOSE_SETTER(TiViewProxy, setVisible)
	EXPOSE_SETTER(TiViewProxy, setWidth)
	EXPOSE_SETTER(TiViewProxy, setHorizontalWrap)
	EXPOSE_SETTER(TiViewProxy, setZIndex)
	EXPOSE_SETTER(TiViewProxy, setKeepScreenOn)
	EXPOSE_SETTER(TiViewProxy, setContextMenus)

	EXPOSE_GETTER(TiViewProxy, getAccessibilityHidden)
	EXPOSE_GETTER(TiViewProxy, getAccessibilityHint)
	EXPOSE_GETTER(TiViewProxy, getAccessibilityLabel)
	EXPOSE_GETTER(TiViewProxy, getAccessibilityValue)
	EXPOSE_GETTER(TiViewProxy, getAnchorPoint)
	EXPOSE_GETTER(TiViewProxy, getAnimatedCenter)
	EXPOSE_GETTER(TiViewProxy, getBackgroundColor)
	EXPOSE_GETTER(TiViewProxy, getBackgroundDisabledColor)
	EXPOSE_GETTER(TiViewProxy, getBackgroundDisabledImage)
	EXPOSE_GETTER(TiViewProxy, getBackgroundFocusedColor)
	EXPOSE_GETTER(TiViewProxy, getBackgroundFocusedImage)
	EXPOSE_GETTER(TiViewProxy, getBackgroundGradient)
	EXPOSE_GETTER(TiViewProxy, getBackgroundImage)
	EXPOSE_GETTER(TiViewProxy, getBackgroundRepeat)
	EXPOSE_GETTER(TiViewProxy, getBackgroundLeftCap)
	EXPOSE_GETTER(TiViewProxy, getBackgroundSelectedColor)
	EXPOSE_GETTER(TiViewProxy, getBackgroundSelectedImage)
	EXPOSE_GETTER(TiViewProxy, getBackgroundTopCap)
	EXPOSE_GETTER(TiViewProxy, getBorderColor)
	EXPOSE_GETTER(TiViewProxy, getBorderRadius)
	EXPOSE_GETTER(TiViewProxy, getBorderWidth)
	EXPOSE_GETTER(TiViewProxy, getBottom)
	EXPOSE_GETTER(TiViewProxy, getCenter)
	EXPOSE_GETTER(TiViewProxy, getChildren)
	EXPOSE_GETTER(TiViewProxy, getEnabled)
	EXPOSE_GETTER(TiViewProxy, getFocusable)
	EXPOSE_GETTER(TiViewProxy, getHeight)
	EXPOSE_GETTER(TiViewProxy, getLeft)
	EXPOSE_GETTER(TiViewProxy, getLayout)
	EXPOSE_GETTER(TiViewProxy, getOpacity)
	EXPOSE_GETTER(TiViewProxy, getRight)
	EXPOSE_GETTER(TiViewProxy, getRect)
	EXPOSE_GETTER(TiViewProxy, getSize)
	EXPOSE_GETTER(TiViewProxy, getSoftKeyboardOnFocus)
	EXPOSE_GETTER(TiViewProxy, getTop)
	EXPOSE_GETTER(TiViewProxy, getTouchEnabled)
	EXPOSE_GETTER(TiViewProxy, getTransform)
	EXPOSE_GETTER(TiViewProxy, getVisible)
	EXPOSE_GETTER(TiViewProxy, getWidth)
	EXPOSE_GETTER(TiViewProxy, getHorizontalWrap)
	EXPOSE_GETTER(TiViewProxy, getZIndex)
	EXPOSE_GETTER(TiViewProxy, getKeepScreenOn)
	EXPOSE_GETTER(TiViewProxy, getContextMenus)
	EXPOSE_GETTER(TiViewProxy, getTiParent)

	EXPOSE_METHOD(TiViewProxy, add)
	EXPOSE_METHOD(TiViewProxy, animate)
	EXPOSE_METHOD(TiViewProxy, finishLayout)
	EXPOSE_METHOD(TiViewProxy, hide)
	EXPOSE_METHOD(TiViewProxy, remove)
	EXPOSE_METHOD(TiViewProxy, removeAllChildren)
	EXPOSE_METHOD(TiViewProxy, show)
	EXPOSE_METHOD(TiViewProxy, startLayout)
	EXPOSE_METHOD(TiViewProxy, toImage)
	EXPOSE_METHOD(TiViewProxy, updateLayout)
	EXPOSE_METHOD(TiViewProxy, convertPointToView)

	virtual void fireEvent(QString, Ti::TiEventParameters);

	TiView *view;
	bool isDestroyed;
	QList<Ti::TiViewProxy*> _childViewsProxies;
	bb::cascades::Control* getChildControl();
	Ti::TiViewProxy *getParentProxy();
protected:
	void setView(TiView *);
private:
	Ti::TiViewProxy *_parentProxy;
	bool _backgroundImageRepeat;
	QString _backgroundImageUrl;
	void setBackground();
};

class TiViewProxyEventHandler : public QObject
{
	Q_OBJECT;
public:
	TiViewProxyEventHandler(TiViewProxy*);
	virtual ~TiViewProxyEventHandler();
	TiViewProxy* _proxy;
public slots:
	void onViewDestroyed(QObject*);
};
}
#endif /* TIVIEWPROXY_H_ */
