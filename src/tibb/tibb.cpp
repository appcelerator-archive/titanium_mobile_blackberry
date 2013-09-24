/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "tibb.h"
#include "TitaniumRuntime.h"
#include <string>
#include "TiModuleRegistry.h"
#include "TiModule.h"
#include <v8.h>

map<std::string, TiModule*> g_tiRegisterModuleMap;

void startV8Engine() {
    HandleScope handleScope;
	v8::Persistent<v8::Context> ctx = v8::Context::New(NULL, v8::ObjectTemplate::New());
	TitaniumRuntime::setContext(ctx);
}
int tibb_run(const char* javaScript, int argc, char** argv)
{
    return TitaniumRuntime::run(javaScript, argc, argv);
}

void tiRegisterModule(const char* name, ModuleStartup module)
{
	TiModuleRegistry::RegisterModule(QString(name), module);
}

TiModule* getModuleByName(const std::string name)
{
	std::map<std::string, TiModule*>::iterator it = g_tiRegisterModuleMap.find(name);
	if (it != g_tiRegisterModuleMap.end()) {
		return g_tiRegisterModuleMap.find(name)->second;
	}
	else {
		return NULL;
	}
}
