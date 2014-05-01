/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIVIEWPROXY_H_
#define TIUIVIEWPROXY_H_

#include <TiCore.h>

namespace TiUI {

class TiUIViewProxy : public Ti::TiViewProxy
{
public:
	CREATE_PROXY(TiUIViewProxy);
	TiUIViewProxy(const char*);
	virtual ~TiUIViewProxy();
	void setVisible(Ti::TiValue);
	EXPOSE_SETTER(TiUIViewProxy, setVisible)
};
}
#endif /* TIUIVIEWPROXY_H_ */
