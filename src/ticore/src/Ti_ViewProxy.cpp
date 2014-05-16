/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "Ti_View.h"
#include "Ti_ViewProxy.h"
#include "Ti_Value.h"
#include "Ti_Constants.h"
#include "Ti_Macros.h"
#include "Ti_Callback.h"
#include "Ti_AnimationProxy.h"

#include "TitaniumLayout.h"
#include <bb/cascades/ImagePaint>
#include <bb/cascades/ActionSet>

#include "TiUIBase.h"
#include "TiObject.h"
#include "NativeObject.h"

Ti::TiViewProxy::TiViewProxy(const char* name)
: Ti::TiProxy(name),
view(NULL),
isDestroyed(true),
_backgroundImageRepeat(false),
_backgroundImageUrl(""),
_parentProxy(NULL)
{

	createPropertyGetter("animatedCenter", _getAnimatedCenter);
	createPropertyGetter("children", _getChildren);
	createPropertyGetter("rect", _getRect);
	createPropertyGetter("size", _getSize);
	createPropertyGetter("parent", _getTiParent);

	createPropertySetterGetter("accessibilityHidden", _setAccessibilityHidden,  _getAccessibilityHidden);
	createPropertySetterGetter("accessibilityHint", _setAccessibilityHint,  _getAccessibilityHint);
	createPropertySetterGetter("accessibilityLabel", _setAccessibilityLabel,  _getAccessibilityLabel);
	createPropertySetterGetter("accessibilityValue", _setAccessibilityValue,  _getAccessibilityValue);
	createPropertySetterGetter("anchorPoint", _setAnchorPoint,  _getAnchorPoint);
	createPropertySetterGetter("backgroundColor", _setBackgroundColor,  _getBackgroundColor);
	createPropertySetterGetter("backgroundDisabledColor", _setBackgroundDisabledColor,  _getBackgroundDisabledColor);
	createPropertySetterGetter("backgroundDisabledImage", _setBackgroundDisabledImage,  _getBackgroundDisabledImage);
	createPropertySetterGetter("backgroundFocusedColor", _setBackgroundFocusedColor,  _getBackgroundFocusedColor);
	createPropertySetterGetter("backgroundFocusedImage", _setBackgroundFocusedImage,  _getBackgroundFocusedImage);
	createPropertySetterGetter("backgroundGradient", _setBackgroundGradient,  _getBackgroundGradient);
	createPropertySetterGetter("backgroundImage", _setBackgroundImage,  _getBackgroundImage);
	createPropertySetterGetter("backgroundRepeat", _setBackgroundRepeat,  _getBackgroundRepeat);
	createPropertySetterGetter("backgroundLeftCap", _setBackgroundLeftCap,  _getBackgroundLeftCap);
	createPropertySetterGetter("backgroundSelectedColor", _setBackgroundSelectedColor,  _getBackgroundSelectedColor);
	createPropertySetterGetter("backgroundSelectedImage", _setBackgroundSelectedImage,  _getBackgroundSelectedImage);
	createPropertySetterGetter("backgroundTopCap", _setBackgroundTopCap,  _getBackgroundTopCap);
	createPropertySetterGetter("borderColor", _setBorderColor,  _getBorderColor);
	createPropertySetterGetter("borderRadius", _setBorderRadius,  _getBorderRadius);
	createPropertySetterGetter("borderWidth", _setBorderWidth,  _getBorderWidth);
	createPropertySetterGetter("bottom", _setBottom,  _getBottom);
	createPropertySetterGetter("center", _setCenter,  _getCenter);
	createPropertySetterGetter("contextMenus", _setContextMenus,  _getContextMenus);
	createPropertySetterGetter("enabled", _setEnabled,  _getEnabled);
	createPropertySetterGetter("focusable", _setFocusable,  _getFocusable);
	createPropertySetterGetter("height", _setHeight,  _getHeight);
	createPropertySetterGetter("left", _setLeft,  _getLeft);
	createPropertySetterGetter("layout", _setLayout,  _getLayout);
	createPropertySetterGetter("opacity", _setOpacity,  _getOpacity);
	createPropertySetterGetter("right", _setRight,  _getRight);
	createPropertySetterGetter("softKeyboardOnFocus", _setSoftKeyboardOnFocus,  _getSoftKeyboardOnFocus);
	createPropertySetterGetter("top", _setTop,  _getTop);
	createPropertySetterGetter("touchEnabled", _setTouchEnabled,  _getTouchEnabled);
	createPropertySetterGetter("transform", _setTransform,  _getTransform);
	createPropertySetterGetter("visible", _setVisible,  _getVisible);
	createPropertySetterGetter("width", _setWidth,  _getWidth);
	createPropertySetterGetter("horizontalWrap", _setHorizontalWrap,  _getHorizontalWrap);
	createPropertySetterGetter("zIndex", _setZIndex,  _getZIndex);
	createPropertySetterGetter("keepScreenOn", _setKeepScreenOn,  _getKeepScreenOn);

	createPropertyFunction("add", _add);
	createPropertyFunction("animate", _animate);
	createPropertyFunction("finishLayout", _finishLayout);
	createPropertyFunction("hide", _hide);
	createPropertyFunction("remove", _remove);
	createPropertyFunction("removeAllChildren", _removeAllChildren);
	createPropertyFunction("show", _show);
	createPropertyFunction("startLayout", _startLayout);
	createPropertyFunction("toImage", _toImage);
	createPropertyFunction("updateLayout", _updateLayout);
	createPropertyFunction("convertPointToView", _convertPointToView);

}

