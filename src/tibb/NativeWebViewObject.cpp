/*
 * NativeWebViewObject.cpp
 *
 *  Created on: Jan 25, 2013
 *      Author: penrique
 */

#include "NativeWebViewObject.h"
#include "TiEvent.h"
#include "TiEventContainerFactory.h"
#include <bb/cascades/ActivityIndicator>
#include <bb/cascades/DockLayout>
#include <bb/cascades/Container>
#include <bb/cascades/JavaScriptWorld>
#include <bb/cascades/ScrollView>
#include <bb/cascades/ScrollViewProperties>
#include <bb/cascades/ScrollAnimation>
#include <bb/cascades/WebView>
#include <bb/cascades/WebLoadRequest>
#include <bb/cascades/WebLoadStatus>
#include <bb/cascades/WebNavigationRequest>
#include <bb/cascades/WebSettings>

NativeWebViewObject::NativeWebViewObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_WEBVIEW)
{
	webview_ = NULL;
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

    loading_ = bb::cascades::ActivityIndicator::create();
//    scroller_->setVerticalAlignment(bb::cascades::VerticalAlignment::Fill);
//    scroller_->setHorizontalAlignment(bb::cascades::HorizontalAlignment::Fill);

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
    QString str;
    int error = NativeControlObject::getString(obj, str);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    webview_->setHtml(str, QUrl(""));
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
    QString str;
    int error = NativeControlObject::getString(obj, str);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    webview_->setUrl(QUrl(str));
  //  webview_->reload();

    return NATIVE_ERROR_OK;
    
}
// string
int NativeWebViewObject::setUserAgent(TiObject* obj)
{
    QString str;
    int error = NativeControlObject::getString(obj, str);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    webview_->settings()->setUserAgent(str);
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

    TiLogger::getInstance().log("Loading Events");
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
    TiLogger::getInstance().log("onLoadingChanged");

    if(webRequest->status() == bb::cascades::WebLoadStatus::Started)
    {
        TiLogger::getInstance().log("WebLoadStatus::Type::Started");
    	return;
    }
    if(webRequest->status() == bb::cascades::WebLoadStatus::Succeeded)
    {
    	eventContainer_->fireEvent();
    	loading_->stop();
        TiLogger::getInstance().log("WebLoadStatus::Type::Succeeded");
    	return;
    }
    if(webRequest->status() == bb::cascades::WebLoadStatus::Failed)
    {
        TiLogger::getInstance().log("WebLoadStatus::Type::Succeeded");
    	return;
    }

}

void WebViewEventHandler::onLoadProgress(int a)
{
	eventContainer_->fireEvent();
    TiLogger::getInstance().log("onLoadProgress");
}

void WebViewEventHandler::onTitleChanged (const QString &title)
{
	eventContainer_->fireEvent();
    TiLogger::getInstance().log("onUrlChanged");
}

void WebViewEventHandler::onNavigationHistoryChanged ()
{
	eventContainer_->fireEvent();
    TiLogger::getInstance().log("onUrlChanged");
}

void WebViewEventHandler::onUrlChanged (const QUrl &url)
{
	eventContainer_->fireEvent();
    TiLogger::getInstance().log("onUrlChanged");
}

void WebViewEventHandler::onIconChanged (const QUrl &icon)
{
	eventContainer_->fireEvent();
    TiLogger::getInstance().log("onIconChanged");
}

void WebViewEventHandler::onNavigationRequested (bb::cascades::WebNavigationRequest *request)
{
	eventContainer_->fireEvent();
    TiLogger::getInstance().log("onNavigationRequested");
}

void WebViewEventHandler::onJavaScriptResult (int resultId, const QVariant &result)
{
	eventContainer_->fireEvent();
    TiLogger::getInstance().log("onJavaScriptResult");
}

void WebViewEventHandler::onJavaScriptInterrupted ()
{
	eventContainer_->fireEvent();
    TiLogger::getInstance().log("onJavaScriptInterrupted");
}

void WebViewEventHandler::onMessageReceived (const QVariantMap &message)
{
	eventContainer_->fireEvent();
    TiLogger::getInstance().log("onMessageReceived");
}

void WebViewEventHandler::onMicroFocusChanged ()
{
	eventContainer_->fireEvent();
    TiLogger::getInstance().log("onMicroFocusChanged");
}

void WebViewEventHandler::onMinContentScaleChanged (float minContentScale)
{
	eventContainer_->fireEvent();
//	scroller_->scrollViewProperties()->setMinContentScale(minContentScale);
}
void WebViewEventHandler::onMaxContentScaleChanged (float maxContentScale)
{
	eventContainer_->fireEvent();
//	scroller_->scrollViewProperties()->setMaxContentScale(maxContentScale);
}
