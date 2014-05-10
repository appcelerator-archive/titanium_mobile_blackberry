/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_IMAGELOADER_H_
#define TI_IMAGELOADER_H_

#include <bb/cascades/ImageView>
#include <QObject>

namespace TiUI {
class TiUIImageView;
class ImageLoader : public QObject
{
Q_OBJECT;
public:
	static bool loadImage(TiUIImageView* ,bb::cascades::ImageView *img, QUrl url);

public slots:
	void onFinish();

private:
	ImageLoader(TiUIImageView*, bb::cascades::ImageView* img, QUrl url);
	virtual ~ImageLoader();

	QUrl imageUrl;
	QNetworkReply* networkReply;
	QNetworkAccessManager *networkManager;
	bb::cascades::ImageView *imageView;

	static void saveToDisk(QUrl url, QByteArray data);
	static bool loadFromDisk(TiUIImageView*, QUrl url, bb::cascades::ImageView* img);
	static QString generateTempUrl(QUrl url);
	TiUIImageView* _tiView;
};

} /* namespace titanium */
#endif /* IMAGELOADER_H_ */