Ti::TiViewProxy *Ti::TiViewProxy::getParentProxy()
{
	return _parentProxy;
}


void Ti::TiViewProxy::fireEvent(QString str, Ti::TiEventParameters params)
{
	Ti::TiProxy::fireEvent(str, params);
}

void Ti::TiViewProxy::setView(Ti::TiView *_view)
{
	_view->setTiLayout();
	view = _view;
	isDestroyed = false;
    QObject::connect(view, SIGNAL(destroyed(QObject*)), new Ti::TiViewProxyEventHandler(this), SLOT(onViewDestroyed(QObject*)));
}

Ti::TiViewProxy::~TiViewProxy()
{
	HandleScope scope;
	foreach(Ti::TiViewProxy* child, _childViewsProxies)
	{
		child->makeWeak();
	}
	_childViewsProxies.clear();
	_jsObject->Delete(String::New("children"));

	if(!isDestroyed)
	{
		delete view;
	}
}

Ti::TiView *Ti::TiViewProxy::getView()
{
	if(view == NULL) {
		setView(new Ti::TiView(this));
	}
	return view;
}

bb::cascades::Control* Ti::TiViewProxy::getChildControl()
{
	if(view->childControl != NULL)
		return view->childControl;
	return view;
}
void Ti::TiViewProxy::onEventAdded(QString eventName)
{
	getView()->onEventAdded(eventName);
	Ti::TiProxy::onEventAdded(eventName);
}

void Ti::TiViewProxy::setWidth(Ti::TiValue value)
{
	getView()->_setWidth(value.toString());
}
void Ti::TiViewProxy::setHeight(Ti::TiValue value)
{
	getView()->_setHeight(value.toString());
}
void Ti::TiViewProxy::setTop(Ti::TiValue value)
{
	getView()->_setTop(value.toString());
}
void Ti::TiViewProxy::setBottom(Ti::TiValue value)
{
	getView()->_setBottom(value.toString());
}
void Ti::TiViewProxy::setLeft(Ti::TiValue value)
{
	getView()->_setLeft(value.toString());
}
void Ti::TiViewProxy::setRight(Ti::TiValue value)
{
	getView()->_setRight(value.toString());
}
void Ti::TiViewProxy::setLayout(Ti::TiValue value) {
	getView()->_setLayout(value.toString());
}

