/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "tibb.h"

#include <fstream>
#include <string>
#include "TiCore.h"

#include <v8.h>
//#include "ReplaceWithModuleName.h"

/**
 * To test native modules make sure to include the module header file
 * and register the module.
 */

using namespace std;
class Ti::TiModule;

typedef Handle<Object> (*ModuleStartup)();

int main(int argc, char** argv)
{

	string javascript;
    {
        ifstream ifs("app/native/assets/app.js");
        if (!ifs)
        {
            return -1;
        }
        getline(ifs, javascript, string::traits_type::to_char_type(string::traits_type::eof()));
        ifs.close();
    }
    startV8Engine();
    int ret = tibb_run(javascript.c_str(), argc, argv);
    return ret;
}

