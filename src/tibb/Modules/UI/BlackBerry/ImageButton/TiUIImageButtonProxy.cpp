/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIImageButtonProxy.h"

namespace TiUI {

TiUIImageButtonProxy::TiUIImageButtonProxy(const char* name) : Ti::TiViewProxy(name)
{
	createPropertySetterGetter("title", _setTitle, _getTitle);
	createPropertySetterGetter("image", _setImage, _getImage);
	createPropertySetterGetter("imageDisabled", _setImageDisabled, _getImageDisabled);
	createPropertySetterGetter("imagePressed", _setImagePressed, _getImagePressed);

	_imageButton = new TiUIImageButton(this);
	setView(_imageButton);
}

TiUIImageButtonProxy::~TiUIImageButtonProxy()
{
}

void TiUIImageButtonProxy::setTitle(Ti::TiValue val)
{
}
void TiUIImageButtonProxy::setImage(Ti::TiValue val)
{
	_image = val.toString();
	_imageButton->getNative()->setDefaultImage(bb::cascades::Image(QUrl(Ti::TiHelper::getAssetPath(_image))));
}
void TiUIImageButtonProxy::setImageDisabled(Ti::TiValue val)
{
	_imageDisabled = val.toString();
	_imageButton->getNative()->setDisabledImage(bb::cascades::Image(QUrl(Ti::TiHelper::getAssetPath(_imageDisabled))));
}
void TiUIImageButtonProxy::setImagePressed(Ti::TiValue val)
{
	_imagePressed = val.toString();
	_imageButton->getNative()->setPressedImage(bb::cascades::Image(QUrl(Ti::TiHelper::getAssetPath(_imagePressed))));
}

Ti::TiValue TiUIImageButtonProxy::getTitle()
{
	return Ti::TiValue();
}
Ti::TiValue TiUIImageButtonProxy::getImage()
{
	Ti::TiValue val;
	val.setString(_image);
	return val;
}
Ti::TiValue TiUIImageButtonProxy::getImageDisabled()
{
	Ti::TiValue val;
	val.setString(_imageDisabled);
	return val;
}
Ti::TiValue TiUIImageButtonProxy::getImagePressed()
{
	Ti::TiValue val;
	val.setString(_imagePressed);
	return val;
}
} /* namespace TiUI */