Ti::TiValue Ti::TiViewProxy::getWidth()
{
	Ti::TiValue val;
	val.setString(getView()->_width);
	return val;
}
Ti::TiValue Ti::TiViewProxy::getHeight()
{
	Ti::TiValue val;
	val.setString(getView()->_height);
	return val;
}
Ti::TiValue Ti::TiViewProxy::getTop()
{
	Ti::TiValue val;
	val.setString(getView()->_top);
	return val;
}
Ti::TiValue Ti::TiViewProxy::getBottom()
{
	Ti::TiValue val;
	val.setString(getView()->_bottom);
	return val;
}
Ti::TiValue Ti::TiViewProxy::getLeft()
{
	Ti::TiValue val;
	val.setString(getView()->_left);
	return val;
}
Ti::TiValue Ti::TiViewProxy::getRight()
{
	Ti::TiValue val;
	val.setString(getView()->_right);
	return val;
}

void Ti::TiViewProxy::setAccessibilityHidden(Ti::TiValue)
{
}
void Ti::TiViewProxy::setAccessibilityHint(Ti::TiValue)
{
}
void Ti::TiViewProxy::setAccessibilityLabel(Ti::TiValue)
{
}
void Ti::TiViewProxy::setAccessibilityValue(Ti::TiValue)
{
}
void Ti::TiViewProxy::setAnchorPoint(Ti::TiValue value)
{
	if(!value.isMap()) return;
	QMap<QString, Ti::TiValue> map = value.toMap();
	Ti::TiValue xValue = map.value("x");
	Ti::TiValue yValue = map.value("y");
	view->setPivot(xValue.toNumber(), yValue.toNumber());
}
void Ti::TiViewProxy::setBackgroundColor(Ti::TiValue value)
{
	view->setBackground(value.toColor());
}
void Ti::TiViewProxy::setBackgroundDisabledColor(Ti::TiValue)
{
}
void Ti::TiViewProxy::setBackgroundDisabledImage(Ti::TiValue)
{
}
void Ti::TiViewProxy::setBackgroundFocusedColor(Ti::TiValue)
{
}
void Ti::TiViewProxy::setBackgroundFocusedImage(Ti::TiValue)
{
}
void Ti::TiViewProxy::setBackgroundGradient(Ti::TiValue)
{
}

void Ti::TiViewProxy::setBackground()
{
	_backgroundImageUrl.replace("//", "/");

	bb::cascades::RepeatPattern::Type type;
	if(_backgroundImageRepeat)
		type = bb::cascades::RepeatPattern::XY;
	else
		type = bb::cascades::RepeatPattern::Fill;

	bb::cascades::ImagePaint bgImg = bb::cascades::ImagePaint(QUrl(_backgroundImageUrl), type);

	view->setBackground(bgImg);
}

