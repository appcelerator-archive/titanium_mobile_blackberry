/*
 * TiModule.cpp
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "Ti_Module.h"
#include "Ti_Helper.h"
Ti::TiModule::TiModule(const char* name) : Ti::TiProxy(name) {
	createPropertyGetter("id", _getModuleId);
	createPropertyGetter("version", _getModuleVersion);
	createPropertyGetter("name", _getModuleName);
}

Ti::TiValue Ti::TiModule::getModuleId()
{
	Ti::TiValue val;
	val.setString("");
	return val;
}
Ti::TiValue Ti::TiModule::getModuleVersion()
{
	Ti::TiValue val;
	val.setString("");
	return val;
}
Ti::TiValue Ti::TiModule::getModuleName()
{
	Ti::TiValue val;
	val.setString("root_module");
	return val;
}
void Ti::TiModule::addModule(const char* name, Handle<Object> obj)
{
	HandleScope scope;
	getJSObject()->Set(String::New(name), obj, DontDelete);
}

void Ti::TiModule::addString(QString name, QString value)
{
	HandleScope scope;
	getJSObject()->Set(String::New(name.toLocal8Bit().data()), String::New(value.toLocal8Bit().data()), DontDelete);
}

void Ti::TiModule::addNumber(QString name, double value)
{
	HandleScope scope;
	getJSObject()->Set(String::New(name.toLocal8Bit().data()), Number::New(value), DontDelete);
}

void Ti::TiModule::initStart()
{
	Ti::TiProxy::initStart();
}

void Ti::TiModule::initEnd()
{
	Ti::TiProxy::initEnd();
}


Ti::TiModule::~TiModule() {
	// TODO Auto-generated destructor stub
}

