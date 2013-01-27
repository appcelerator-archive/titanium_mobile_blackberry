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

void TiUIWebView::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
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

Handle<Value> TiUIWebView::_evalJS(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope scope;
    TiUIWebView* self = static_cast<TiUIWebView*>(userContext);
    NativeWebViewObject* webview = static_cast<NativeWebViewObject*>(self->getNativeObject());

    QString javascript = QString::fromUtf8(*String::Utf8Value(args[0]));
    webview->evalJS(javascript);
    return Undefined();
}