void Ti::TiViewProxy::setBackgroundImage(Ti::TiValue value)
{
	_backgroundImageUrl = Ti::TiHelper::getAssetPath(value.toString());
	setBackground();
}
void Ti::TiViewProxy::setBackgroundRepeat(Ti::TiValue value)
{
	_backgroundImageRepeat = value.toBool();
	setBackground();
}
void Ti::TiViewProxy::setBackgroundLeftCap(Ti::TiValue)
{
}
void Ti::TiViewProxy::setBackgroundSelectedColor(Ti::TiValue)
{
}
void Ti::TiViewProxy::setBackgroundSelectedImage(Ti::TiValue)
{
}
void Ti::TiViewProxy::setBackgroundTopCap(Ti::TiValue)
{
}
void Ti::TiViewProxy::setBorderColor(Ti::TiValue)
{
}
void Ti::TiViewProxy::setBorderRadius(Ti::TiValue)
{
}
void Ti::TiViewProxy::setBorderWidth(Ti::TiValue)
{
}
void Ti::TiViewProxy::setCenter(Ti::TiValue)
{
}
void Ti::TiViewProxy::setContextMenus(Ti::TiValue value)
{
	if(!value.isList()) return;
	QList<Ti::TiValue> allValues = value.toList();
	foreach(Ti::TiValue current, allValues)
	{
		if(!current.isProxy()) continue;
		Ti::TiProxy* menuProxy = current.toProxy();
		if(menuProxy->__data__ == NULL) return;

		bb::cascades::ActionSet *menu = (bb::cascades::ActionSet*)menuProxy->__data__;
		getChildControl()->addActionSet(menu);
	}
}
void Ti::TiViewProxy::setEnabled(Ti::TiValue value)
{
	getChildControl()->setEnabled(value.toBool());
}
void Ti::TiViewProxy::setFocusable(Ti::TiValue value)
{
	if(value.toBool())
		getChildControl()->setFocusPolicy(bb::cascades::FocusPolicy::KeyAndTouch);
	else
		getChildControl()->setFocusPolicy(bb::cascades::FocusPolicy::None);
}
void Ti::TiViewProxy::setOpacity(Ti::TiValue value)
{
	getChildControl()->setOpacity(value.toNumber());
}
void Ti::TiViewProxy::setSoftKeyboardOnFocus(Ti::TiValue)
{
}
void Ti::TiViewProxy::setTouchEnabled(Ti::TiValue value)
{
	if(value.toBool())
		getChildControl()->setTouchPropagationMode(bb::cascades::TouchPropagationMode::Full);
	else
		getChildControl()->setTouchPropagationMode(bb::cascades::TouchPropagationMode::PassThrough);
}
void Ti::TiViewProxy::setTransform(Ti::TiValue)
{
}
void Ti::TiViewProxy::setVisible(Ti::TiValue value)
{
	getChildControl()->setVisible(value.toBool());
}
void Ti::TiViewProxy::setHorizontalWrap(Ti::TiValue)
{
}
void Ti::TiViewProxy::setZIndex(Ti::TiValue value)
{
	getView()->setZIndex((int)value.toNumber());
}
void Ti::TiViewProxy::setKeepScreenOn(Ti::TiValue)
{
}

Ti::TiValue Ti::TiViewProxy::getAccessibilityHidden()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getAccessibilityHint()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getAccessibilityLabel()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getAccessibilityValue()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getAnchorPoint()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getAnimatedCenter()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getBackgroundColor()
{
	return Ti::TiValue();
}
Ti::TiValue Ti::TiViewProxy::getBackgroundDisabledColor()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getBackgroundDisabledImage()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getBackgroundFocusedColor()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getBackgroundFocusedImage()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getBackgroundGradient()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getBackgroundImage()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getBackgroundRepeat()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getBackgroundLeftCap()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getBackgroundSelectedColor()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getBackgroundSelectedImage()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getBackgroundTopCap()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getBorderColor()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getBorderRadius()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getBorderWidth()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getCenter()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getContextMenus()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getEnabled()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getFocusable()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getLayout()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getOpacity()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getRect()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

Ti::TiValue Ti::TiViewProxy::getTiParent()
{
	Ti::TiValue val;
	if(_parentProxy != NULL) {
		val.setProxy(_parentProxy);
	}
	return val;
}
Ti::TiValue Ti::TiViewProxy::getSize()
{
	Ti::TiValue val;

	Ti::TiValue width;
	width.setNumber(Ti::TiHelper::PixelsToDP(getView()->viewLayout->_layoutNode.element._measuredWidth));
	Ti::TiValue height;
	height.setNumber(Ti::TiHelper::PixelsToDP(getView()->viewLayout->_layoutNode.element._measuredHeight));

	QMap<QString, Ti::TiValue> size;
	size["width"] = width;
	size["height"] = height;
	val.setMap(size);
	return val;
}
Ti::TiValue Ti::TiViewProxy::getSoftKeyboardOnFocus()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getTouchEnabled()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getTransform()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getVisible()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getHorizontalWrap()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getZIndex()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::getKeepScreenOn()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}


