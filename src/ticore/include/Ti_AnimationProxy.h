/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIANIMATIONPROXY_H_
#define TI_TIANIMATIONPROXY_H_

namespace Ti {
class TiAnimationProxy : public Ti::TiProxy
{
public:
	TiAnimationProxy(const char*name) : Ti::TiProxy(name)
	{

	}
	virtual void animate(Ti::TiViewProxy*, Ti::TiCallback*) = 0;
};
}

#endif
