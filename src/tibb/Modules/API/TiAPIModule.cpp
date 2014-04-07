/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiAPIModule.h"

TiAPIModule::TiAPIModule(const char* name) : Ti::TiModule(name)
{
	createPropertyFunction("debug", _debug);
	createPropertyFunction("error", _error);
	createPropertyFunction("info", _info);
	createPropertyFunction("log", _log );
	createPropertyFunction("timestamp", _timestamp);
	createPropertyFunction("trace", _trace);
	createPropertyFunction("warn", _warn);
}

TiAPIModule::~TiAPIModule()
{

}

Ti::TiValue TiAPIModule::getModuleId()
{
	Ti::TiValue val;
	val.setString("ti.api");
	return val;
}
Ti::TiValue TiAPIModule::getModuleVersion()
{
	Ti::TiValue val;
	val.setString("1.0");
	return val;
}
Ti::TiValue TiAPIModule::getModuleName()
{
	Ti::TiValue val;
	val.setString("TiAPI");
	return val;
}

Ti::TiValue TiAPIModule::debug(Ti::TiValue val)
{
	QString str = "[DEBUG] " + val.toString();
	Ti::TiHelper::Log(str);
	return Ti::TiValue();
}
Ti::TiValue TiAPIModule::error(Ti::TiValue val)
{
	QString str = "[ERROR] " + val.toString();
	Ti::TiHelper::Log(str);
	return Ti::TiValue();
}
Ti::TiValue TiAPIModule::info(Ti::TiValue val)
{
	QString str = "[INFO] " + val.toString();
	Ti::TiHelper::Log(str);
	return Ti::TiValue();
}
Ti::TiValue TiAPIModule::log (Ti::TiValue val)
{
	QString str = "[INFO] " + val.toString();
	Ti::TiHelper::Log(str);
	return Ti::TiValue();
}
Ti::TiValue TiAPIModule::timestamp(Ti::TiValue val)
{
	QString str = "[TIMESTAMP] " + val.toString();
	Ti::TiHelper::Log(str);
	return Ti::TiValue();
}
Ti::TiValue TiAPIModule::trace(Ti::TiValue val)
{
	QString str = "[TRACE] " + val.toString();
	Ti::TiHelper::Log(str);
	return Ti::TiValue();
}
Ti::TiValue TiAPIModule::warn(Ti::TiValue val)
{
	QString str = "[WARN] " + val.toString();
	Ti::TiHelper::Log(str);
	return Ti::TiValue();
}


