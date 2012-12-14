/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "tibb.h"
#include "TitaniumRuntime.h"

int tibb_run(const char* javaScript, int argc, char** argv)
{
    return TitaniumRuntime::run(javaScript, argc, argv);
}
