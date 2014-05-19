/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUIWEBVIEW_H_
#define TI_TIUIWEBVIEW_H_

#include <TiCore.h>

#include <bb/cascades/ScrollView>
#include <bb/cascades/WebView>
#include <bb/cascades/WebLoadRequest>
#include <bb/cascades/WebNavigationRequest>
#include <bb/cascades/WebNavigationType>
#include <bb/cascades/ActivityIndicator>
#include <bb/cascades/WebSettings>
#include <bb/cascades/ScrollViewProperties>
#include <v8.h>

namespace TiUI {

class UIWebView : public Ti::TiView
{
	Q_OBJECT;
public:
	UIWebView(Ti::TiViewProxy*);
	virtual ~UIWebView();
	virtual bool ingoreWidth();
	virtual bool ingoreHeight();
	virtual QString defaultWidth();
	virtual QString defaultHeight();
	virtual void onEventAdded(QString);
	void setUserAgent(QString);
	void setIsLocal(bool);
	void hideLoadingIndicator();
	void setScalesPageToFit(bool);
	void evalJS(QString);
	void evalJS(QString, Ti::TiValue);
	void setDisableBounce(bool);
	bb::cascades::ScrollView* getNativeScrollView();
	bb::cascades::WebView* getNativeWebView();
private:
	bool _isLocal;
	bool _hasLoadEvent;
	bool _hasEvalEvent;
	bb::cascades::ScrollView *_scrollView;
	bb::cascades::WebView *_webView;
	bb::cascades::WebNavigationType::Type _navigationType;
	bb::cascades::ActivityIndicator* _loadingIndicator;
	bb::cascades::WebSettings *_webviewSettings;
	v8::Persistent<Object> _evalCallbacks;
	bb::cascades::ScrollViewProperties *_scrollViewProps;
public slots:
	void onLoadingChanged(bb::cascades::WebLoadRequest* loadRequest);
	void onNavigationRequested(bb::cascades::WebNavigationRequest* request);
	void onJavaScriptResult(int resultId, const QVariant& result);
	void onMessageReceived (const QVariantMap &);
};
}
#endif /* TIUIWEBVIEW_H_ */
