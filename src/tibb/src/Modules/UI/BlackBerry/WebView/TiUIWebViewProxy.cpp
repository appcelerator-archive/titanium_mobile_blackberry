/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIWebViewProxy.h"

namespace TiUI {

static QList<TiUIWebViewProxy*> webViews_;
QList<TiUIWebViewProxy*> TiUIWebViewProxy::getWebViewProxies()
{
	return webViews_;
}

TiUIWebViewProxy::TiUIWebViewProxy(const char* name) : Ti::TiViewProxy(name)
{
	createPropertySetterGetter("data", _setData,  _getData);
	createPropertySetterGetter("disableBounce", _setDisableBounce,  _getDisableBounce);
	createPropertySetterGetter("hideLoadIndicator", _setHideLoadIndicator,  _getHideLoadIndicator);
	createPropertySetterGetter("html", _setHtml,  _getHtml);
	createPropertySetterGetter("ignoreSslError", _setIgnoreSslError,  _getIgnoreSslError);
	createPropertySetterGetter("loading", _setLoading,  _getLoading);
	createPropertySetterGetter("overScrollMode", _setOverScrollMode,  _getOverScrollMode);
	createPropertySetterGetter("pluginState", _setPluginState,  _getPluginState);
	createPropertySetterGetter("scrollsToTop", _setScrollsToTop,  _getScrollsToTop);
	createPropertySetterGetter("showScrollbars", _setShowScrollbars,  _getShowScrollbars);
	createPropertySetterGetter("enableZoomControls", _setEnableZoomControls,  _getEnableZoomControls);
	createPropertySetterGetter("scalesPageToFit", _setScalesPageToFit,  _getScalesPageToFit);
	createPropertySetterGetter("url", _setUrl,  _getUrl);
	createPropertySetterGetter("userAgent", _setUserAgent,  _getUserAgent);
	createPropertySetterGetter("willHandleTouches", _setWillHandleTouches,  _getWillHandleTouches);

	createPropertyFunction("canGoBack", _canGoBack);
	createPropertyFunction("canGoForward", _canGoForward);
	createPropertyFunction("evalJS", _evalJS);
	createPropertyFunction("goBack", _goBack);
	createPropertyFunction("goForward", _goForward);
	createPropertyFunction("pause", _pause);
	createPropertyFunction("reload", _reload);
	createPropertyFunction("repaint", _repaint);
	createPropertyFunction("release", _release);
	createPropertyFunction("resume", _resume);
	createPropertyFunction("setBasicAuthentication", _setBasicAuthentication);
	createPropertyFunction("stopLoading", _stopLoading);

	_tiWebView = new UIWebView(this);
	setView(_tiWebView);
	webViews_.append(this);
}

UIWebView *TiUIWebViewProxy::getTiWebView()
{
	return _tiWebView;
}
TiUIWebViewProxy::~TiUIWebViewProxy()
{
	webViews_.removeOne(this);
}
void TiUIWebViewProxy::setData(Ti::TiValue)
{
}
void TiUIWebViewProxy::setDisableBounce(Ti::TiValue val)
{
	_tiWebView->setDisableBounce(val.toBool());
}
void TiUIWebViewProxy::setHideLoadIndicator(Ti::TiValue val)
{
	if(val.toBool() == true) {
		_tiWebView->hideLoadingIndicator();
	}
}
void TiUIWebViewProxy::setHtml(Ti::TiValue val)
{
	_tiWebView->setIsLocal(true);
	_tiWebView->getNativeWebView()->setHtml(val.toString());
}
void TiUIWebViewProxy::setIgnoreSslError(Ti::TiValue)
{
}
void TiUIWebViewProxy::setLoading(Ti::TiValue)
{
}
void TiUIWebViewProxy::setOverScrollMode(Ti::TiValue)
{
}
void TiUIWebViewProxy::setPluginState(Ti::TiValue)
{
}
void TiUIWebViewProxy::setScrollsToTop(Ti::TiValue)
{
}
void TiUIWebViewProxy::setShowScrollbars(Ti::TiValue)
{
}
void TiUIWebViewProxy::setEnableZoomControls(Ti::TiValue)
{
}
void TiUIWebViewProxy::setScalesPageToFit(Ti::TiValue val)
{
	_tiWebView->setScalesPageToFit(val.toBool());
}
void TiUIWebViewProxy::setUrl(Ti::TiValue val)
{
    QString url = val.toString();
    if(url.startsWith("http://") || url.startsWith("https://"))
    {
        _tiWebView->setIsLocal(false);
    	_tiWebView->getNativeWebView()->setUrl(QUrl(url));
    	return;
   	}
    const char* a = url.toLocal8Bit().constData();
    QString localUrl = QString("local:///").append(Ti::TiHelper::getAssetPath(url));
    const char* aa = localUrl.toLocal8Bit().constData();
//    localUrl.replace("local:///assets//", "local:///assets/");
//    const char* aaa = localUrl.toLocal8Bit().constData();
    _tiWebView->setIsLocal(true);
	_tiWebView->getNativeWebView()->setUrl(QUrl(localUrl));
	_tiWebView->hideLoadingIndicator();
}
void TiUIWebViewProxy::setUserAgent(Ti::TiValue val)
{
	_tiWebView->setUserAgent(val.toString());
}
void TiUIWebViewProxy::setWillHandleTouches(Ti::TiValue)
{
}

Ti::TiValue TiUIWebViewProxy::getData()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::getDisableBounce()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::getHideLoadIndicator()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::getHtml()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::getIgnoreSslError()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::getLoading()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::getOverScrollMode()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::getPluginState()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::getScrollsToTop()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::getShowScrollbars()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::getEnableZoomControls()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::getScalesPageToFit()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::getUrl()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::getUserAgent()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::getWillHandleTouches()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

Ti::TiValue TiUIWebViewProxy::canGoBack(Ti::TiValue)
{
	Ti::TiValue val;
	val.setBool(_tiWebView->getNativeWebView()->canGoBack());
	return val;
}
Ti::TiValue TiUIWebViewProxy::canGoForward(Ti::TiValue)
{
	Ti::TiValue val;
	val.setBool(_tiWebView->getNativeWebView()->canGoForward());
	return val;
}
Ti::TiValue TiUIWebViewProxy::evalJS(Ti::TiValue val)
{
	if(val.isList())
	{
		QList<Ti::TiValue> array = val.toList();
		Ti::TiValue str = array.at(0);
		Ti::TiValue callback = array.at(1);
		_tiWebView->evalJS(str.toString(), callback);
	}
	else
	{
		_tiWebView->evalJS(val.toString());
	}
	return Ti::TiValue();
}
Ti::TiValue TiUIWebViewProxy::goBack(Ti::TiValue)
{
	_tiWebView->getNativeWebView()->goBack();
	return Ti::TiValue();
}
Ti::TiValue TiUIWebViewProxy::goForward(Ti::TiValue)
{
	_tiWebView->getNativeWebView()->goForward();
	return Ti::TiValue();
}
Ti::TiValue TiUIWebViewProxy::pause(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::reload(Ti::TiValue)
{
	_tiWebView->getNativeWebView()->reload();
	return Ti::TiValue();
}
Ti::TiValue TiUIWebViewProxy::repaint(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::release(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::resume(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::setBasicAuthentication(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUIWebViewProxy::stopLoading(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

}
