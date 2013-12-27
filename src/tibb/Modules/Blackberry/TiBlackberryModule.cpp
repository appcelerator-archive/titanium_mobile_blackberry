/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiBlackberryModule.h"
#include "PushNotification/TiPushNotificationProxy.h"

using namespace TiBlackberry;
TiBlackberryModule::TiBlackberryModule(const char* name) : Ti::TiModule(name)
{
	addFunction("createPushService", TiPushNotificationProxy::CreateProxy);
}

TiBlackberryModule::~TiBlackberryModule()
{

}

Ti::TiValue TiBlackberryModule::getModuleId()
{
	Ti::TiValue val;
	val.setString("ti.blackberry");
	return val;
}
Ti::TiValue TiBlackberryModule::getModuleVersion()
{
	Ti::TiValue val;
	val.setString("1.0");
	return val;
}
Ti::TiValue TiBlackberryModule::getModuleName()
{
	Ti::TiValue val;
	val.setString("TiBlackberry");
	return val;
}
