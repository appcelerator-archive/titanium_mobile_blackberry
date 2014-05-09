/*
 * Ti_Blob.h
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIBLOB_H_
#define TI_TIBLOB_H_

#include "Ti_Data.h"
#include "Ti_Value.h"

#include <bb/ImageData>
#include <bb/cascades/Image>
#include <bb/cascades/ImageTracker>
#include <bb/cascades/ResourceState>
#include <QObject>
#include <QByteArray>
#include <QString>

namespace Ti {

typedef enum {
	TiBlobTypeImage = 0,
	TiBlobTypeFile = 1,
	TiBlobTypeData = 2,
	TiBlobTypeNone = 3
} TiBlobType;

class TiBlob : public Ti::TiData
{
public:
	CREATE_PROXY(TiBlob);
	TiBlob(const char*);
	virtual ~TiBlob();

	virtual Ti::TiValue getToString(Ti::TiValue);
	Ti::TiValue getWidth();
	Ti::TiValue getHeight();
	Ti::TiValue getText();
	Ti::TiValue getLength();
	Ti::TiValue getSize();
	Ti::TiValue _getMimeType();

	EXPOSE_GETTER(Ti::TiBlob, getWidth)
	EXPOSE_GETTER(Ti::TiBlob, getHeight)
	EXPOSE_GETTER(Ti::TiBlob, getText)
	EXPOSE_GETTER(Ti::TiBlob, getLength)
	EXPOSE_GETTER(Ti::TiBlob, getSize)
	EXPOSE_GETTER(Ti::TiBlob, _getMimeType)

	static Ti::TiBlob* InitWithImageData(bb::ImageData);
	static Ti::TiBlob* InitWithData(QByteArray, QString);
	static Ti::TiBlob* InitWithFile(QString);
	static Ti::TiBlob* InitWithString(QByteArray, QString);
	static Ti::TiBlob* InitWithString(QString);

	void setData(QByteArray);
	void setImageData(bb::ImageData);
	void setMimeType(QString, TiBlobType);

	virtual TiData::Type getType();
	virtual QByteArray getData();
	virtual QString getFilename();
	virtual QString getContentType();
	QString getMimeType();
	QString getPath();
	Ti::TiBlobType getBlobType();
	Ti::TiBlob* getNativePath();
	bb::ImageData getImageData();
	QSizeF _imageSize;

private:
	Ti::TiBlobType _blobType;
	QString _mimetype;
	QByteArray _data;
	QString _path;
	bb::ImageData _imageData;
	bool isImageMimeType();
	void ensureImageLoaded();
};
} /* namespace Ti */
#endif /* TIBLOB_H_ */
