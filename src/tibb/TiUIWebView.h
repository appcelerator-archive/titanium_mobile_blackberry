/*
 * TiUIWebView.h
 *
 *  Created on: Jan 25, 2013
 *      Author: penrique
 */

#ifndef TIUIWEBVIEW_H_
#define TIUIWEBVIEW_H_

#include "TiUIBase.h"
#include <bb/cascades/WebView>

/*
 * TiUIWebView
 *
 * Represents a Titanium WebView object
 *
 */


class TiUIWebView: public TiUIBase
{
public:
    static TiUIWebView* createWebView(NativeObjectFactory* nativeObjectFactory);
    static QList<TiUIWebView*> getWebViews();
    bb::cascades::WebView *getNativeWebView();
protected:
    virtual ~TiUIWebView();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();

private:
	TiUIWebView();
	static Handle<Value> _evalJS(void* userContext, TiObject* caller, const Arguments& args);
	static Handle<Value> _goBack(void* userContext, TiObject* caller, const Arguments& args);
	static Handle<Value> _canGoBack(void* userContext, TiObject* caller, const Arguments& args);
	static Handle<Value> _goForward(void* userContext, TiObject* caller, const Arguments& args);
	static Handle<Value> _canGoForward(void* userContext, TiObject* caller, const Arguments& args);
	static Handle<Value> _reload(void* userContext, TiObject* caller, const Arguments& args);
};

#endif /* TIUIWEBVIEW_H_ */
