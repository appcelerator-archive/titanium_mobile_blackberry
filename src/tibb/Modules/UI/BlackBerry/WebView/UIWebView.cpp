/*
 * UIWebView.cpp
 *
 *  Created on: Sunday, September 15, 2013
 *      Author: penrique
 */

#include "UIWebView.h"
#include <bb/cascades/ScrollMode>
#include <bb/cascades/VerticalAlignment>
#include <bb/cascades/HorizontalAlignment>
#include <bb/cascades/OverScrollEffectMode>
#include "../../../App/TiAppModule.h"

namespace TiUI {

UIWebView::UIWebView(Ti::TiViewProxy* proxy) :
		Ti::TiView(proxy),
		_hasLoadEvent(false),
		_isLocal(false),
		_hasEvalEvent(false)
{
	_evalCallbacks = v8::Persistent<Object>::New(Object::New());
	_navigationType = bb::cascades::WebNavigationType::Other;

	_scrollView = new bb::cascades::ScrollView();
	_scrollViewProps = _scrollView->scrollViewProperties();
	_scrollViewProps->setScrollMode(bb::cascades::ScrollMode::Both);
	_scrollViewProps->setPinchToZoomEnabled(true);

	_webView = new bb::cascades::WebView();
	QVariantMap args;
	args["width"] = "device-width";
	args["initial-scale"] = QVariant(1.0);
	_webviewSettings = _webView->settings();
    _webviewSettings->setViewportArguments(args);
	_scrollView->setContent(_webView);
	setChildControl(_scrollView);

	_loadingIndicator = new bb::cascades::ActivityIndicator();
	_loadingIndicator->setMinHeight(100);
	_loadingIndicator->setMinWidth(100);
	_loadingIndicator->setVerticalAlignment(bb::cascades::VerticalAlignment::Center);
	_loadingIndicator->setHorizontalAlignment(bb::cascades::HorizontalAlignment::Center);
	bb::cascades::Container::add(_loadingIndicator);

    QObject::connect(_webView, SIGNAL(messageReceived (const QVariantMap &)), this, SLOT(onMessageReceived (const QVariantMap &)));
	QObject::connect(_webView, SIGNAL(loadingChanged(bb::cascades::WebLoadRequest*)), this, SLOT(onLoadingChanged(bb::cascades::WebLoadRequest*))
	);

}

bool UIWebView::ingoreWidth()
{
	return false;
}
bool UIWebView::ingoreHeight()
{
	return false;
}
QString UIWebView::defaultWidth()
{
	return Ti::TiConstants::SizeFILL;
}
QString UIWebView::defaultHeight()
{
	return Ti::TiConstants::SizeFILL;
}

bb::cascades::ScrollView* UIWebView::getNativeScrollView()
{
	return _scrollView;
}
bb::cascades::WebView* UIWebView::getNativeWebView()
{
	return _webView;
}

void UIWebView::onEventAdded(QString event)
{
	Ti::TiView::onEventAdded(event);
	if(_hasLoadEvent == false && (event == "beforeload" || event == "error" || event == "load" || event == "navigation"))
	{
		_hasLoadEvent = true;
		// this gets the navigationType
		QObject::connect(
				_webView,
				SIGNAL(navigationRequested(bb::cascades::WebNavigationRequest*)),
				this,
				SLOT(onNavigationRequested(bb::cascades::WebNavigationRequest*))
		);
	} else
	if(event == "focus")
	{

	} else
	if(event == "keypressed")
	{

	} else
	if(event == "longclick")
	{

	} else
	if(event == "longpress")
	{

	} else
	if(event == "pinch")
	{

	}
}

void UIWebView::setDisableBounce(bool flag)
{
	_scrollViewProps->setOverScrollEffectMode(flag ? bb::cascades::OverScrollEffectMode::None : bb::cascades::OverScrollEffectMode::OnPinchAndScroll);
}
void UIWebView::setIsLocal(bool isLocal)
{
	_isLocal = isLocal;
}

void UIWebView::setUserAgent(QString userAgent)
{
	_webviewSettings->setUserAgent(userAgent);
}

void UIWebView::hideLoadingIndicator()
{
	if(_loadingIndicator == NULL) return;
	bb::cascades::Container::remove(_loadingIndicator);
	delete _loadingIndicator;
	_loadingIndicator = NULL;
}

void UIWebView::onNavigationRequested(bb::cascades::WebNavigationRequest* request)
{
	_navigationType = request->navigationType();
	Ti::TiEventParameters eventParams;
	eventParams.addParam("url", request->url().toString());
	eventParams.addParam("type", (int)_navigationType);
	getProxy()->fireEvent("navigation", eventParams);
}

void UIWebView::onLoadingChanged(bb::cascades::WebLoadRequest* loadRequest)
{

	Ti::TiEventParameters eventParams;
	eventParams.addParam("status", (int)loadRequest->status());
	eventParams.addParam("url", loadRequest->url().toString());
	eventParams.addParam("navigationType", (int)_navigationType);
    switch (loadRequest->status())
    {
		case bb::cascades::WebLoadStatus::Started:
		{
			if(_loadingIndicator != NULL)
			{
				_loadingIndicator->start();
			}
			getProxy()->fireEvent("beforeload", eventParams);
			break;
		}
		case bb::cascades::WebLoadStatus::Succeeded:
		{
			if(_loadingIndicator != NULL)
			{
				_loadingIndicator->stop();
				bb::cascades::Container::remove(_loadingIndicator);
				delete _loadingIndicator;
				_loadingIndicator = NULL;
			}
			getProxy()->fireEvent("load", eventParams);
			if(_isLocal)
			{
	    		_webView->evaluateJavaScript("(function(){function e(e,t){if(typeof t=='string'||typeof t=='object')t=JSON.stringify(t);var t='log'+','+e+','+t;navigator.cascades.postMessage(t)}Ti={_event_listeners:[],createEventListener:function(e,t){var n={eventName:e,listener:t,systemId:-1,index:this._event_listeners.length};this._event_listeners.push(n);return n},getEventListenerByKey:function(e,t){for(var n=0;n<this._event_listeners.length;n++){if(this._event_listeners[n][e]==t){return this._event_listeners[n]}}return null},getEventListenerByName:function(e){for(var t=0;t<this._event_listeners.length;t++){if(this._event_listeners[t]['eventName']==e){return this._event_listeners[t]}}return null},API:{info:function(t){e('info',t)},debug:function(t){e('debug',t)},error:function(t){e('error',t)}},App:{addEventListener:function(e,t){var n=Ti.createEventListener(e,t);return n.systemId},removeEventListener:function(e,t){if(typeof t=='number'){var n=Ti.getEventListenerByKey('systemId',t);if(n!==null){Ti._event_listeners.splice(n.index,1)}}else{n=Ti.getEventListenerByKey('listener',t);if(n!==null){Ti._event_listeners.splice(n.index,1)}}},fireEvent:function(e,t){var n='event,'+e+','+JSON.stringify(t||{});navigator.cascades.postMessage(n)}},executeListener:function(e,t){var n=this.getEventListenerByName(e);if(n!==null){n.listener.call(n.listener,t)}}};navigator.cascades.onmessage=function(t){t=JSON.parse(t);Ti.executeListener(t.id,t.data)};Titanium=Ti})()");
			}
			break;
		}
		case bb::cascades::WebLoadStatus::Failed:
		{
			getProxy()->fireEvent("error", eventParams);
			break;
		}
    }
}

void UIWebView::onMessageReceived (const QVariantMap & message)
{
	QString msg = message.value("data").toString();
	QStringList parts = msg.split(',');
	QString type = parts.at(0).toLower();

	QString script_;
	if(type == "event")
	{
		script_ = "Ti.App.fireEvent('";
		script_.append(parts.at(1)).append("',");
		script_.append(parts.at(2)).append(");");
	}
	else if(type == "log")
	{
		script_ = "Ti.API.";
		script_.append(parts.at(1)).append("(");
		script_.append(parts.at(2)).append(");");
	}

	v8::HandleScope scope;
	Handle<Script> script = Script::Compile(String::New(script_.toLocal8Bit().data()));
 	scope.Close(script->Run());
// TODO:
// 	TiAppModule::getInstance()->fireEvent("", eventParams);
}
void UIWebView::onJavaScriptResult(int resultId, const QVariant& result)
{
	QString id = QString::number(resultId);

	Ti::TiValue callback(_evalCallbacks->Get(Ti::TiHelper::ValueFromQString(id)));
	if(callback.isUndefined()) return;

	Ti::TiValue e;

	Ti::TiValue index;
	index.setString(id);
	Ti::TiValue res;
	res.setString(result.toString());

	QMap<QString, Ti::TiValue> map;
	map["id"] = index;
	map["result"] = res;
	e.setMap(map);

	qDebug() << "[WEBIVEW] id:" << id << callback.toString();
	callback.callFunction(getProxy(), e);
}

void UIWebView::setScalesPageToFit(bool val){
	_webviewSettings->setZoomToFitEnabled(val);
}

void UIWebView::evalJS(QString str)
{
	_webView->evaluateJavaScript(str);
}

void UIWebView::evalJS(QString str, Ti::TiValue callback)
{
	if(!_hasEvalEvent) {
		_hasEvalEvent = true;
		QObject::connect(_webView, SIGNAL(javaScriptResult(int, const QVariant&)), this, SLOT(onJavaScriptResult(int, const QVariant&)));
	}
	int e = _webView->evaluateJavaScript(str);
	QString id = QString::number(e);
	qDebug() << "[WEBIVEW] id:" << id << callback.toString();
	_evalCallbacks->Set(Ti::TiHelper::ValueFromQString(id), callback.toJSValue());
}

UIWebView::~UIWebView()
{
	_evalCallbacks.Dispose();
	_evalCallbacks.Clear();
}
}
