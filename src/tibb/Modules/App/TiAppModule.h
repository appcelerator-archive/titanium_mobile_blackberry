/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIAPPMODULE_H_
#define TIAPPMODULE_H_

#include "TiCore.h"

class TiAppModule : public Ti::TiModule
{
public:
	CREATE_MODULE(TiAppModule);
	TiAppModule(const char*);
	virtual ~TiAppModule();

	virtual Ti::TiValue getModuleId();
	virtual Ti::TiValue getModuleVersion();
	virtual Ti::TiValue getModuleName();

	virtual void fireEvent(QString, Ti::TiEventParameters);

	static TiAppModule* getInstance();

	Ti::TiValue fireSystemEvent(Ti::TiValue);
	Ti::TiValue getArguments(Ti::TiValue);

	void setIdleTimerDisabled(Ti::TiValue);
	void setProximityDetection(Ti::TiValue);
	void setDisableNetworkActivityIndicator(Ti::TiValue);

	Ti::TiValue getEVENT_ACCESSIBILITY_ANNOUNCEMENT();
	Ti::TiValue getEVENT_ACCESSIBILITY_CHANGED();
	Ti::TiValue getAccessibilityEnabled();
	Ti::TiValue getAnalytics();
	Ti::TiValue getCopyright();
	Ti::TiValue getDeployType();
	Ti::TiValue getDescription();
	Ti::TiValue getGuid();
	Ti::TiValue getId();
	Ti::TiValue getInstallId();
	Ti::TiValue getIdleTimerDisabled();
	Ti::TiValue getName();
	Ti::TiValue getProximityDetection();
	Ti::TiValue getProximityState();
	Ti::TiValue getDisableNetworkActivityIndicator();
	Ti::TiValue getPublisher();
	Ti::TiValue getSessionId();
	Ti::TiValue getUrl();
	Ti::TiValue getVersion();
	Ti::TiValue getKeyboardVisible();

	EXPOSE_METHOD(TiAppModule, fireSystemEvent)
	EXPOSE_METHOD(TiAppModule, getArguments)

	EXPOSE_SETTER(TiAppModule, setIdleTimerDisabled)
	EXPOSE_SETTER(TiAppModule, setProximityDetection)
	EXPOSE_SETTER(TiAppModule, setDisableNetworkActivityIndicator)

	EXPOSE_GETTER(TiAppModule, getEVENT_ACCESSIBILITY_ANNOUNCEMENT)
	EXPOSE_GETTER(TiAppModule, getEVENT_ACCESSIBILITY_CHANGED)
	EXPOSE_GETTER(TiAppModule, getAccessibilityEnabled)
	EXPOSE_GETTER(TiAppModule, getAnalytics)
	EXPOSE_GETTER(TiAppModule, getCopyright)
	EXPOSE_GETTER(TiAppModule, getDeployType)
	EXPOSE_GETTER(TiAppModule, getDescription)
	EXPOSE_GETTER(TiAppModule, getGuid)
	EXPOSE_GETTER(TiAppModule, getId)
	EXPOSE_GETTER(TiAppModule, getInstallId)
	EXPOSE_GETTER(TiAppModule, getIdleTimerDisabled)
	EXPOSE_GETTER(TiAppModule, getName)
	EXPOSE_GETTER(TiAppModule, getProximityDetection)
	EXPOSE_GETTER(TiAppModule, getProximityState)
	EXPOSE_GETTER(TiAppModule, getDisableNetworkActivityIndicator)
	EXPOSE_GETTER(TiAppModule, getPublisher)
	EXPOSE_GETTER(TiAppModule, getSessionId)
	EXPOSE_GETTER(TiAppModule, getUrl)
	EXPOSE_GETTER(TiAppModule, getVersion)
	EXPOSE_GETTER(TiAppModule, getKeyboardVisible)
};

#endif /* TIAPPMODULE_H_ */
