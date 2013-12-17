/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiAppModule.h"
#include "TiAppPropertiesModule.h"
#include <bb/ApplicationInfo>
#include <bb/PackageInfo>

#include "TiUIWebView.h"

TiAppModule::TiAppModule(const char* name) : Ti::TiModule(name)
{

	addModule("Properties", TiAppPropertiesModule::CreateModule());
	createPropertyFunction("fireSystemEvent", _fireSystemEvent);
	createPropertyFunction("getArguments", _getArguments);

	createPropertyGetter("EVENT_ACCESSIBILITY_ANNOUNCEMENT", _getEVENT_ACCESSIBILITY_ANNOUNCEMENT);
	createPropertyGetter("EVENT_ACCESSIBILITY_CHANGED", _getEVENT_ACCESSIBILITY_CHANGED);
	createPropertyGetter("accessibilityEnabled", _getAccessibilityEnabled);
	createPropertyGetter("analytics", _getAnalytics);
	createPropertyGetter("copyright", _getCopyright);
	createPropertyGetter("deployType", _getDeployType);
	createPropertyGetter("description", _getDescription);
	createPropertyGetter("guid", _getGuid);
	createPropertyGetter("GUID", _getGuid);
	createPropertyGetter("id", _getId);
	createPropertyGetter("ID", _getId);
	createPropertyGetter("installId", _getInstallId);
	createPropertyGetter("name", _getName);
	createPropertyGetter("proximityState", _getProximityState);
	createPropertyGetter("publisher", _getPublisher);
	createPropertyGetter("sessionId", _getSessionId);
	createPropertyGetter("url", _getUrl);
	createPropertyGetter("URL", _getUrl);
	createPropertyGetter("version", _getVersion);
	createPropertyGetter("keyboardVisible", _getKeyboardVisible);

	createPropertySetterGetter("idleTimerDisabled", _setIdleTimerDisabled,  _getIdleTimerDisabled);
	createPropertySetterGetter("proximityDetection", _setProximityDetection,  _getProximityDetection);
	createPropertySetterGetter("disableNetworkActivityIndicator", _setDisableNetworkActivityIndicator,  _getDisableNetworkActivityIndicator);

}

TiAppModule::~TiAppModule()
{

}

void TiAppModule::fireEvent(QString eventName, Ti::TiEventParameters eventParams)
{
	Ti::TiProxy::fireEvent(eventName, eventParams);
	QList<TiUIWebView*> webViews = TiUIWebView::getWebViews();
	if(webViews.size() > 0)
	{
		Ti::TiEventParameters webViewEventParams;
		webViewEventParams.addParam("data", eventParams);
		webViewEventParams.addParam("id", eventName);

		QString json = webViewEventParams.toJsonQString();
		for(int i = 0, len = webViews.length(); i < len; i++)
		{
			webViews.at(i)->getNativeWebView()->postMessage(json);
		}
	}
}

Ti::TiValue TiAppModule::getModuleId()
{
	Ti::TiValue val;
	val.setString("ti.app");
	return val;
}
Ti::TiValue TiAppModule::getModuleVersion()
{
	Ti::TiValue val;
	val.setString("1.0");
	return val;
}
Ti::TiValue TiAppModule::getModuleName()
{
	Ti::TiValue val;
	val.setString("TiApp");
	return val;
}

Ti::TiValue TiAppModule::fireSystemEvent(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppModule::getArguments(Ti::TiValue)
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}

void TiAppModule::setIdleTimerDisabled(Ti::TiValue)
{
}
void TiAppModule::setProximityDetection(Ti::TiValue)
{
}
void TiAppModule::setDisableNetworkActivityIndicator(Ti::TiValue)
{
}

Ti::TiValue TiAppModule::getEVENT_ACCESSIBILITY_ANNOUNCEMENT()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppModule::getEVENT_ACCESSIBILITY_CHANGED()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppModule::getAccessibilityEnabled()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppModule::getAnalytics()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppModule::getCopyright()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppModule::getDeployType()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppModule::getDescription()
{
	Ti::TiValue val;
	bb::PackageInfo info;
	val.setString(info.description());
	return val;
}
Ti::TiValue TiAppModule::getGuid()
{
	Ti::TiValue val;
	bb::PackageInfo info;
	val.setString(info.versionSigningHash());
	return val;
}
Ti::TiValue TiAppModule::getId()
{
	Ti::TiValue val;
	bb::PackageInfo info;
	val.setString(info.installId());
	return val;
}
Ti::TiValue TiAppModule::getInstallId()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppModule::getIdleTimerDisabled()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppModule::getName()
{
	Ti::TiValue val;
	bb::ApplicationInfo info;
	val.setString(info.title());
	return val;
}
Ti::TiValue TiAppModule::getProximityDetection()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppModule::getProximityState()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppModule::getDisableNetworkActivityIndicator()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppModule::getPublisher()
{
	Ti::TiValue val;
	bb::PackageInfo info;
	val.setString(info.author());
	return val;
}
Ti::TiValue TiAppModule::getSessionId()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppModule::getUrl()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiAppModule::getVersion()
{
	Ti::TiValue val;
	bb::PackageInfo info;
	val.setString(info.version());
	return val;
}
Ti::TiValue TiAppModule::getKeyboardVisible()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
