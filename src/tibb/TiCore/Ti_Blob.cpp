/*
 * Ti_Blob.h
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "Ti_Blob.h"
#include <bb/utility/ImageConverter>

static QString const MIMETYPE_PNG = "image/png";
static QString const MIMETYPE_JPEG = "image/jpeg";

Ti::TiBlob::TiBlob(const char* name) :
		Ti::TiProxy(name),
		_imageSize(0,0),
		_blobType(Ti::TiBlobTypeNone),
		_mimetype(""),
		_data(""),
		_imageData(),
		_path("")
{
	createPropertyGetter("width", _getWidth);
	createPropertyGetter("height", _getHeight);
	createPropertyGetter("text", _getText);
	createPropertyGetter("length", _getLength);
	createPropertyGetter("size", _getSize);
	createPropertyGetter("mimeType", __getMimeType);
}

Ti::TiBlob::~TiBlob()
{
}


Ti::TiBlob* Ti::TiBlob::InitWithImageData(bb::ImageData image)
{
	Ti::TiBlob* blob = Ti::TiBlob::CreateProxy();
	blob->setImageData(image);
	blob->_blobType = Ti::TiBlobTypeImage;
	return blob;
}
Ti::TiBlob* Ti::TiBlob::InitWithData(QByteArray data, QString mimeType)
{

	qDebug() << "Data length: " << data.size();
	Ti::TiBlob* blob = Ti::TiBlob::CreateProxy();
	blob->setData(data);
	blob->_mimetype = mimeType;
	blob->_blobType = Ti::TiBlobTypeData;
	return blob;

}
Ti::TiBlob* Ti::TiBlob::InitWithFile(QString path)
{
	Ti::TiBlob* blob = Ti::TiBlob::CreateProxy();
	blob->_path = QString(path);
	blob->_blobType = Ti::TiBlobTypeFile;
	return blob;
}

bool Ti::TiBlob::isImageMimeType()
{
	return _mimetype.startsWith("image/");
}

void Ti::TiBlob::ensureImageLoaded()
{
	if (!_imageData.isValid())
	{
		_imageData = getImageData();
	}
}


void Ti::TiBlob::setData(QByteArray data)
{
	_data = QByteArray(data);
}
void Ti::TiBlob::setImageData(bb::ImageData image)
{
	setMimeType(
			image.format() == bb::PixelFormat::RGBA_Premultiplied ? MIMETYPE_PNG : MIMETYPE_JPEG,
			Ti::TiBlobTypeImage
	);
	_imageData = bb::ImageData(image);
}
void Ti::TiBlob::setMimeType(QString mime, TiBlobType type)
{
	_mimetype = mime;
	_blobType = type;
}

QString Ti::TiBlob::getPath()
{
	return _path;
}
QByteArray Ti::TiBlob::getData()
{
	switch(_blobType)
	{
		case TiBlobTypeFile:
		{
			QFile file(_path);
			if(file.open(QIODevice::ReadOnly)) {
				QByteArray d = file.readAll();
				file.close();
				return d;
			}
			break;
		}
		case TiBlobTypeImage:
		{
            return QByteArray((char *)_imageData.pixels());
		}
		default: {
			break;
		}
	}
	return _data;
}

bb::ImageData Ti::TiBlob::getImageData()
{
	switch(_blobType)
	{
		case Ti::TiBlobTypeFile:
		{
			_imageData = bb::ImageData(bb::utility::ImageConverter::decode(QUrl(_path)));
			break;
		}
		case Ti::TiBlobTypeData:
		{
			_imageData = bb::ImageData(bb::utility::ImageConverter::decode(_data));
			break;
		}
		default: {
			break;
		}
	}
	if(_imageData.isValid())
	{
		setMimeType(
				_imageData.format() == bb::PixelFormat::RGBA_Premultiplied ? MIMETYPE_PNG : MIMETYPE_JPEG,
				Ti::TiBlobTypeImage
		);
	}
	return _imageData;

}
QString Ti::TiBlob::getMimeType()
{
	return _mimetype;
}

Ti::TiBlobType Ti::TiBlob::getType()
{
	return _blobType;
}
Ti::TiBlob* Ti::TiBlob::getNativePath()
{
	return NULL;
}

Ti::TiValue Ti::TiBlob::getWidth()
{
	Ti::TiValue returnedValue;
	ensureImageLoaded();
	returnedValue.setNumber(_imageData.width());
	return returnedValue;
}

Ti::TiValue Ti::TiBlob::getHeight()
{
	Ti::TiValue returnedValue;
	ensureImageLoaded();
	returnedValue.setNumber(_imageData.height());
	return returnedValue;
}
Ti::TiValue Ti::TiBlob::getText()
{
	Ti::TiValue returnedValue;

	returnedValue.setString(QString(getData()));
	return returnedValue;
}

Ti::TiValue Ti::TiBlob::getLength()
{
	Ti::TiValue returnedValue;
	returnedValue.setNumber(getData().size());
	return returnedValue;
}

Ti::TiValue Ti::TiBlob::getSize()
{
	Ti::TiValue returnedValue;

	ensureImageLoaded();
	if (_imageData.isValid())
	{
		returnedValue.setNumber(_imageData.width() * _imageData.height());
		return returnedValue;
	}
	switch (_blobType)
	{
		case TiBlobTypeData:
		case TiBlobTypeFile:
		{
			returnedValue.setNumber(getData().length());
			break;
		}
		default: {
			returnedValue.setNumber(0);
			break;
		}
	}

	return returnedValue;
}

Ti::TiValue Ti::TiBlob::_getMimeType()
{
	Ti::TiValue val;
	val.setString(getMimeType());
	return val;
}
