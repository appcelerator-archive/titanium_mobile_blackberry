/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUtils.h"
#include "Layout/ParseProperty.h"
#include <bb/device/DisplayInfo>
#include <QObject>
#include <QString>

static TiUtils* sharedInstance = NULL;

TiUtils::TiUtils()
{

	const float MMPERINCH = 25.4f;

	bb::device::DisplayInfo display;
	QSize pixelSize = display.pixelSize();
	QSizeF physicalSize = display.physicalSize();

	const float physicalWidth = physicalSize.width();
	const float physicalHeight = physicalSize.height();
	const float pixelWidth = pixelSize.width();
	const float pixelHeight = pixelSize.height();

	// Calculate pixels density
	const float diagonalWidth = sqrtf(physicalWidth * physicalWidth + physicalHeight * physicalHeight) / MMPERINCH;
	const float diagonalPixels = sqrtf(pixelWidth * pixelWidth + pixelHeight * pixelHeight);

	ppi_ = diagonalPixels / diagonalWidth;
}

TiUtils::~TiUtils()
{

}

float TiUtils::getPPI()
{
	return ppi_;
}

float TiUtils::getCalculatedDimension(QString str)
{
	return getDimensionValue(str.toUtf8().constData(), ppi_);
}

TiUtils* TiUtils::getInstance()
{
	if(sharedInstance == NULL)
		sharedInstance = new TiUtils();
	return sharedInstance;
}
