/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIAnimationProxy.h"
#include <bb/cascades/ImplicitAnimationController>

namespace TiUI {

TiUIAnimationProxy::TiUIAnimationProxy(const char* name) :
		Ti::TiAnimationProxy(name),
		_transitionAnimation(NULL),
		_fadeAnimation(NULL),
		_scaleAnimation(NULL),
		_control(NULL)
{
	// TODO Auto-generated constructor stub

	createPropertySetterGetter("anchorPoint", _setAnchorPoint, _getAnchorPoint);
	createPropertySetterGetter("autoreverse", _setAutoreverse, _getAutoreverse);
	createPropertySetterGetter("backgroundColor", _setBackgroundColor, _getBackgroundColor);
	createPropertySetterGetter("bottom", _setBottom, _getBottom);
	createPropertySetterGetter("center", _setCenter, _getCenter);
	createPropertySetterGetter("color", _setColor, _getColor);
	createPropertySetterGetter("curve", _setCurve, _getCurve);
	createPropertySetterGetter("delay", _setDelay, _getDelay);
	createPropertySetterGetter("duration", _setDuration, _getDuration);
	createPropertySetterGetter("height", _setHeight, _getHeight);
	createPropertySetterGetter("left", _setLeft, _getLeft);
	createPropertySetterGetter("opacity", _setOpacity, _getOpacity);
	createPropertySetterGetter("opaque", _setOpaque, _getOpaque);
	createPropertySetterGetter("repeat", _setRepeat, _getRepeat);
	createPropertySetterGetter("right", _setRight, _getRight);
	createPropertySetterGetter("top", _setTop, _getTop);
	createPropertySetterGetter("transform", _setTransform, _getTransform);
	createPropertySetterGetter("transition", _setTransition, _getTransition);
	createPropertySetterGetter("view", _setView, _getView);
	createPropertySetterGetter("visible", _setVisible, _getVisible);
	createPropertySetterGetter("width", _setWidth, _getWidth);
	createPropertySetterGetter("zIndex", _setZIndex, _getZIndex);

}
TiUIAnimationProxy::~TiUIAnimationProxy() {
	// TODO Auto-generated destructor stub
}

TI_GETTER_DEFER(TiUIAnimationProxy, getAnchorPoint)
void TiUIAnimationProxy::setAnchorPoint(Ti::TiValue val)
{
	_properties[AnchorPoint] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getAutoreverse)
void TiUIAnimationProxy::setAutoreverse(Ti::TiValue val)
{
	_properties[AutoReverse] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getBackgroundColor)
void TiUIAnimationProxy::setBackgroundColor(Ti::TiValue val)
{
	_properties[BackgroundColor] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getBottom)
void TiUIAnimationProxy::setBottom(Ti::TiValue val)
{
	_properties[Bottom] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getCenter)
void TiUIAnimationProxy::setCenter(Ti::TiValue val)
{
	_properties[Center] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getColor)
void TiUIAnimationProxy::setColor(Ti::TiValue val)
{
	_properties[Color] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getCurve)
void TiUIAnimationProxy::setCurve(Ti::TiValue val)
{
	_properties[Curve] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getDelay)
void TiUIAnimationProxy::setDelay(Ti::TiValue val)
{
	_properties[Delay] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getDuration)
void TiUIAnimationProxy::setDuration(Ti::TiValue val)
{
	_properties[Duration] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getHeight)
void TiUIAnimationProxy::setHeight(Ti::TiValue val)
{
	_properties[Height] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getLeft)
void TiUIAnimationProxy::setLeft(Ti::TiValue val)
{
	_properties[Left] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getOpacity)
void TiUIAnimationProxy::setOpacity(Ti::TiValue val)
{
	_properties[Opacity] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getOpaque)
void TiUIAnimationProxy::setOpaque(Ti::TiValue val)
{
	_properties[Opaque] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getRepeat)
void TiUIAnimationProxy::setRepeat(Ti::TiValue val)
{
	_properties[Repeat] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getRight)
void TiUIAnimationProxy::setRight(Ti::TiValue val)
{
	_properties[Right] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getTop)
void TiUIAnimationProxy::setTop(Ti::TiValue val)
{
	_properties[Top] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getTransform)
void TiUIAnimationProxy::setTransform(Ti::TiValue val)
{
	_properties[Transform] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getTransition)
void TiUIAnimationProxy::setTransition(Ti::TiValue val)
{
	_properties[Transition] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getView)
void TiUIAnimationProxy::setView(Ti::TiValue val)
{
	_properties[View] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getVisible)
void TiUIAnimationProxy::setVisible(Ti::TiValue val)
{
	_properties[Visible] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getWidth)
void TiUIAnimationProxy::setWidth(Ti::TiValue val)
{
	_properties[Width] = val.toString();
}
TI_GETTER_DEFER(TiUIAnimationProxy, getZIndex)
void TiUIAnimationProxy::setZIndex(Ti::TiValue val)
{
	_properties[zIndex] = val.toString();
}

QMap<TiUIAnimationProxy::Type, QString> TiUIAnimationProxy::getProperties()
{
	return _properties;
}

void TiUIAnimationProxy::animate(Ti::TiViewProxy* viewProxy, Ti::TiCallback* callback)
{
	Ti::TiView* tiView = viewProxy->getView();
//	_control = tiView->childControl;
//	if(_control == NULL)
//	{
		_control = tiView;
//	}
	Ti::Layout::Node layoutNode = tiView->viewLayout->_layoutNode;

	double objectX = layoutNode.element._measuredLeft;
	double objectY = layoutNode.element._measuredTop;
	double objectWidth = layoutNode.element._measuredWidth;
	double objectHeight = layoutNode.element._measuredHeight;
	double parentWidth = layoutNode.parent->element._measuredWidth;
	double parentHeight = layoutNode.parent->element._measuredHeight;


	if(_properties.contains(Width))
	{
		float value = Ti::Layout::ParseProperty::getDimensionValue(_properties[Width].toStdString(), Ti::TiHelper::PPI());
		getScaleAnimation()->setToX(value / objectWidth);
		if(layoutNode.properties.right.value > 0) {
			_control->setPivotX( objectWidth / 2);
		} else
		if(layoutNode.properties.left.value > 0) {
			_control->setPivotX( -(objectWidth / 2) );
		}
	}
	if(_properties.contains(Height)) {
		float value = Ti::Layout::ParseProperty::getDimensionValue(_properties[Height].toStdString(), Ti::TiHelper::PPI());
		getScaleAnimation()->setToY(value / objectHeight);
		if(layoutNode.properties.top.value > 0) {
			_control->setPivotY(-(objectHeight/2));
		} else
		if(layoutNode.properties.bottom.value > 0) {
			_control->setPivotY(objectHeight/2);
		}
	}
	if(_properties.contains(Left)) {
		float value = Ti::Layout::ParseProperty::getDimensionValue(_properties[Left].toStdString(), Ti::TiHelper::PPI());
		getTranslateAnimation()->setToX(-objectX + value);
	}

	if(_properties.contains(Top)) {
		float value = Ti::Layout::ParseProperty::getDimensionValue(_properties[Top].toStdString(), Ti::TiHelper::PPI());
		getTranslateAnimation()->setToY(-objectY + value);
	}
	if(_properties.contains(Right)) {
		float value = Ti::Layout::ParseProperty::getDimensionValue(_properties[Right].toStdString(), Ti::TiHelper::PPI());
		getTranslateAnimation()->setToX(-objectX + parentWidth - objectWidth - value);
	}
	if(_properties.contains(Bottom)) {
		float value = Ti::Layout::ParseProperty::getDimensionValue(_properties[Bottom].toStdString(), Ti::TiHelper::PPI());
		getTranslateAnimation()->setToY(-objectY + parentHeight - objectHeight - value);
	}
	if(_properties.contains(Opacity)) {
		getFadeAnimation()->setFromOpacity(_control->opacity());
		getFadeAnimation()->setToOpacity(_properties[Opacity].toFloat(NULL));
	}
	if(_properties.contains(Duration)) {
		bool ok;
		int value = _properties[Duration].toInt(&ok);
		if(_transitionAnimation != NULL)
			_transitionAnimation->setDuration(value);
		if(_fadeAnimation != NULL)
			_fadeAnimation->setDuration(value);
		if(_scaleAnimation != NULL)
			_scaleAnimation->setDuration(value);
	}
	if(_properties.contains(Delay)) {
		bool ok;
		int value = _properties[Delay].toInt(&ok);
		if(_transitionAnimation != NULL)
			_transitionAnimation->setDelay(value);
		if(_fadeAnimation != NULL)
			_fadeAnimation->setDelay(value);
		if(_scaleAnimation != NULL)
			_scaleAnimation->setDelay(value);
	}

	if(_properties.contains(Repeat)) {
		bool ok;
		int value = _properties[Repeat].toInt(&ok);
		if(_transitionAnimation != NULL)
			_transitionAnimation->setRepeatCount(value);
		if(_fadeAnimation != NULL)
			_fadeAnimation->setRepeatCount(value);
		if(_scaleAnimation != NULL)
			_scaleAnimation->setRepeatCount(value);
	}

	TiUIAnimationEventHandler *event = new TiUIAnimationEventHandler(this, viewProxy, callback);
	if(_transitionAnimation != NULL) {
		_control->addAnimation(_transitionAnimation);
	    QObject::connect(_transitionAnimation, SIGNAL(ended()), event, SLOT(onAnimationEnd()));
	    _transitionAnimation->play();
	}
	if(_fadeAnimation != NULL) {
		_control->addAnimation(_fadeAnimation);
		QObject::connect(_fadeAnimation, SIGNAL(ended()), event, SLOT(onAnimationEnd()));
	    _fadeAnimation->play();
	}
	if(_scaleAnimation != NULL) {
		_control->addAnimation(_scaleAnimation);
		QObject::connect(_scaleAnimation, SIGNAL(ended()), event, SLOT(onAnimationEnd()));
		_scaleAnimation->play();
	}
}

void TiUIAnimationProxy::removeAnimations()
{
	if(_control == NULL) return;
	if(_scaleAnimation != NULL)
		_control->removeAnimation(_scaleAnimation);
	if(_transitionAnimation != NULL)
		_control->removeAnimation(_transitionAnimation);
	if(_fadeAnimation != NULL)
		_control->removeAnimation(_fadeAnimation);
}

bb::cascades::TranslateTransition *TiUIAnimationProxy::getTranslateAnimation()
{
	if(_transitionAnimation == NULL)
		_transitionAnimation =  new bb::cascades::TranslateTransition();
	return _transitionAnimation;
}
bb::cascades::FadeTransition *TiUIAnimationProxy::getFadeAnimation()
{
	if(_fadeAnimation == NULL)
		_fadeAnimation = new bb::cascades::FadeTransition();
	return _fadeAnimation;
}
bb::cascades::ScaleTransition *TiUIAnimationProxy::getScaleAnimation()
{
	if(_scaleAnimation == NULL)
		_scaleAnimation = new bb::cascades::ScaleTransition();
	return _scaleAnimation;
}


TiUIAnimationEventHandler::TiUIAnimationEventHandler(TiUIAnimationProxy* animationProxy, Ti::TiViewProxy* viewProxy, Ti::TiCallback* callback)
{
	_callback = callback;
	_animationProxy = animationProxy;
	_viewProxy = viewProxy;
	_view = _viewProxy->getView();
	_hasFired = false;
}
/*
TiUIAnimationEventHandler::~TiUIAnimationEventHandler()
{
	delete _callback;
}
*/
void TiUIAnimationEventHandler::onAnimationEnd()
{
	_animationProxy->removeAnimations();
	bb::cascades::ImplicitAnimationController allDisabled = bb::cascades::ImplicitAnimationController::create(_view).enabled(false);
	Ti::TitaniumLayout *layout = _view->viewLayout;

	QMap<TiUIAnimationProxy::Type, QString> properties = _animationProxy->getProperties();
	if(properties.contains(TiUIAnimationProxy::Left)) {
		layout->_setLeft(properties[TiUIAnimationProxy::Left]);
		_view->setTranslationX(0);
	}
	if(properties.contains(TiUIAnimationProxy::Top)) {
		layout->_setTop(properties[TiUIAnimationProxy::Top]);
		_view->setTranslationY(0);
	}
	if(properties.contains(TiUIAnimationProxy::Right)) {
		layout->_setRight(properties[TiUIAnimationProxy::Right]);
		_view->setTranslationX(0);
	}
	if(properties.contains(TiUIAnimationProxy::Bottom)) {
		layout->_setBottom(properties[TiUIAnimationProxy::Bottom]);
		_view->setTranslationY(0);
	}
	if(properties.contains(TiUIAnimationProxy::Opacity)) {
		_view->setOpacity(properties[TiUIAnimationProxy::Opacity].toFloat(NULL));
	}
	if(properties.contains(TiUIAnimationProxy::Width)) {
		layout->_setWidth(properties[TiUIAnimationProxy::Width]);
		_view->setScaleX(1);
		_view->setPivotX(0);
	}
	if(properties.contains(TiUIAnimationProxy::Height)) {
		layout->_setHeight(properties[TiUIAnimationProxy::Height]);
		_view->setScaleY(1);
		_view->setPivotY(0);
	}
	if(!_hasFired && _callback != NULL)
	{
		_hasFired = true;
		_callback->fire(Ti::TiEventParameters());
	}
}


}
