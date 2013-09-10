/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIBB_H_
#define TIBB_H_

#include <v8.h>

typedef v8::Handle<v8::Object> (*ModuleStartup)();

extern "C"
{
	void startV8Engine();
	int tibb_run(const char* javaScript, int argc, char** argv);
    void tiRegisterModule(const char* name, ModuleStartup mod);
}

#endif /* TIBB_H_ */
