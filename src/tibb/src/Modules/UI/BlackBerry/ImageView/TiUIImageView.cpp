/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIImageView.h"
#include "ImageLoader.h"
#include <bb/cascades/Image>
#include <bb/cascades/ScalingMethod>
#include <bb/cascades/ImageViewLoadEffect>

namespace TiUI {

TiUIImageView::TiUIImageView(Ti::TiViewProxy* proxy) : Ti::TiView(proxy),
		_isAnimating(false), _isReverse(false),
		_animationInterval(100),
		_repeatCount(0), _iterations(0), _animationIndex(0),
		_animationTimer(NULL)
{
	_imageView = new bb::cascades::ImageView();
	_imageView->setScalingMethod(bb::cascades::ScalingMethod::AspectFit);
	setChildControl(_imageView);
}

TiUIImageView::~TiUIImageView()
{
	if(_animationTimer != NULL)
	{
		_animationTimer->stop();
		_isAnimating = false;
	}
}

void TiUIImageView::onRelayout(QRectF r)
{
	Ti::TiView::onRelayout(r);
	getProxy()->fireEvent("load", Ti::TiEventParameters());
}

bool TiUIImageView::ingoreWidth()
{
	return false;
}
bool TiUIImageView::ingoreHeight()
{
	return false;
}
QString TiUIImageView::defaultWidth()
{
	return Ti::TiConstants::SizeSIZE;
}
QString TiUIImageView::defaultHeight()
{
	return Ti::TiConstants::SizeSIZE;
}

bb::cascades::ImageView* TiUIImageView::getNative()
{
	return _imageView;
}

void TiUIImageView::setByteData(QByteArray ar)
{
	_byteArray = ar;
}
QByteArray TiUIImageView::getByteData()
{
	return _byteArray;
}
bool TiUIImageView::setImage(QString str)
{
	_imageView->resetImage();

	if(str.startsWith("http://") || str.startsWith("https://"))
	{
		return ImageLoader::loadImage(this, _imageView, QUrl(str));
	}
	_imageView->setImageSource(QUrl(Ti::TiHelper::getAssetPath(str)));
	return true;
}
void TiUIImageView::setBlob(Ti::TiBlob* blob)
{
	setByteData(blob->getData());
	_imageView->resetImage();
	_imageView->setImage(bb::cascades::Image(blob->getImageData()));
}

void TiUIImageView::setImages(QList<QString> list)
{
	_images.clear();
	foreach(QString src, list)
	{
		_images.append(Ti::TiHelper::getAssetPath(src));
	}
	_imageView->setImage(bb::cascades::Image(QUrl(_images.at(0))));
}

bool TiUIImageView::isReverse()
{
	return  _isReverse;
}
void TiUIImageView::setReverse(bool reverse)
{
	_isReverse = reverse;
}

void TiUIImageView::resume()
{
	if(_animationTimer != NULL)
	{
		_animationTimer->start();
	}
}
void TiUIImageView::pause()
{
	if(_animationTimer != NULL)
	{
		_animationTimer->stop();
	}
}
void TiUIImageView::startAnimating()
{
	_imageView->setLoadEffect(bb::cascades::ImageViewLoadEffect::None);
	if(_animationTimer == NULL) {
		_animationTimer = new QTimer(this);
		QObject::connect(_animationTimer, SIGNAL(timeout()), this, SLOT(onTimer()));
	}
	else
	{
		_animationTimer->stop();
	}
	_animationTimer->setInterval(_animationInterval);
	_animationTimer->start();
	getProxy()->fireEvent("start", Ti::TiEventParameters());
	_isAnimating = true;
}
void TiUIImageView::stopAnimating()
{
	if(_animationTimer == NULL) {
		return;
	}

	_animationIndex = 0;
	_iterations = 0;

	_animationTimer->stop();
	_isAnimating = false;
	getProxy()->fireEvent("stop", Ti::TiEventParameters());
	_imageView->resetLoadEffect();
}

void TiUIImageView::setRepeatCount(int r)
{
	_repeatCount = r;
}
int TiUIImageView::getRepeatCount()
{
	return _repeatCount;
}

bool TiUIImageView::isAnimating()
{
	return _isAnimating;
}
void TiUIImageView::setDuration(int d)
{
	_animationInterval = d;
	if(_animationTimer != NULL)
	{
		_animationTimer->setInterval(d);
	}
}
int TiUIImageView::getDuration()
{
	return _animationInterval;
}

void TiUIImageView::onTimer()
{
	int arrayLength = _images.size();
	int eventIndex = _animationIndex;
	if(!_isReverse)
	{
		if(_animationIndex < arrayLength)
		{
			_imageView->setImage(bb::cascades::Image(QUrl(_images.at(_animationIndex))));
			eventIndex = _animationIndex;
			_animationIndex++;
		} else {
			_animationIndex = 0;
			_imageView->setImage(bb::cascades::Image(QUrl(_images.at(_animationIndex))));
			eventIndex = _animationIndex;
			_animationIndex++;
			if(_repeatCount != 0) {
				_iterations++;
				if(_repeatCount < _iterations)
				{
					stopAnimating();
				}
			}
		}
	}
	else
	{
		if(_animationIndex > -1)
		{
			_imageView->setImage(bb::cascades::Image(QUrl(_images.at(_animationIndex))));
			eventIndex = _animationIndex;
			_animationIndex--;
		} else {
			_animationIndex = arrayLength - 1;
			_imageView->setImage(bb::cascades::Image(QUrl(_images.at(_animationIndex))));
			eventIndex = _animationIndex;
			_animationIndex--;
			if(_repeatCount != 0) {
				_iterations++;
				if(_repeatCount < _iterations)
				{
					stopAnimating();
				}
			}
		}
	}
	Ti::TiEventParameters event;
	event.addParam("index", eventIndex);
	getProxy()->fireEvent(Ti::TiConstants::EventChange, event);
}

}
