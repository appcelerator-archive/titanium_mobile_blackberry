/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIBB_H_
#define TIBB_H_

#include <string>
#include "TiModule.h"

extern "C"
{
    int tibb_run(const char* javaScript, int argc, char** argv);

    void tiRegisterModule(std::string name, TiModule* module);

    TiModule* getModuleByName(std::string name);
}

#endif /* TIBB_H_ */
