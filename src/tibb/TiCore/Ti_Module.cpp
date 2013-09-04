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
}

void Ti::TiModule::addModule(const char* name, Handle<Object> obj)
{
	HandleScope scope;
	getJSObject()->Set(String::New(name), obj);
}

void Ti::TiModule::addString(QString name, QString value)
{
	HandleScope scope;
	getJSObject()->Set(String::New(name.toLocal8Bit().data()), String::New(value.toLocal8Bit().data()));
}
Ti::TiModule::~TiModule() {
	// TODO Auto-generated destructor stub
}

