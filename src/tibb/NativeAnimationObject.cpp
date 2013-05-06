/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeAnimationObject.h"

#include <iostream>
#include <string>
#include "TiObject.h"
#include "NativeControlObject.h"
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/device/DisplayInfo>
#include <bb/cascades/ImplicitAnimationController>
#include "TiUtils.h"

using namespace v8;
/*

enum N_ANIMATION_PROPS {
    N_ANIMATION_PROP_TOP,
    N_ANIMATION_PROP_LEFT,
};

 */
static NativeAnimationObject::PropertyInfo properties[] = {
		{N_ANIMATION_PROP_ANCHORPOINT, 0, &NativeAnimationObject::setAnchorPoint},
		{N_ANIMATION_PROP_AUTOREVERSE, 0, &NativeAnimationObject::setAutoreverse},
		{N_ANIMATION_PROP_BACKGROUNDCOLOR, 0, &NativeAnimationObject::setBackgroundColor},
		{N_ANIMATION_PROP_BOTTOM, 0, &NativeAnimationObject::setBottom},
		{N_ANIMATION_PROP_CENTER, 0, &NativeAnimationObject::setCenter},
		{N_ANIMATION_PROP_COLOR, 0, &NativeAnimationObject::setColor},
		{N_ANIMATION_PROP_CURVE, 0, &NativeAnimationObject::setCurve},
		{N_ANIMATION_PROP_DELAY, 0, &NativeAnimationObject::setDelay},
		{N_ANIMATION_PROP_DURATION, 0, &NativeAnimationObject::setDuration},
		{N_ANIMATION_PROP_HEIGHT, 0, &NativeAnimationObject::setHeight},
		{N_ANIMATION_PROP_LEFT, 0, &NativeAnimationObject::setLeft},
		{N_ANIMATION_PROP_OPACITY, 0, &NativeAnimationObject::setOpacity},
		{N_ANIMATION_PROP_OPAQUE, 0, &NativeAnimationObject::setOpaque},
		{N_ANIMATION_PROP_REPEAT, 0, &NativeAnimationObject::setRepeat},
		{N_ANIMATION_PROP_RIGHT, 0, &NativeAnimationObject::setRight},
		{N_ANIMATION_PROP_TOP, 0, &NativeAnimationObject::setTop},
		{N_ANIMATION_PROP_TRANSFORM, 0, &NativeAnimationObject::setTransform},
		{N_ANIMATION_PROP_TRANSITION, 0, &NativeAnimationObject::setTransition},
		{N_ANIMATION_PROP_VIEW, 0, &NativeAnimationObject::setView},
		{N_ANIMATION_PROP_VISIBLE, 0, &NativeAnimationObject::setVisible},
		{N_ANIMATION_PROP_WIDTH, 0, &NativeAnimationObject::setWidth},
		{N_ANIMATION_PROP_ZINDEX, 0, &NativeAnimationObject::setZIndex}
};

static const int propertyCount = sizeof(properties) / sizeof(properties[0]);

NativeAnimationObject* NativeAnimationObject::createAnimation(TiObject* object) {
	return new NativeAnimationObject(object);
}
NativeAnimationObject::~NativeAnimationObject()
{

}
NativeAnimationObject::NativeAnimationObject(TiObject* object)
  : NativeProxyObject(object)
  , PropertyDelegateBase<NativeAnimationObject>(this, properties, propertyCount) {

	_jsObject = object;
	_hasCallback = false;
	_fadeAnimation = NULL;
	_transitionAnimation = NULL;
	_nativeControlObject = NULL;
}
/*
int NativeAnimationObject::setPropertyValue(size_t propertyNumber, TiObject* obj) {
    return setProperty(propertyNumber, obj);
}

int NativeAnimationObject::getPropertyValue(size_t propertyNumber, TiObject* obj) {
    return getProperty(propertyNumber, obj);
}
 */
int NativeAnimationObject::setPropertyValue(size_t propertyNumber, TiObject* obj)
{
    return setProperty(propertyNumber, obj);
}

int NativeAnimationObject::getPropertyValue(size_t propertyNumber, TiObject* obj)
{
    return getProperty(propertyNumber, obj);
}

void NativeAnimationObject::addToMap(N_ANIMATION_PROPS prop, TiObject* obj)
{
	if(_animationProperties.contains(prop))
		delete _animationProperties[prop];

	TiObject *_obj = new TiObject();
	_obj->setValue(obj->getValue());
	_animationProperties.insert(prop, _obj);
}