Ti::TiValue Ti::TiViewProxy::add(Ti::TiValue value)
{
	if(value.isProxy())
	{
		Ti::TiViewProxy *childProxy = static_cast<Ti::TiViewProxy*>(value.toProxy());
		childProxy->clearWeak();
		_childViewsProxies.append(childProxy);
		Ti::TiView* childView = childProxy->getView();
		Ti::TiView* thisView = getView();
		thisView->add(childView);
		childProxy->_parentProxy = this;
	}
	else
	{
        TiObject* addObj = TiObject::getTiObjectFromJsObject(value.toJSValue());
        TiUIBase* uiObj = (TiUIBase*) addObj;
        NativeObject* childNO = uiObj->getNativeObject();
        getView()->addOldObject(childNO);

       Local<Value> children = _jsObject->Get(String::New("children"));
       Local<Array> array;
       if(children.IsEmpty() || children->IsUndefined())
       {
    	   array = Array::New();
    	   _jsObject->Set(String::New("children"), array);
       }
       else
       {
    	   array = Local<Array>::Cast(children);
       }
       array->Set(array->Length(), value.toJSValue());
       childNO->release();

	}

	Ti::TiValue val;
	val.setUndefined();
	return val;
}

Ti::TiValue Ti::TiViewProxy::animate(Ti::TiValue val)
{
	if(val.isProxy()) {
		Ti::TiAnimationProxy *proxy = static_cast<Ti::TiAnimationProxy*>(val.toProxy());
		proxy->animate(this, NULL);
	}
	Ti::TiValue result;
	result.setUndefined();
	return result;
}
Ti::TiValue Ti::TiViewProxy::finishLayout(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::hide(Ti::TiValue)
{
	getView()->setVisible(false);
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::remove(Ti::TiValue value)
{
	Ti::TiValue val;
	val.setUndefined();

	Ti::TiViewProxy *childProxy = static_cast<Ti::TiViewProxy*>(value.toProxy());
	if(!_childViewsProxies.contains(childProxy)) return val;

	Ti::TiView* childView = childProxy->getView();
	Ti::TiView* thisView = getView();
	childProxy->makeWeak();
	thisView->remove(childView);
	_childViewsProxies.removeOne(childProxy);

	childProxy->_parentProxy = NULL;
    Local<Value> children = _jsObject->Get(String::New("children"));
    if(!children.IsEmpty() && !children->IsUndefined())
    {
    	Local<Array> array = Local<Array>::Cast(children);
    	for(int i = 0, len = array->Length(); i < len; i++) {
    		if(array->Get(i) == value.toJSValue())
    		{
    	    	array->Delete(i);
    	    	break;
    		}
    	}
    }

	return val;
}

TI_GETTER_DEFER(Ti::TiViewProxy, getChildren)
Ti::TiValue Ti::TiViewProxy::removeAllChildren(Ti::TiValue)
{
	foreach(Ti::TiViewProxy* child, _childViewsProxies)
	{
		remove(Ti::TiValue(child->_jsObject));
	}
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::show(Ti::TiValue)
{
	getView()->setVisible(true);
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::startLayout(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::toImage(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue Ti::TiViewProxy::updateLayout(Ti::TiValue val)
{
	return applyProperties(val);
}
Ti::TiValue Ti::TiViewProxy::convertPointToView(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

Ti::TiViewProxyEventHandler::TiViewProxyEventHandler(Ti::TiViewProxy* proxy)
{
	_proxy = proxy;
}
Ti::TiViewProxyEventHandler::~TiViewProxyEventHandler()
{
}

void Ti::TiViewProxyEventHandler::onViewDestroyed(QObject*)
{
	_proxy->isDestroyed = true;
}
