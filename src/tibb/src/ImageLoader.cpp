/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "ImageLoader.h"

namespace titanium {

ImageLoader::ImageLoader(bb::cascades::ImageView* img, QUrl url)
{
	imageView = img;
	networkManager = new QNetworkAccessManager();
	imageUrl = url;
	if (networkManager)
	{
	    QNetworkRequest networkRequest(url);
	   	networkReply = networkManager->get(networkRequest);
	    connect(networkReply, SIGNAL(finished()), this, SLOT(onFinish()));
	}
}

ImageLoader::~ImageLoader()
{
	networkManager->deleteLater();
}

void ImageLoader::onFinish()
{
    if (networkReply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Some error occurred while fetching remote image";
        deleteLater();
        return;
    }
    QByteArray data(networkReply->readAll());
    ImageLoader::saveToDisk(imageUrl, data);
    bb::cascades::Image image = bb::cascades::Image(data);
    imageView->setImage(image);
    deleteLater();
}

void ImageLoader::loadImage(bb::cascades::ImageView* img, QUrl url)
{
	// check if the file exist
	if(ImageLoader::loadFromDisk(url, img))
		return;
	// otherwise get it from the server
	new ImageLoader(img, url);
}

// Generates a temporary directory path for the image, using the image url as file name
QString ImageLoader::generateTempUrl(QUrl url)
{
	QString base64 = QString("ti_").append(QString(url.toString().toUtf8().toBase64().constData()));

	QString path = QDir::tempPath();
			path.append("/");
			path.append(base64);

	return path;
}

// Saves the image to disk for later use
void ImageLoader::saveToDisk(QUrl url, QByteArray data)
{

	QFile imageFile(ImageLoader::generateTempUrl(url));
	if(!imageFile.open(QIODevice::WriteOnly)) return;

	imageFile.write(data);
	imageFile.close();
}

// Gets an image file from disk if it exists
bool ImageLoader::loadFromDisk(QUrl url, bb::cascades::ImageView* img)
{
	QFile imageFile(ImageLoader::generateTempUrl(url));
	if(imageFile.exists() && imageFile.open(QIODevice::ReadOnly))
	{
		bb::cascades::Image i = bb::cascades::Image(imageFile.readAll());
		img->setImage(i);
		imageFile.close();
		return true;
	}
	return false;
}

} /* namespace titanium */
