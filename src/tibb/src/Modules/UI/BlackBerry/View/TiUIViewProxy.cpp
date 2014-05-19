/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIViewProxy.h"
#include "TiUIView.h"
#include <unistd.h>
namespace TiUI {

TiUIViewProxy::TiUIViewProxy(const char* name) : Ti::TiViewProxy(name)
{
	createPropertySetter("visible", _setVisible);
	setView(new TiUIView(this));
}

TiUIViewProxy::~TiUIViewProxy()
{

}

void TiUIViewProxy::setVisible(Ti::TiValue value)
{
	view->setVisible(value.toBool());
}

}