int NativeAnimationObject::setAnchorPoint(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_ANCHORPOINT, obj);
	return NATIVE_ERROR_NOTSUPPORTED;
}
int NativeAnimationObject::setAutoreverse(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_ANCHORPOINT, obj);
	return NATIVE_ERROR_NOTSUPPORTED;
}
int NativeAnimationObject::setBackgroundColor(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_BACKGROUNDCOLOR, obj);
	return NATIVE_ERROR_NOTSUPPORTED;
}
int NativeAnimationObject::setBottom(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_BOTTOM, obj);
	return NATIVE_ERROR_OK;
}
int NativeAnimationObject::setCenter(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_CENTER, obj);
	return NATIVE_ERROR_NOTSUPPORTED;
}
int NativeAnimationObject::setColor(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_COLOR, obj);
	return NATIVE_ERROR_NOTSUPPORTED;
}
int NativeAnimationObject::setCurve(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_CURVE, obj);
	return NATIVE_ERROR_NOTSUPPORTED;
}
int NativeAnimationObject::setDelay(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_DELAY, obj);
	return NATIVE_ERROR_OK;
}
int NativeAnimationObject::setDuration(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_DURATION, obj);
	return NATIVE_ERROR_OK;
}
int NativeAnimationObject::setHeight(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_HEIGHT, obj);
	return NATIVE_ERROR_NOTSUPPORTED;
}
int NativeAnimationObject::setLeft(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_LEFT, obj);
	return NATIVE_ERROR_OK;
}
int NativeAnimationObject::setOpacity(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_OPACITY, obj);
	return NATIVE_ERROR_OK;
}
int NativeAnimationObject::setOpaque(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_OPACITY, obj);
	return NATIVE_ERROR_NOTSUPPORTED;
}
int NativeAnimationObject::setRepeat(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_REPEAT, obj);
	return NATIVE_ERROR_OK;
}
int NativeAnimationObject::setRight(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_RIGHT, obj);
	return NATIVE_ERROR_OK;
}
int NativeAnimationObject::setTop(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_TOP, obj);
	return NATIVE_ERROR_OK;
}
int NativeAnimationObject::setTransform(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_TRANSFORM, obj);
	return NATIVE_ERROR_NOTSUPPORTED;
}
int NativeAnimationObject::setTransition(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_TRANSITION, obj);
	return NATIVE_ERROR_NOTSUPPORTED;
}
int NativeAnimationObject::setView(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_VIEW, obj);
	return NATIVE_ERROR_NOTSUPPORTED;
}
int NativeAnimationObject::setVisible(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_VISIBLE, obj);
	return NATIVE_ERROR_NOTSUPPORTED;
}
int NativeAnimationObject::setWidth(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_WIDTH, obj);
	return NATIVE_ERROR_NOTSUPPORTED;
}
int NativeAnimationObject::setZIndex(TiObject* obj)
{
	addToMap(N_ANIMATION_PROP_ZINDEX, obj);
	return NATIVE_ERROR_NOTSUPPORTED;
}

void NativeAnimationObject::setNativeControlObject(NativeControlObject *obj)
{
	_nativeControlObject = obj;
}

NativeControlObject* NativeAnimationObject::getNativeControlObject()
{
	return _nativeControlObject;
}

bb::cascades::TranslateTransition *NativeAnimationObject::getTranslateAnimation()
{
	if(_transitionAnimation == NULL)
		_transitionAnimation = bb::cascades::TranslateTransition::create().autoDeleted(true);
	return _transitionAnimation;
}
bb::cascades::FadeTransition *NativeAnimationObject::getFadeAnimation()
{
	if(_fadeAnimation == NULL)
		_fadeAnimation = bb::cascades::FadeTransition::create().autoDeleted(true);
	return _fadeAnimation;
}
QMap<N_ANIMATION_PROPS, TiObject*> NativeAnimationObject::getAnimationProperies()
{
	return _animationProperties;
}

void NativeAnimationObject::setCallback(TiV8Event* callback)
{
	std::cout << "function " << std::endl;
	_callback = callback;
	_hasCallback = true;
}

void NativeAnimationObject::setHasCallback(bool hasCallback)
{
	_hasCallback = hasCallback;
}

bool NativeAnimationObject::hasCallback()
{
	return _hasCallback;
}
TiV8Event* NativeAnimationObject::getCallback()
{
	return _callback;
}

void NativeAnimationObject::removeAnimations()
{
	if(_nativeControlObject == NULL) return;
	bb::cascades::Control *view = (bb::cascades::Control*)_nativeControlObject->getNativeHandle();

	if(_transitionAnimation != NULL)
		view->removeAnimation(_transitionAnimation);
	if(_fadeAnimation != NULL)
		view->removeAnimation(_fadeAnimation);

}

TiObject *NativeAnimationObject::getJSObject()
{
	return _jsObject;
}

