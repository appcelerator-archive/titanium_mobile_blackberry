/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TITANIUMRUNTIME_H_
#define TITANIUMRUNTIME_H_

#include "TiObject.h"
#include "TiObjectScope.h"

class TitaniumRuntime
{
public:
    static int run(const char* javaScript, int argc, char** argv);
private:
    TitaniumRuntime();
    TitaniumRuntime(const char* javaScript);
    virtual ~TitaniumRuntime();
    int internalRun(int argc, char** argv);
    void Log(const char* msg);

    char* javaScript_;
    TiObjectScope rootObject_;
};

#endif /* TITANIUMRUNTIME_H_ */
