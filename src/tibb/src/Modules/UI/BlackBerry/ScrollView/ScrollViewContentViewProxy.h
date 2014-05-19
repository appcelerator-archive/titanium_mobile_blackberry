/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_SCROLLVIEWCONTENTVIEWPROXY_H_
#define TI_SCROLLVIEWCONTENTVIEWPROXY_H_

#include <TiCore.h>
#include <ostream>

namespace TiUI
{

class ScrollViewContentViewProxy : public Ti::TiViewProxy
{
public:
	CREATE_PROXY(ScrollViewContentViewProxy);
	ScrollViewContentViewProxy(const char*);
	virtual ~ScrollViewContentViewProxy();
};

} /* namespace Ti */
#endif /* SCROLLVIEWCONTENTVIEWPROXY_H_ */
