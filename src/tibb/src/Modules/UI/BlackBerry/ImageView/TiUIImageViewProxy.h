/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIIMAGEVIEWPROXY_H_
#define TIUIIMAGEVIEWPROXY_H_

#include <TiCore.h>
#include <bb/cascades/ImageView>

namespace TiUI {
class TiUIImageView;
class TiUIImageViewProxy : public Ti::TiViewProxy
{
public:
	CREATE_PROXY(TiUIImageViewProxy)
	TiUIImageViewProxy(const char*);
	virtual ~TiUIImageViewProxy();

	Ti::TiValue add(Ti::TiValue);
	Ti::TiValue pause(Ti::TiValue);
	Ti::TiValue remove(Ti::TiValue);
	Ti::TiValue resume(Ti::TiValue);
	Ti::TiValue start(Ti::TiValue);
	Ti::TiValue stop(Ti::TiValue);
	Ti::TiValue toBlob(Ti::TiValue);


	TI_CREATE_SETTER_GETTER(TiUIImageViewProxy, setAutorotate, getAutorotate)
	TI_CREATE_SETTER_GETTER(TiUIImageViewProxy, setDecodeRetries, getDecodeRetries)
	TI_CREATE_SETTER_GETTER(TiUIImageViewProxy, setDefaultImage, getDefaultImage)
	TI_CREATE_SETTER_GETTER(TiUIImageViewProxy, setDuration, getDuration)
	TI_CREATE_SETTER_GETTER(TiUIImageViewProxy, setEnableZoomControls, getEnableZoomControls)
	TI_CREATE_SETTER_GETTER(TiUIImageViewProxy, setHires, getHires)
	TI_CREATE_SETTER_GETTER(TiUIImageViewProxy, setImage, getImage)
	TI_CREATE_SETTER_GETTER(TiUIImageViewProxy, setImages, getImages)
	TI_CREATE_SETTER_GETTER(TiUIImageViewProxy, setPreventDefaultImage, getPreventDefaultImage)
	TI_CREATE_SETTER_GETTER(TiUIImageViewProxy, setRepeatCount, getRepeatCount)
	TI_CREATE_SETTER_GETTER(TiUIImageViewProxy, setReverse, getReverse)
	TI_CREATE_SETTER_GETTER(TiUIImageViewProxy, setUrl, getUrl)

	TI_CREATE_GETTER(TiUIImageViewProxy, getAnimating)
	TI_CREATE_GETTER(TiUIImageViewProxy, getPaused)

	EXPOSE_METHOD(TiUIImageViewProxy, add)
	EXPOSE_METHOD(TiUIImageViewProxy, pause)
	EXPOSE_METHOD(TiUIImageViewProxy, remove)
	EXPOSE_METHOD(TiUIImageViewProxy, resume)
	EXPOSE_METHOD(TiUIImageViewProxy, start)
	EXPOSE_METHOD(TiUIImageViewProxy, stop)
	EXPOSE_METHOD(TiUIImageViewProxy, toBlob)
private:
	TiUIImageView* _imageView;
	bb::cascades::ImageView* _native;
	bool _imageSet;
};

}
#endif /* TIUIIMAGEVIEWPROXY_H_ */
