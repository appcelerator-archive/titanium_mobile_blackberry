/*
 * NativeWebViewObject.h
 *
 *  Created on: Jan 25, 2013
 *      Author: penrique
 */

#ifndef NATIVEWEBVIEWOBJECT_H_
#define NATIVEWEBVIEWOBJECT_H_

#include "NativeControlObject.h"
#include <QtCore/QObject>
#include "TiLogger.h"

namespace bb
{
namespace cascades
{
class WebView;
class ScrollView;
class ScrollViewProperties;
class ScrollMode;
class WebLoadRequest;
class WebNavigationRequest;
class ActivityIndicator;

}
}

class NativeWebViewObject : public NativeControlObject
{
public:
    static NativeWebViewObject* createWebView(TiObject* tiObject);
    virtual ~NativeWebViewObject();
    virtual NATIVE_TYPE getObjectType() const;
    virtual int initialize();
    // properties
    virtual int setData(TiObject* obj);
    virtual int setDisableBounce(TiObject* obj);
    virtual int setEnableZoomControls(TiObject* obj);
    virtual int setHideLoadIndicator(TiObject* obj);
    virtual int setHtml(TiObject* obj);
    virtual int setLoading(TiObject* obj);
    virtual int setPluginState(TiObject* obj);
    virtual int setScalesPageToFit(TiObject* obj);
    virtual int setScrollsToTop(TiObject* obj);
    virtual int setShowScrollbars(TiObject* obj);
    virtual int setUrl(TiObject* obj);
    virtual int setUserAgent(TiObject* obj);
    virtual int setWillHandleTouches(TiObject* obj);

    // methods
    virtual int evalJS(QString javascript);

    bool canGoBack();
    void goBack();
    bool canGoForward();
    void goForward();
    void reload();

    bool isLocal_;
    bb::cascades::WebView *getWebView();
    bb::cascades::ScrollView *getScroller();
    bb::cascades::ActivityIndicator *getLoadingIndicator();
protected:
    virtual void setupEvents(TiEventContainerFactory* containerFactory);

private:

    explicit NativeWebViewObject(TiObject* tiObject);
    // Disable copy ctor & assignment operator
    NativeWebViewObject(const NativeWebViewObject&);
    void operator=(const NativeWebViewObject&);

    bb::cascades::WebView* webview_;
    bb::cascades::ScrollView* scroller_;
    bb::cascades::ActivityIndicator* loading_;
};


//Event handler for webview object
class WebViewEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit WebViewEventHandler(TiEventContainer* eventContainer, NativeWebViewObject* webviewObject);
    virtual ~WebViewEventHandler();

public slots:

	void onLoadingChanged(bb::cascades::WebLoadRequest* webRequest);
	void onLoadProgress(int a);
	void onTitleChanged (const QString &title);
	void onNavigationHistoryChanged ();
	void onUrlChanged (const QUrl &url);
	void onIconChanged (const QUrl &icon);
	void onNavigationRequested (bb::cascades::WebNavigationRequest *request);
	void onJavaScriptResult (int resultId, const QVariant &result);
	void onJavaScriptInterrupted ();
	void onMessageReceived (const QVariantMap &message);
	void onMicroFocusChanged ();
	void onMinContentScaleChanged (float minContentScale);
	void onMaxContentScaleChanged (float maxContentScale);


private:
    TiEventContainer* eventContainer_;
    NativeWebViewObject* webviewObject_;
    bb::cascades::WebView *webview_;
    bb::cascades::ScrollView *scroller_;
    bb::cascades::ActivityIndicator* loading_;
    // Disable copy ctor & assignment operator
    WebViewEventHandler(const WebViewEventHandler& eHandler);
    WebViewEventHandler& operator=(const WebViewEventHandler& eHandler);
};


#endif /* NATIVEWEBVIEWOBJECT_H_ */
