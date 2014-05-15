/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIVIEW_H_
#define TIVIEW_H_

#include <bb/cascades/Container>
#include <bb/cascades/Control>
#include <v8.h>

using namespace v8;

namespace bb
{
namespace cascades
{
class TapEvent;
class DoubleTapEvent;
class PinchEvent;
class LongPressEvent;
}
}
namespace Ti
{
class TitaniumLayout;
class TiViewProxy;
class TiView: public bb::cascades::Container {
	Q_OBJECT;
public:
	TiView(TiViewProxy*);
	virtual ~TiView();
	virtual void _setTop(QString);
	virtual void _setBottom(QString);
	virtual void _setLeft(QString);
	virtual void _setRight(QString);
	virtual void _setWidth(QString);
	virtual void _setHeight(QString);
	virtual void _setLayout(QString);
	virtual void setChildControl(bb::cascades::Control *);
	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();
	virtual void add(bb::cascades::Control*);
	virtual void remove(bb::cascades::Control*);
	virtual void onEventAdded(QString);
	virtual void onRelayout(QRectF);
	void addOldObject(void*);
	void setParentView(TiView*);
	void setTiLayout();
	QList<TiView*> childViews;
	QString _left;
	QString _right;
	QString _top;
	QString _bottom;
	QString _width;
	QString _height;
	TiView *parentView;
	TitaniumLayout *viewLayout;
	bb::cascades::Control* childControl;
	void setZIndex(int index);
	int getZIndex();
protected:
	virtual TiViewProxy *getProxy() const;
private:
	Ti::TiView *clickSource;
	TiViewProxy *proxy;
	int _zIndex;
	bool hasTouchEvents;
public slots:
	virtual void onTapEvent(bb::cascades::TapEvent*);
	virtual void onDoubleTapEvent(bb::cascades::DoubleTapEvent*);
	virtual void onLongPressEvent(bb::cascades::LongPressEvent*);

	virtual void onPinchStartedEvent(bb::cascades::PinchEvent*);
	virtual void onPinchUpdatedEvent(bb::cascades::PinchEvent*);
	virtual void onPinchEndedEvent(bb::cascades::PinchEvent*);
	virtual void onPinchCancelledEvent(bb::cascades::PinchEvent*);
	virtual void onTouch(bb::cascades::TouchEvent*);
	virtual void onTouchCapture(bb::cascades::TouchEvent*);


};
}
#endif /* TIVIEW_H_ */
