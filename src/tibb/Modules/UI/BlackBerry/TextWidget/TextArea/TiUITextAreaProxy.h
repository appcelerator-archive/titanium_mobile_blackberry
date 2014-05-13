/*
 * TiUITextAreaProxy.h
 *
 *  Created on: Sunday, September 15, 2013
 *      Author: penrique
 */

#ifndef TI_TIUITEXTAREAPROXY_H_
#define TI_TIUITEXTAREAPROXY_H_

#include "TiCore.h"
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
