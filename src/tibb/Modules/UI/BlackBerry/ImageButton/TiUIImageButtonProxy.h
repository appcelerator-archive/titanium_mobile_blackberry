/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUIIMAGEBUTTONPROXY_H_
#define TI_TIUIIMAGEBUTTONPROXY_H_

#include "TiCore.h"
#include "TiUIImageButton.h"

namespace TiUI {

class TiUIImageButtonProxy : public Ti::TiViewProxy
{
public:
	CREATE_PROXY(TiUIImageButtonProxy)
	TiUIImageButtonProxy(const char*);
	virtual ~TiUIImageButtonProxy();

	TI_CREATE_SETTER_GETTER(TiUIImageButtonProxy, setTitle, getTitle)
	TI_CREATE_SETTER_GETTER(TiUIImageButtonProxy, setImage, getImage)
	TI_CREATE_SETTER_GETTER(TiUIImageButtonProxy, setImageDisabled, getImageDisabled)
	TI_CREATE_SETTER_GETTER(TiUIImageButtonProxy, setImagePressed, getImagePressed)
private:
	QString _image;
	QString _imageDisabled;
	QString _imagePressed;
	TiUIImageButton* _imageButton;
};

} /* namespace TiUI */
#endif /* TIUIIMAGEBUTTONPROXY_H_ */
