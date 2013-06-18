/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeWebViewObject.h"

#include <bb/cascades/ActivityIndicator>
#include <bb/cascades/DockLayout>
#include <bb/cascades/Container>
#include <bb/cascades/JavaScriptWorld>
#include <bb/cascades/ScrollView>
#include <bb/cascades/ScrollViewProperties>
#include <bb/cascades/ScrollAnimation>
#include <bb/cascades/ScrollMode>
#include <bb/cascades/WebView>
#include <bb/cascades/WebLoadRequest>
#include <bb/cascades/WebLoadStatus>
#include <bb/cascades/WebNavigationRequest>
#include <bb/cascades/WebSettings>
#include <iostream>
#include "TiEvent.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "V8Utils.h"

using namespace titanium;

NativeWebViewObject::NativeWebViewObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_WEBVIEW)
{
	webview_ = NULL;
	isLocal_ = false;
}

NativeWebViewObject::~NativeWebViewObject()
{
}

NativeWebViewObject* NativeWebViewObject::createWebView(TiObject* tiObject)
{
    return new NativeWebViewObject(tiObject);
}

NATIVE_TYPE NativeWebViewObject::getObjectType() const
{
    return N_TYPE_WEBVIEW;
}

int NativeWebViewObject::initialize()
{

    bb::cascades::Container *mainView = new bb::cascades::Container();
    mainView->setLayout(new bb::cascades::DockLayout());

    webview_ = bb::cascades::WebView::create();
    scroller_ = bb::cascades::ScrollView::create(webview_);

    bb::cascades::ScrollViewProperties *props = scroller_->scrollViewProperties();
    props->setPinchToZoomEnabled(true);
    props->setScrollMode(bb::cascades::ScrollMode::Both);
    loading_ = bb::cascades::ActivityIndicator::create();


    mainView->add(scroller_);
    mainView->add(loading_);
    setControl(mainView);
    loading_->start();
//    scroller_->resetViewableArea(bb::cascades::ScrollAnimation::Smooth);
    return NATIVE_ERROR_OK;
}

// blob
int NativeWebViewObject::setData(TiObject* obj)
{

    return NATIVE_ERROR_NOTSUPPORTED;
}
// bool
int NativeWebViewObject::setDisableBounce(TiObject* obj)
{
	// could not find in docs
	return NATIVE_ERROR_NOTSUPPORTED;
}
// bool
int NativeWebViewObject::setEnableZoomControls(TiObject* obj)
{
	// android only
	return NATIVE_ERROR_NOTSUPPORTED;
}
//bool
int NativeWebViewObject::setHideLoadIndicator(TiObject* obj)
{
	bool value = true;
    int error = NativeControlObject::getBoolean(obj, &value);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }

    if(value == false) {
    	loading_->stop();
    }

    return NATIVE_ERROR_OK;
    
}
// string
int NativeWebViewObject::setHtml(TiObject* obj)
{
    QString html = V8ValueToQString(obj->getValue());
    webview_->setHtml(html, QUrl(""));
    // Needed?
    webview_->reload();

    return NATIVE_ERROR_OK;
    
}
// bool
int NativeWebViewObject::setLoading(TiObject* obj)
{
	// Not sure what this is for. Docs are not clear
	return NATIVE_ERROR_NOTSUPPORTED;
}
// number
int NativeWebViewObject::setPluginState(TiObject* obj)
{
	// Android
	return NATIVE_ERROR_NOTSUPPORTED;
}
// bool
int NativeWebViewObject::setScalesPageToFit(TiObject* obj)
{
	bool value = false;
    int error = NativeControlObject::getBoolean(obj, &value);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
	webview_->settings()->setZoomToFitEnabled(value);
	return NATIVE_ERROR_OK;
}
// bool
int NativeWebViewObject::setScrollsToTop(TiObject* obj)
{
	// iOS only
	return NATIVE_ERROR_NOTSUPPORTED;
}
// bool
int NativeWebViewObject::setShowScrollbars(TiObject* obj)
{
	// Not available in BB10, well, only for ListView
	// weird
	return NATIVE_ERROR_NOTSUPPORTED;
}
// string
int NativeWebViewObject::setUrl(TiObject* obj)
{
    QString url = V8ValueToQString(obj->getValue());
    if(url.startsWith("http://") || url.startsWith("https://"))
    {
    	webview_->setUrl(QUrl(url));
        return NATIVE_ERROR_OK;
   	}


    QString localUrl = QString("local:///assets/").append(url);
    localUrl.replace("local:///assets//", "local:///assets/");

	webview_->setUrl(QUrl(localUrl));
	isLocal_ = true;

	std::cout << localUrl.toUtf8().constData() << std::endl;

    return NATIVE_ERROR_OK;
    
}

