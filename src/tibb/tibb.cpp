/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "tibb.h"
#include "TitaniumRuntime.h"
#include <string>

#include "TiModule.h"

map<std::string, TiModule*> g_tiRegisterModuleMap;

int tibb_run(const char* javaScript, int argc, char** argv)
{
    return TitaniumRuntime::run(javaScript, argc, argv);
}

void tiRegisterModule(std::string name, TiModule* module)
{
	g_tiRegisterModuleMap[name] = module;
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
