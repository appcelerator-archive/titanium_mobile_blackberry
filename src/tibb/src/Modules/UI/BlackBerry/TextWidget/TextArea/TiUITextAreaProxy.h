/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUITEXTAREAPROXY_H_
#define TI_TIUITEXTAREAPROXY_H_

#include <TiCore.h>
#include "../TiUITextWidgetProxy.h"
#include "../TiUITextWidget.h"

// #include <bb/cascades/AbstractTextControl>

namespace TiUI {
class TiUITextArea;
class TiUITextAreaProxy : public TiUITextWidgetProxy
{
public:
	CREATE_PROXY(TiUITextAreaProxy)
	TiUITextAreaProxy(const char*);
	virtual ~TiUITextAreaProxy();

	void setScrollsToTop(Ti::TiValue);
	void setScrollable(Ti::TiValue);

	Ti::TiValue getScrollsToTop();
	Ti::TiValue getScrollable();

	EXPOSE_SETTER(TiUITextAreaProxy, setScrollsToTop)
	EXPOSE_SETTER(TiUITextAreaProxy, setScrollable)

	EXPOSE_GETTER(TiUITextAreaProxy, getScrollsToTop)
	EXPOSE_GETTER(TiUITextAreaProxy, getScrollable)

private:
	bb::cascades::TextArea* _nativeTextArea;
};
}
#endif /* TIUITEXTAREAPROXY_H_ */