void NativeWebViewObject::goBack() {
	webview_->goBack();
}

bool NativeWebViewObject::canGoBack() {
	return webview_->canGoBack();
}

void NativeWebViewObject::goForward() {
	webview_->goForward();
}

bool NativeWebViewObject::canGoForward() {
	return webview_->canGoForward();
}

void NativeWebViewObject::reload() {
	webview_->reload();
}
// string
int NativeWebViewObject::setUserAgent(TiObject* obj)
{
    QString userAgent = V8ValueToQString(obj->getValue());
    webview_->settings()->setUserAgent(userAgent);
    return NATIVE_ERROR_OK;
}
// bool
int NativeWebViewObject::setWillHandleTouches(TiObject* obj)
{
	// iOS only
	return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeWebViewObject::evalJS(QString javascript)
{
    webview_->evaluateJavaScript(javascript, bb::cascades::JavaScriptWorld::Normal);
    return NATIVE_ERROR_OK;
}

bb::cascades::WebView* NativeWebViewObject::getWebView()
{
	return webview_;
}

bb::cascades::ScrollView* NativeWebViewObject::getScroller()
{
	return scroller_;
}

bb::cascades::ActivityIndicator *NativeWebViewObject::getLoadingIndicator()
{
	return loading_;
}

void NativeWebViewObject::setupEvents(TiEventContainerFactory* containerFactory)
{

    NativeControlObject::setupEvents(containerFactory);

    // debug event
    TiEventContainer* eventDebug = containerFactory->createEventContainer();
    eventDebug->setDataProperty("type", tetDATA);
    events_.insert(tetDATA, EventPairSmartPtr(eventDebug, new WebViewEventHandler(eventDebug, this)));

    TiEventContainer* eventLoad = containerFactory->createEventContainer();
    eventLoad->setDataProperty("type", tetLOAD);
    events_.insert(tetLOAD, EventPairSmartPtr(eventLoad, new WebViewEventHandler(eventLoad, this)));
/*
    TiEventContainer* eventError = containerFactory->createEventContainer();
    eventError->setDataProperty("type", tetERROR);
    events_.insert(tetERROR, EventPairSmartPtr(eventError, new WebViewEventHandler(eventError, this)));
*/
    TiEventContainer* eventBeforeLoad = containerFactory->createEventContainer();
    eventBeforeLoad->setDataProperty("type", tetBEFORELOAD);
    events_.insert(tetBEFORELOAD, EventPairSmartPtr(eventBeforeLoad, new WebViewEventHandler(eventBeforeLoad, this)));

    bool res;


    // load
    res = QObject::connect(webview_, SIGNAL(loadingChanged(bb::cascades::WebLoadRequest *)), events_[tetLOAD]->handler(), SLOT(onLoadingChanged(bb::cascades::WebLoadRequest *)));
    // beforeload
    res = QObject::connect(webview_, SIGNAL(navigationRequested (bb::cascades::WebNavigationRequest *)), events_[tetBEFORELOAD]->handler(), SLOT(onNavigationRequested (bb::cascades::WebNavigationRequest *)));
    // debug
    res = QObject::connect(webview_, SIGNAL(javaScriptInterrupted()), events_[tetDATA]->handler(), SLOT(inJavaScriptInterrupted()));
    res = QObject::connect(webview_, SIGNAL(loadProgressChanged(int)), events_[tetDATA]->handler(), SLOT(onLoadProgressChanged(int)));
    res = QObject::connect(webview_, SIGNAL(titleChanged (const QString &)), events_[tetDATA]->handler(), SLOT(onTitleChanged (const QString &)));
    res = QObject::connect(webview_, SIGNAL(navigationHistoryChanged()), events_[tetDATA]->handler(), SLOT(onNavigationHistoryChanged()));
    res = QObject::connect(webview_, SIGNAL(urlChanged(const QUrl &)), events_[tetDATA]->handler(), SLOT(onUrlChanged(const QUrl &)));
    res = QObject::connect(webview_, SIGNAL(iconChanged(const QUrl &)), events_[tetDATA]->handler(), SLOT(onIconChanged(const QUrl &)));
    res = QObject::connect(webview_, SIGNAL(javaScriptResult (int, const QVariant &)), events_[tetDATA]->handler(), SLOT(onJavaScriptResult (int, const QVariant &)));
    res = QObject::connect(webview_, SIGNAL(messageReceived (const QVariantMap &)), events_[tetDATA]->handler(), SLOT(onMessageReceived (const QVariantMap &)));
    res = QObject::connect(webview_, SIGNAL(microFocusChanged()), events_[tetDATA]->handler(), SLOT(onMicroFocusChanged()));
	res = QObject::connect(webview_, SIGNAL(maxContentScaleChanged(float)), events_[tetDATA]->handler(), SLOT(onMaxContentScaleChanged(float)));
	res = QObject::connect(webview_, SIGNAL(minContentScaleChanged(float)), events_[tetDATA]->handler(), SLOT(onMinContentScaleChanged(float)));
	Q_ASSERT(res);
    // Indicate that the variable res isn't used in the rest of the app, to prevent
    // a compiler warning
    Q_UNUSED(res);
}




WebViewEventHandler::WebViewEventHandler(TiEventContainer* eventContainer, NativeWebViewObject* webviewObject)
{
    eventContainer_ = eventContainer;
    webviewObject_ = webviewObject;
    webview_ = webviewObject->getWebView();
    scroller_= webviewObject->getScroller();
    loading_= webviewObject->getLoadingIndicator();

}
WebViewEventHandler::~WebViewEventHandler() {

}

void WebViewEventHandler::onLoadingChanged(bb::cascades::WebLoadRequest* webRequest)
{

    if(webRequest->status() == bb::cascades::WebLoadStatus::Started)
    {
    	return;
    }
    if(webRequest->status() == bb::cascades::WebLoadStatus::Succeeded)
    {
    	eventContainer_->fireEvent();
    	loading_->stop();
    	if(webviewObject_->isLocal_)
    	{
  //  		webviewObject_->evalJS("(function(){Ti={};Ti.API={};Ti.API.info=function(e){navigator.cascades.postMessage('Ti.API.info('+JSON.stringify(e)+')')};Ti.App={};Ti.App.addEventListener=function(e,t){navigator.cascades.postMessage('Ti.App.addEventListener('+JSON.stringify(e)+', '+t+')')};Ti.App.fireEvent=function(e,t){t=t||{};navigator.cascades.postMessage('Ti.App.fireEvent('+JSON.stringify(e)+', '+JSON.stringify(t)+')')}})();");
    	}
    	return;
    }
    if(webRequest->status() == bb::cascades::WebLoadStatus::Failed)
    {
    	return;
    }

}

void WebViewEventHandler::onLoadProgress(int a)
{
	eventContainer_->fireEvent();
}

void WebViewEventHandler::onTitleChanged (const QString &title)
{
	eventContainer_->fireEvent();
}

void WebViewEventHandler::onNavigationHistoryChanged ()
{
	eventContainer_->fireEvent();
}

void WebViewEventHandler::onUrlChanged (const QUrl &url)
{
	eventContainer_->fireEvent();
}

void WebViewEventHandler::onIconChanged (const QUrl &icon)
{
	eventContainer_->fireEvent();
}

void WebViewEventHandler::onNavigationRequested (bb::cascades::WebNavigationRequest *request)
{
	eventContainer_->fireEvent();
}

void WebViewEventHandler::onJavaScriptResult (int resultId, const QVariant &result)
{
	eventContainer_->fireEvent();
}

void WebViewEventHandler::onJavaScriptInterrupted ()
{
	eventContainer_->fireEvent();
}

void WebViewEventHandler::onMessageReceived (const QVariantMap &message)
{
	QVariant m = message.value("data");
	QString funct = m.toString();
	webview_->postMessage("meh");
	v8::HandleScope scope;
    Handle<Script> script = Script::Compile(String::New(funct.toLocal8Bit().data()));
    script->Run();
}

void WebViewEventHandler::onMicroFocusChanged ()
{
	eventContainer_->fireEvent();
}

void WebViewEventHandler::onMinContentScaleChanged (float minContentScale)
{
	eventContainer_->fireEvent();
	scroller_->scrollViewProperties()->setMinContentScale(minContentScale);
}
void WebViewEventHandler::onMaxContentScaleChanged (float maxContentScale)
{
	eventContainer_->fireEvent();
	scroller_->scrollViewProperties()->setMaxContentScale(maxContentScale);
}
