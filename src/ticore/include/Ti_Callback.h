
/*
 * Ti_Blob.h
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_CALLBACK_H_
#define TI_CALLBACK_H_


/**
 * This is for callback functions passed in parameters. For example:
 * win.addAction("Title", "image.png", callbackFunction);
 */

namespace Ti
{
class TiProxy;
class TiValue;
class TiCallback
{
public:
	TiCallback(Ti::TiProxy* proxy, Ti::TiValue val);
	virtual ~TiCallback();
	void fire(Ti::TiEventParameters params);

private:
	Ti::TiProxy* _proxy;
	uint32_t _id;
	bool hasFunction;
};


}

#endif