void NativeAnimationObject::animate(NativeControlObject *obj, Node layoutNode)
{
	setNativeControlObject(obj);
	bb::cascades::Control *view = (bb::cascades::Control*)obj->getNativeHandle();

	float x = layoutNode.element._measuredLeft;
	float y = layoutNode.element._measuredTop;

	float parentWidth = layoutNode.parent->element._measuredWidth;
	float objectWidth = layoutNode.element._measuredWidth;
	float parentHeight = layoutNode.parent->element._measuredHeight;
	float objectHeight = layoutNode.element._measuredHeight;

	std::string stringValue;
	float floatValue;

	TiUtils *tiUtils = TiUtils::getInstance();


	if(_animationProperties.contains(N_ANIMATION_PROP_LEFT)) {
		NativeControlObject::getStdString(_animationProperties[N_ANIMATION_PROP_LEFT], &stringValue);
		float left = tiUtils->getCalculatedDimension(stringValue);
		getTranslateAnimation()->setToX(-x + left);
	}
	if(_animationProperties.contains(N_ANIMATION_PROP_TOP)) {
		NativeControlObject::getStdString(_animationProperties[N_ANIMATION_PROP_TOP], &stringValue);
		float top = tiUtils->getCalculatedDimension(stringValue);
		getTranslateAnimation()->setToY(-y + top);
	}
	if(_animationProperties.contains(N_ANIMATION_PROP_RIGHT)) {
		NativeControlObject::getStdString(_animationProperties[N_ANIMATION_PROP_RIGHT], &stringValue);
		float right = tiUtils->getCalculatedDimension(stringValue);
		getTranslateAnimation()->setToX(-x + parentWidth - objectWidth - right);
	}
	if(_animationProperties.contains(N_ANIMATION_PROP_BOTTOM)) {
		NativeControlObject::getStdString(_animationProperties[N_ANIMATION_PROP_BOTTOM], &stringValue);
		float bottom = tiUtils->getCalculatedDimension(stringValue);
		getTranslateAnimation()->setToY(-y + parentHeight - objectHeight - bottom);
	}
	if(_animationProperties.contains(N_ANIMATION_PROP_OPACITY)) {
		NativeControlObject::getFloat(_animationProperties[N_ANIMATION_PROP_OPACITY], &floatValue);
		getFadeAnimation()->setToOpacity(floatValue);
	}
	if(_animationProperties.contains(N_ANIMATION_PROP_DURATION)) {
		NativeControlObject::getFloat(_animationProperties[N_ANIMATION_PROP_DURATION], &floatValue);
		if(_transitionAnimation != NULL)
			_transitionAnimation->setDuration((int)floatValue);
		if(_fadeAnimation != NULL)
			_fadeAnimation->setDuration((int)floatValue);
	}
	if(_animationProperties.contains(N_ANIMATION_PROP_DELAY)) {
		NativeControlObject::getFloat(_animationProperties[N_ANIMATION_PROP_DELAY], &floatValue);
		if(_transitionAnimation != NULL)
			_transitionAnimation->setDelay((int)floatValue);
		if(_fadeAnimation != NULL)
			_fadeAnimation->setDelay((int)floatValue);
	}
	if(_animationProperties.contains(N_ANIMATION_PROP_REPEAT)) {
		NativeControlObject::getFloat(_animationProperties[N_ANIMATION_PROP_REPEAT], &floatValue);
		if(_transitionAnimation != NULL)
			_transitionAnimation->setRepeatCount((int)floatValue);
		if(_fadeAnimation != NULL)
			_fadeAnimation->setRepeatCount((int)floatValue);
	}

	NativeAnimationEventHandler *events = new NativeAnimationEventHandler(this);
	if(_transitionAnimation != NULL) {
		view->addAnimation(_transitionAnimation);
	    QObject::connect(_transitionAnimation, SIGNAL(ended()), events, SLOT(onAnimationEnd()));
	    _transitionAnimation->play();
	}
	if(_fadeAnimation != NULL) {
		view->addAnimation(_fadeAnimation);
		QObject::connect(_fadeAnimation, SIGNAL(ended()), events, SLOT(onAnimationEnd()));
	    _fadeAnimation->play();
	}

}

NativeAnimationEventHandler::NativeAnimationEventHandler(NativeAnimationObject *obj)
{
	_animationObject = obj;
	_nativeObject = obj->getNativeControlObject();
	_view = (bb::cascades::Control*)_nativeObject->getNativeHandle();
	_animationProperties = _animationObject->getAnimationProperies();
}

void NativeAnimationEventHandler::onAnimationEnd()
{
	bb::cascades::ImplicitAnimationController allDisabled = bb::cascades::ImplicitAnimationController::create(_view).enabled(false);

	_animationObject->removeAnimations();

	if(_animationProperties.contains(N_ANIMATION_PROP_LEFT)) {
		_nativeObject->setLeft(_animationProperties[N_ANIMATION_PROP_LEFT]);
		_view->setTranslationX(0);
	}
	if(_animationProperties.contains(N_ANIMATION_PROP_TOP)) {
		_nativeObject->setTop(_animationProperties[N_ANIMATION_PROP_TOP]);
		_view->setTranslationY(0);
	}
	if(_animationProperties.contains(N_ANIMATION_PROP_RIGHT)) {
		_nativeObject->setRight(_animationProperties[N_ANIMATION_PROP_RIGHT]);
		_view->setTranslationX(0);
	}
	if(_animationProperties.contains(N_ANIMATION_PROP_BOTTOM)) {
		_nativeObject->setBottom(_animationProperties[N_ANIMATION_PROP_BOTTOM]);
		_view->setTranslationY(0);
	}
	if(_animationProperties.contains(N_ANIMATION_PROP_OPACITY)) {
		_nativeObject->setOpacity(_animationProperties[N_ANIMATION_PROP_OPACITY]);
	}
	if(_animationObject->hasCallback()) {
		// Fire only once
		_animationObject->setHasCallback(false);
	    TiV8Event* callback = _animationObject->getCallback();
		callback->fire();
	}
}