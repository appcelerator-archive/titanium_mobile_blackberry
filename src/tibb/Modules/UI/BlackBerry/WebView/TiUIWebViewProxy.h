/*
 * TiUIWebViewProxy.h
 *
 *  Created on: Sunday, September 15, 2013
 *      Author: penrique
 */

#ifndef TI_TIUIWEBVIEWPROXY_H_
#define TI_TIUIWEBVIEWPROXY_H_

#include "TiCore.h"
#include "UIWebView.h"

namespace TiUI {

class TiUIWebViewProxy : public Ti::TiViewProxy
{
public:
	CREATE_PROXY(TiUIWebViewProxy)
	TiUIWebViewProxy(const char*);
    static QList<TiUIWebViewProxy*> getWebViewProxies();
	virtual ~TiUIWebViewProxy();
	UIWebView *getTiWebView();

	void setData(Ti::TiValue);
	void setDisableBounce(Ti::TiValue);
	void setHideLoadIndicator(Ti::TiValue);
	void setHtml(Ti::TiValue);
	void setIgnoreSslError(Ti::TiValue);
	void setLoading(Ti::TiValue);
	void setOverScrollMode(Ti::TiValue);
	void setPluginState(Ti::TiValue);
	void setScrollsToTop(Ti::TiValue);
	void setShowScrollbars(Ti::TiValue);
	void setEnableZoomControls(Ti::TiValue);
	void setScalesPageToFit(Ti::TiValue);
	void setUrl(Ti::TiValue);
	void setUserAgent(Ti::TiValue);
	void setWillHandleTouches(Ti::TiValue);

	Ti::TiValue getData();
	Ti::TiValue getDisableBounce();
	Ti::TiValue getHideLoadIndicator();
	Ti::TiValue getHtml();
	Ti::TiValue getIgnoreSslError();
	Ti::TiValue getLoading();
	Ti::TiValue getOverScrollMode();
	Ti::TiValue getPluginState();
	Ti::TiValue getScrollsToTop();
	Ti::TiValue getShowScrollbars();
	Ti::TiValue getEnableZoomControls();
	Ti::TiValue getScalesPageToFit();
	Ti::TiValue getUrl();
	Ti::TiValue getUserAgent();
	Ti::TiValue getWillHandleTouches();

	Ti::TiValue canGoBack(Ti::TiValue);
	Ti::TiValue canGoForward(Ti::TiValue);
	Ti::TiValue evalJS(Ti::TiValue);
	Ti::TiValue goBack(Ti::TiValue);
	Ti::TiValue goForward(Ti::TiValue);
	Ti::TiValue pause(Ti::TiValue);
	Ti::TiValue reload(Ti::TiValue);
	Ti::TiValue repaint(Ti::TiValue);
	Ti::TiValue release(Ti::TiValue);
	Ti::TiValue resume(Ti::TiValue);
	Ti::TiValue setBasicAuthentication(Ti::TiValue);
	Ti::TiValue stopLoading(Ti::TiValue);


	EXPOSE_SETTER(TiUIWebViewProxy, setData)
	EXPOSE_SETTER(TiUIWebViewProxy, setDisableBounce)
	EXPOSE_SETTER(TiUIWebViewProxy, setHideLoadIndicator)
	EXPOSE_SETTER(TiUIWebViewProxy, setHtml)
	EXPOSE_SETTER(TiUIWebViewProxy, setIgnoreSslError)
	EXPOSE_SETTER(TiUIWebViewProxy, setLoading)
	EXPOSE_SETTER(TiUIWebViewProxy, setOverScrollMode)
	EXPOSE_SETTER(TiUIWebViewProxy, setPluginState)
	EXPOSE_SETTER(TiUIWebViewProxy, setScrollsToTop)
	EXPOSE_SETTER(TiUIWebViewProxy, setShowScrollbars)
	EXPOSE_SETTER(TiUIWebViewProxy, setEnableZoomControls)
	EXPOSE_SETTER(TiUIWebViewProxy, setScalesPageToFit)
	EXPOSE_SETTER(TiUIWebViewProxy, setUrl)
	EXPOSE_SETTER(TiUIWebViewProxy, setUserAgent)
	EXPOSE_SETTER(TiUIWebViewProxy, setWillHandleTouches)

	EXPOSE_GETTER(TiUIWebViewProxy, getData)
	EXPOSE_GETTER(TiUIWebViewProxy, getDisableBounce)
	EXPOSE_GETTER(TiUIWebViewProxy, getHideLoadIndicator)
	EXPOSE_GETTER(TiUIWebViewProxy, getHtml)
	EXPOSE_GETTER(TiUIWebViewProxy, getIgnoreSslError)
	EXPOSE_GETTER(TiUIWebViewProxy, getLoading)
	EXPOSE_GETTER(TiUIWebViewProxy, getOverScrollMode)
	EXPOSE_GETTER(TiUIWebViewProxy, getPluginState)
	EXPOSE_GETTER(TiUIWebViewProxy, getScrollsToTop)
	EXPOSE_GETTER(TiUIWebViewProxy, getShowScrollbars)
	EXPOSE_GETTER(TiUIWebViewProxy, getEnableZoomControls)
	EXPOSE_GETTER(TiUIWebViewProxy, getScalesPageToFit)
	EXPOSE_GETTER(TiUIWebViewProxy, getUrl)
	EXPOSE_GETTER(TiUIWebViewProxy, getUserAgent)
	EXPOSE_GETTER(TiUIWebViewProxy, getWillHandleTouches)

	EXPOSE_METHOD(TiUIWebViewProxy, canGoBack)
	EXPOSE_METHOD(TiUIWebViewProxy, canGoForward)
	EXPOSE_METHOD(TiUIWebViewProxy, evalJS)
	EXPOSE_METHOD(TiUIWebViewProxy, goBack)
	EXPOSE_METHOD(TiUIWebViewProxy, goForward)
	EXPOSE_METHOD(TiUIWebViewProxy, pause)
	EXPOSE_METHOD(TiUIWebViewProxy, reload)
	EXPOSE_METHOD(TiUIWebViewProxy, repaint)
	EXPOSE_METHOD(TiUIWebViewProxy, release)
	EXPOSE_METHOD(TiUIWebViewProxy, resume)
	EXPOSE_METHOD(TiUIWebViewProxy, setBasicAuthentication)
	EXPOSE_METHOD(TiUIWebViewProxy, stopLoading)
private:
	UIWebView* _tiWebView;
};}
#endif /* TIUIWEBVIEWPROXY_H_ */
