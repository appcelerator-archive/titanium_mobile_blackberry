/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TITANIUMLAYOUT_H_
#define TITANIUMLAYOUT_H_

#include <QObject>
#include <bb/cascades/Control>
#include <bb/cascades/LayoutUpdateHandler>
#include "Ti_View.h"
#include "Layout/Headers.h"

namespace Ti
{
class TitaniumLayout : QObject
{
	Q_OBJECT;
public:
	TitaniumLayout(TiView*);
	virtual ~TitaniumLayout();

	static void onPostLayout(struct Ti::Layout::Node*);
	static void calculatePPI();
	void addChild(TiView*);
	void removeChild(TiView*);
	bool resize(float width, float height);
	TiView* getView();
	void updateLayoutProperty(Ti::Layout::ValueName name, QString val);
	void _setLayout(QString);
	void _setLeft(QString);
	void _setRight(QString);
	void _setTop(QString);
	void _setBottom(QString);
	void _setWidth(QString);
	void _setHeight(QString);
	void _setChildControl(bb::cascades::Control *);
	bb::cascades::Control * _getChildControl();
    struct Ti::Layout::Node _layoutNode;
private:


	QString _layout;
	QString _left;
	QString _right;
	QString _top;
	QString _bottom;
	QString _width;
	QString _height;

	float _nLayout;
	float _nLeft;
	float _nRight;
	float _nTop;
	float _nBottom;
	float _nWidth;
	float _nHeight;

    float lastWidth_;
    float lastHeight_;

    int displayWidth_;
    int displayHeight_;

	bool deferWidth_;
	bool deferHeight_;

	bool ignoreWidth_;
	bool ignoreHeight_;

	enum Ti::Layout::ValueType deferWidthType_;
	enum Ti::Layout::ValueType deferHeightType_;

	TiView* _tiView;
	bb::cascades::Control* _control;
	QRectF rect_;
public slots:
	void onLayout(QRectF);
};

} /* namespace Ti */
#endif /* TITANIUMLAYOUT_H_ */
