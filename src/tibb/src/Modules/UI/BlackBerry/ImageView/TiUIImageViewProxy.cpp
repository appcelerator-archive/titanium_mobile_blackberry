/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIImageViewProxy.h"
#include "TiUIImageView.h"
#include "../../../Filesystem/TiFilesystemFileProxy.h"

#include <bb/cascades/ImageView>
#include <bb/utility/ImageConverter>

namespace TiUI {

TiUIImageViewProxy::TiUIImageViewProxy(const char* name) : Ti::TiViewProxy(name), _imageSet(false)
{
	qDebug() << "[INTERNAL] TiUIImageViewProxy Not Fully Implemented yet";

	createPropertyGetter("animating", _getAnimating);
	createPropertyGetter("paused", _getPaused);

	createPropertySetterGetter("autorotate", _setAutorotate,  _getAutorotate);
	createPropertySetterGetter("decodeRetries", _setDecodeRetries,  _getDecodeRetries);
	createPropertySetterGetter("defaultImage", _setDefaultImage,  _getDefaultImage);
	createPropertySetterGetter("duration", _setDuration,  _getDuration);
	createPropertySetterGetter("enableZoomControls", _setEnableZoomControls,  _getEnableZoomControls);
	createPropertySetterGetter("hires", _setHires,  _getHires);
	createPropertySetterGetter("image", _setImage,  _getImage);
	createPropertySetterGetter("images", _setImages,  _getImages);
	createPropertySetterGetter("preventDefaultImage", _setPreventDefaultImage,  _getPreventDefaultImage);
	createPropertySetterGetter("repeatCount", _setRepeatCount,  _getRepeatCount);
	createPropertySetterGetter("reverse", _setReverse,  _getReverse);
	createPropertySetterGetter("url", _setUrl,  _getUrl);

	createPropertyFunction("add", _add);
	createPropertyFunction("pause", _pause);
	createPropertyFunction("remove", _remove);
	createPropertyFunction("resume", _resume);
	createPropertyFunction("start", _start);
	createPropertyFunction("stop", _stop);
	createPropertyFunction("toBlob", _toBlob);
	_imageView = new TiUIImageView(this);
	_native = _imageView->getNative();
	setView(_imageView);
}

TiUIImageViewProxy::~TiUIImageViewProxy()
{
}

TI_GETTER_DEFER(TiUIImageViewProxy, getAutorotate)
void TiUIImageViewProxy::setAutorotate(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIImageViewProxy, getDecodeRetries)
void TiUIImageViewProxy::setDecodeRetries(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIImageViewProxy, getDefaultImage)
void TiUIImageViewProxy::setDefaultImage(Ti::TiValue value)
{
	if(_imageSet) return;
	QString str = value.toString();
	_native->setImage(QUrl(Ti::TiHelper::getAssetPath(value.toString())));
}

Ti::TiValue TiUIImageViewProxy::getDuration()
{
	Ti::TiValue val;
	val.setNumber(_imageView->getDuration());
	return val;
}
void TiUIImageViewProxy::setDuration(Ti::TiValue val)
{
	_imageView->setDuration((int)val.toNumber());
}

TI_GETTER_DEFER(TiUIImageViewProxy, getEnableZoomControls)
void TiUIImageViewProxy::setEnableZoomControls(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIImageViewProxy, getHires)
void TiUIImageViewProxy::setHires(Ti::TiValue)
{
}

TI_GETTER_DEFER(TiUIImageViewProxy, getImage)
void TiUIImageViewProxy::setImage(Ti::TiValue val)
{
	if(val.isProxy())
	{
		Ti::TiData *p = static_cast<Ti::TiData*>(val.toProxy());
		Ti::TiBlob *blob = NULL;
		if(p->getType() == Ti::TiData::Blob)
		{
			blob = static_cast<Ti::TiBlob*>(p);
		} else if(p->getType() == Ti::TiData::File)
		{
			TiFilesystem::TiFilesystemFileProxy *file = static_cast<TiFilesystem::TiFilesystemFileProxy*>(p);
			blob = Ti::TiBlob::InitWithFile(file->getFilePath());
		}
		if(blob != NULL)
		{
			_imageSet = true;
			_imageView->setBlob(blob);
		}
	}
	else
	{
		_imageSet = _imageView->setImage(val.toString());
	}
}

TI_GETTER_DEFER(TiUIImageViewProxy, getImages)
void TiUIImageViewProxy::setImages(Ti::TiValue val)
{
	if(!val.isList()) return;
	QList<Ti::TiValue> array = val.toList();
	QList<QString> images;
	foreach(Ti::TiValue image, array)
	{
		images.append(image.toString());
	}
	_imageView->setImages(images);
}

TI_GETTER_DEFER(TiUIImageViewProxy, getPreventDefaultImage)
void TiUIImageViewProxy::setPreventDefaultImage(Ti::TiValue)
{
}

Ti::TiValue TiUIImageViewProxy::getRepeatCount()
{
	Ti::TiValue val;
	val.setNumber(_imageView->getRepeatCount());
	return val;
}
void TiUIImageViewProxy::setRepeatCount(Ti::TiValue val)
{
	_imageView->setRepeatCount((int)val.toNumber());
}

Ti::TiValue TiUIImageViewProxy::getReverse()
{
	Ti::TiValue val;
	val.setBool(_imageView->isReverse());
	return val;
}
void TiUIImageViewProxy::setReverse(Ti::TiValue val)
{
	_imageView->setReverse(val.toBool());
}

TI_GETTER_DEFER(TiUIImageViewProxy, getUrl)
void TiUIImageViewProxy::setUrl(Ti::TiValue val)
{
	setImage(val);
}

Ti::TiValue TiUIImageViewProxy::getAnimating()
{
	Ti::TiValue val;
	val.setBool(_imageView->isAnimating());
	return val;
}

Ti::TiValue TiUIImageViewProxy::getPaused()
{
	Ti::TiValue val;
	val.setBool(_imageView->isAnimating());
	return val;
}


Ti::TiValue TiUIImageViewProxy::add(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIImageViewProxy::pause(Ti::TiValue)
{
	_imageView->pause();
	return Ti::TiValue();
}
Ti::TiValue TiUIImageViewProxy::remove(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIImageViewProxy::resume(Ti::TiValue)
{
	_imageView->resume();
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIImageViewProxy::start(Ti::TiValue)
{
	_imageView->startAnimating();
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIImageViewProxy::stop(Ti::TiValue)
{
	_imageView->stopAnimating();
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIImageViewProxy::toBlob(Ti::TiValue)
{
Ti::TiValue val;
	if(_imageView->getNative()->imageSource().isValid())
	{
		QFileInfo info(_imageView->getNative()->imageSource().toString());
		val.setProxy(Ti::TiBlob::InitWithFile(info.path()));
	}
	else if(!_imageView->getByteData().isEmpty())
	{
		val.setProxy(Ti::TiBlob::InitWithImageData(bb::ImageData(bb::utility::ImageConverter::decode(_imageView->getByteData()))));
	}

	return val;
}

}
