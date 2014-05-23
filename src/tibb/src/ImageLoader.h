/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef IMAGELOADER_H_
#define IMAGELOADER_H_

#include <bb/cascades/ImageView>
#include <QObject>

namespace titanium {

class ImageLoader : public QObject
{
Q_OBJECT;
public:
	static void loadImage(bb::cascades::ImageView *img, QUrl url);

public slots:
	void onFinish();

private:
	ImageLoader(bb::cascades::ImageView* img, QUrl url);
	virtual ~ImageLoader();

	QUrl imageUrl;
	QNetworkReply* networkReply;
	QNetworkAccessManager *networkManager;
	bb::cascades::ImageView *imageView;

	static void saveToDisk(QUrl url, QByteArray data);
	static bool loadFromDisk(QUrl url, bb::cascades::ImageView* img);
	static QString generateTempUrl(QUrl url);

};

} /* namespace titanium */
#endif /* IMAGELOADER_H_ */
