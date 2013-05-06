/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEANIMATIONOBJECT_H_
#define NATIVEANIMATIONOBJECT_H_


#include "NativeProxyObject.h"
#include "PropertyDelegate.h"
#include <bb/cascades/Control>
#include <bb/cascades/TranslateTransition>
#include <bb/cascades/FadeTransition>
#include "Layout/Node.h"
#include "TiV8Event.h"
#include <QMap>
#include <v8.h>

class NativeControlObject;

enum N_ANIMATION_PROPS {
	N_ANIMATION_PROP_ANCHORPOINT,
	N_ANIMATION_PROP_AUTOREVERSE,
	N_ANIMATION_PROP_BACKGROUNDCOLOR,
	N_ANIMATION_PROP_BOTTOM,
	N_ANIMATION_PROP_CENTER,
	N_ANIMATION_PROP_COLOR,
	N_ANIMATION_PROP_CURVE,
	N_ANIMATION_PROP_DELAY,
	N_ANIMATION_PROP_DURATION ,
	N_ANIMATION_PROP_HEIGHT,
	N_ANIMATION_PROP_LEFT,
	N_ANIMATION_PROP_OPACITY,
	N_ANIMATION_PROP_OPAQUE,
	N_ANIMATION_PROP_REPEAT,
	N_ANIMATION_PROP_RIGHT,
	N_ANIMATION_PROP_TOP,
	N_ANIMATION_PROP_TRANSFORM,
	N_ANIMATION_PROP_TRANSITION,
	N_ANIMATION_PROP_VIEW,
	N_ANIMATION_PROP_VISIBLE,
	N_ANIMATION_PROP_WIDTH,
	N_ANIMATION_PROP_ZINDEX
};

class NativeAnimationObject : public NativeProxyObject,
	public titanium::PropertyDelegateBase<NativeAnimationObject> {

public:
    static NativeAnimationObject* createAnimation(TiObject* object);
    NATIVE_TYPE getObjectType() const {
        return N_TYPE_ANIMATION;
    }

    int setPropertyValue(size_t propertyNumber, TiObject* obj);
    int getPropertyValue(size_t propertyNumber, TiObject* obj);

    int setAnchorPoint(TiObject* obj);
	int setAutoreverse(TiObject* obj);
	int setBackgroundColor(TiObject* obj);
	int setBottom(TiObject* obj);
	int setCenter(TiObject* obj);
	int setColor(TiObject* obj);
	int setCurve(TiObject* obj);
	int setDelay(TiObject* obj);
	int setDuration(TiObject* obj);
	int setHeight(TiObject* obj);
	int setLeft(TiObject* obj);
	int setOpacity(TiObject* obj);
	int setOpaque(TiObject* obj);
	int setRepeat(TiObject* obj);
	int setRight(TiObject* obj);
	int setTop(TiObject* obj);
	int setTransform(TiObject* obj);
	int setTransition(TiObject* obj);
	int setView(TiObject* obj);
	int setVisible(TiObject* obj);
	int setWidth(TiObject* obj);
	int setZIndex(TiObject* obj);
	void setHasCallback(bool hasCallback);
    TiObject *getJSObject();
	bool hasCallback();
	TiV8Event* getCallback();
	void setCallback(TiV8Event* event);
	void setNativeControlObject(NativeControlObject *obj);
	void removeAnimations();
	NativeControlObject* getNativeControlObject();
	bb::cascades::TranslateTransition *getTranslateAnimation();
	bb::cascades::FadeTransition *getFadeAnimation();
	QMap<N_ANIMATION_PROPS, TiObject*> getAnimationProperies();

	void animate(NativeControlObject *obj, Node layoutNode);

	float ppi_;
protected:
    virtual ~NativeAnimationObject();

private:
    void addToMap(N_ANIMATION_PROPS, TiObject*);

    NativeControlObject *_nativeControlObject;
    bb::cascades::TranslateTransition *_transitionAnimation;
    bb::cascades::FadeTransition *_fadeAnimation;
	QMap<N_ANIMATION_PROPS, TiObject*> _animationProperties;
	TiV8Event* _callback;
	bool _hasCallback;
    explicit NativeAnimationObject(TiObject* tiObject);
    NativeAnimationObject(const NativeAnimationObject&);
    NativeAnimationObject& operator=(const NativeAnimationObject&);
    TiObject *_jsObject;
};

class NativeAnimationEventHandler : public QObject
{
	Q_OBJECT
public:
	NativeAnimationEventHandler(NativeAnimationObject *obj);
private:
	NativeAnimationObject *_animationObject;
	NativeControlObject *_nativeObject;
	bb::cascades::Control *_view;
	QMap<N_ANIMATION_PROPS, TiObject*> _animationProperties;

public slots:
	void onAnimationEnd();
};

#endif
