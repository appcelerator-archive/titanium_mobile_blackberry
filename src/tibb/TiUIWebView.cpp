/*
 * TiUIWebView.cpp
 *
 *  Created on: Jan 25, 2013
 *      Author: penrique
 */

#include "TiUIWebView.h"
#include "NativeWebViewObject.h"
#include "TiGenericFunctionObject.h"

TiUIWebView::TiUIWebView(const char* name)
    : TiUIBase(name)
{
}

TiUIWebView::TiUIWebView()
    : TiUIBase("")
{
}

TiUIWebView::~TiUIWebView()
{
}

TiUIWebView* TiUIWebView::createWebView(NativeObjectFactory* nativeObjectFactory)
{
	TiUIWebView* obj = new TiUIWebView;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

static Handle<Value> _meh(void* userContext, TiObject* caller, const Arguments& args)
{
    return String::New("webview!");
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
    TiGenericFunctionObject::addGenericFunctionToParent(this, "_meh", this, _meh);
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
