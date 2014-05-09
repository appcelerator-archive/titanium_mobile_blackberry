/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIIMAGEVIEW_H_
#define TIUIIMAGEVIEW_H_

#include "TiCore.h"
#include <bb/cascades/ImageView>
#include <bb/cascades/Image>

namespace TiUI {

class TiUIImageView : public Ti::TiView
{
	Q_OBJECT;
public:
	TiUIImageView(Ti::TiViewProxy*);
	virtual ~TiUIImageView();

	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();
	virtual void onRelayout(QRectF);

	void setByteData(QByteArray);
	QByteArray getByteData();
	bool setImage(QString);
	void setBlob(Ti::TiBlob*);

	bb::cascades::ImageView* getNative();
	void setImages(QList<QString>);
	void startAnimating();
	void stopAnimating();
	void setDuration(int);
	int getDuration();
	void setRepeatCount(int);
	int getRepeatCount();
	bool isAnimating();
	bool isReverse();
	void setReverse(bool);
	void pause();
	void resume();
private:
	QList<QString> _images;
	bool _isAnimating;
	bool _isReverse;
	int _animationInterval;
	int _repeatCount;
	int _iterations;
	int _animationIndex;
	QTimer *_animationTimer;
	QByteArray _byteArray;
	bb::cascades::ImageView* _imageView;
public slots:
	void onTimer();
};
}
#endif /* TIUIIMAGEVIEW_H_ */
