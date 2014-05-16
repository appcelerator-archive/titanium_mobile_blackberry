/*
 * TiUIAnimationProxy.h
 *
 *  Created on: May 16, 2014
 *      Author: penrique
 */

#ifndef TI_TIUIANIMATIONPROXY_H_
#define TI_TIUIANIMATIONPROXY_H_

#include <bb/cascades/TranslateTransition>
#include <bb/cascades/FadeTransition>
#include <bb/cascades/ScaleTransition>
#include <bb/cascades/Control>


#include "TiCore.h"

namespace TiUI {

class TiUIAnimationProxy : public Ti::TiAnimationProxy
{
public:
	CREATE_PROXY(TiUIAnimationProxy)
	TiUIAnimationProxy(const char*);
	virtual ~TiUIAnimationProxy();

	enum Type {
		AnchorPoint, AutoReverse, BackgroundColor,
		Bottom, Center, Color, Curve, Delay, Duration,
		Height, Left, Opacity, Opaque, Repeat, Right,
		Top, Transform, Transition, View, Visible,
		Width, zIndex
	};

	virtual void animate(Ti::TiViewProxy*, Ti::TiCallback*);

	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setAnchorPoint, getAnchorPoint)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setAutoreverse, getAutoreverse)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setBackgroundColor, getBackgroundColor)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setBottom, getBottom)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setCenter, getCenter)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setColor, getColor)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setCurve, getCurve)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setDelay, getDelay)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setDuration, getDuration)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setHeight, getHeight)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setLeft, getLeft)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setOpacity, getOpacity)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setOpaque, getOpaque)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setRepeat, getRepeat)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setRight, getRight)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setTop, getTop)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setTransform, getTransform)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setTransition, getTransition)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setView, getView)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setVisible, getVisible)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setWidth, getWidth)
	TI_CREATE_SETTER_GETTER(TiUIAnimationProxy, setZIndex, getZIndex)

	bb::cascades::TranslateTransition *getTranslateAnimation();
	bb::cascades::FadeTransition *getFadeAnimation();
	bb::cascades::ScaleTransition *getScaleAnimation();
	void removeAnimations();
	QMap<Type, QString> getProperties();
protected:
	QMap<Type, QString> _properties;
private:
	bb::cascades::TranslateTransition* _transitionAnimation;
	bb::cascades::FadeTransition* _fadeAnimation;
	bb::cascades::ScaleTransition* _scaleAnimation;
	bb::cascades::Control* _control;
};

class TiUIAnimationEventHandler : public QObject
{
	Q_OBJECT
public:
	TiUIAnimationEventHandler(TiUIAnimationProxy*, Ti::TiViewProxy*, Ti::TiCallback*);
private:
	TiUIAnimationProxy *_animationProxy;
	Ti::TiViewProxy *_viewProxy;
	Ti::TiCallback* _callback;
	Ti::TiView* _view;

public slots:
	void onAnimationEnd();
};

} /* namespace TiUI */
#endif /* TIUIANIMATIONPROXY_H_ */
