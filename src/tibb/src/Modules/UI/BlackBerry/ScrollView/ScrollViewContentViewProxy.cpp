/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "ScrollViewContentViewProxy.h"
#include "ScrollViewContentView.h"

namespace TiUI {

ScrollViewContentViewProxy::ScrollViewContentViewProxy(const char* name) : Ti::TiViewProxy(name)
{
	setView(new ScrollViewContentView(this));
}

ScrollViewContentViewProxy::~ScrollViewContentViewProxy() {
	// TODO Auto-generated destructor stub
}

} /* namespace Ti */
