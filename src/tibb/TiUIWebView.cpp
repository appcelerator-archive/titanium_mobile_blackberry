/*
 * TiUIWebView.cpp
 *
 *  Created on: Jan 25, 2013
 *      Author: penrique
 */

#include "TiUIWebView.h"
#include "NativeWebViewObject.h"
#include "TiGenericFunctionObject.h"
#include "V8Utils.h"

static QList<TiUIWebView*> webViews_;

QList<TiUIWebView*> TiUIWebView::getWebViews()
{
	return webViews_;
}


TiUIWebView::TiUIWebView()
    : TiUIBase("WebView")
{
}

TiUIWebView::~TiUIWebView()
{
   webViews_.removeOne(this);
}

TiUIWebView* TiUIWebView::createWebView(NativeObjectFactory* nativeObjectFactory)
{
	TiUIWebView* obj = new TiUIWebView;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    webViews_.append(obj);
    return obj;
}

void TiUIWebView::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "goBack", this, _goBack);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "canGoBack", this, _canGoBack);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "goForward", this, _goForward);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "canGoForward", this, _canGoForward);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "reload", this, _reload);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "evalJS", this, _evalJS);
}

void TiUIWebView::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_WEBVIEW, this);
        setNativeObject(obj);
        obj->release();
    }
}

bb::cascades::WebView* TiUIWebView::getNativeWebView()
{
	NativeWebViewObject* nativeWebView = static_cast<NativeWebViewObject*>(getNativeObject());
	return nativeWebView->getWebView();
}

Handle<Value> TiUIWebView::_evalJS(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope scope;
    TiUIWebView* self = static_cast<TiUIWebView*>(userContext);
    NativeWebViewObject* webview = static_cast<NativeWebViewObject*>(self->getNativeObject());

    QString javascript = QString::fromUtf8(*String::Utf8Value(args[0]));
    webview->evalJS(javascript);
    return Undefined();
}

Handle<Value> TiUIWebView::_reload(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope scope;
    TiUIWebView* self = static_cast<TiUIWebView*>(userContext);
    NativeWebViewObject* webview = static_cast<NativeWebViewObject*>(self->getNativeObject());
    webview->reload();
    return Undefined();
}

Handle<Value> TiUIWebView::_goBack(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope scope;
    TiUIWebView* self = static_cast<TiUIWebView*>(userContext);
    NativeWebViewObject* webview = static_cast<NativeWebViewObject*>(self->getNativeObject());
    webview->goBack();
    return Undefined();
}

Handle<Value> TiUIWebView::_canGoBack(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope scope;
    TiUIWebView* self = static_cast<TiUIWebView*>(userContext);
    NativeWebViewObject* webview = static_cast<NativeWebViewObject*>(self->getNativeObject());
    return Boolean::New(webview->canGoBack());
}

Handle<Value> TiUIWebView::_goForward(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope scope;
    TiUIWebView* self = static_cast<TiUIWebView*>(userContext);
    NativeWebViewObject* webview = static_cast<NativeWebViewObject*>(self->getNativeObject());

    webview->goForward();
    return Undefined();
}

Handle<Value> TiUIWebView::_canGoForward(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope scope;
    TiUIWebView* self = static_cast<TiUIWebView*>(userContext);
    NativeWebViewObject* webview = static_cast<NativeWebViewObject*>(self->getNativeObject());

    QString javascript = QString::fromUtf8(*String::Utf8Value(args[0]));
    return Boolean::New(webview->canGoForward());
}
