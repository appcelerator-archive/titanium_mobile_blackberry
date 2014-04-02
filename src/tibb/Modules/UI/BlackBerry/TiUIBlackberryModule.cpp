/**
 * TiUIBlackberry.cpp
 *
 *
 */

#include "TiUIBlackberryModule.h"
#include "ApplicationMenu/ApplicationMenuProxy.h"
#include "NavButton/NavButtonProxy.h"
#include "View/TiUIViewProxy.h"
#include "WebView/TiUIWebViewProxy.h"
#include "Button/TiUIButtonProxy.h"
using namespace TiUI;

TiUIBlackberryModule::TiUIBlackberryModule(const char* name) : Ti::TiModule(name)
{
	addFunction("createApplicationMenu", ApplicationMenuProxy::CreateProxy);
	addFunction("createNavButton", NavButtonProxy::CreateProxy);
	addFunction("createView", TiUIViewProxy::CreateProxy);
	addFunction("createWebView", TiUIWebViewProxy::CreateProxy);
	addFunction("createButton", TiUIButtonProxy::CreateProxy);

	addNumber("WEBVIEW_NAVIGATION_TYPE_LINK_CLICKED", bb::cascades::WebNavigationType::LinkClicked);
	addNumber("WEBVIEW_NAVIGATION_TYPE_FORM_SUBMIT", bb::cascades::WebNavigationType::FormSubmitted);
	addNumber("WEBVIEW_NAVIGATION_TYPE_BACK_FORWARD", bb::cascades::WebNavigationType::BackForward);
	addNumber("WEBVIEW_NAVIGATION_TYPE_RELOAD", bb::cascades::WebNavigationType::Reload);
	addNumber("WEBVIEW_NAVIGATION_TYPE_FORM_RESUBMIT", bb::cascades::WebNavigationType::FormResubmitted);
	addNumber("WEBVIEW_NAVIGATION_TYPE_OTHER", bb::cascades::WebNavigationType::Other);
	addNumber("WEBVIEW_NAVIGATION_TYPE_OPEN_WINDOW", bb::cascades::WebNavigationType::OpenWindow);
}

TiUIBlackberryModule::~TiUIBlackberryModule()
{

}

Ti::TiValue TiUIBlackberryModule::getModuleId()
{
	Ti::TiValue val;
	val.setString("ti.ui.blackberry");
	return val;
}
Ti::TiValue TiUIBlackberryModule::getModuleVersion()
{
	Ti::TiValue val;
	val.setString("1.0");
	return val;
}
Ti::TiValue TiUIBlackberryModule::getModuleName()
{
	Ti::TiValue val;
	val.setString("TiUIBlackberry");
	return val;
}
