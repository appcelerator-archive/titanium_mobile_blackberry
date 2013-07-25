/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef REPLACEWITHMODULENAME_H_
#define REPLACEWITHMODULENAME_H_

#include <TiModule.h>

#include <v8.h>


class ReplaceWithModuleName :  public TiModule
{

public:
    ReplaceWithModuleName();
    ReplaceWithModuleName(const ReplaceWithModuleName&);
    ReplaceWithModuleName& operator=(const ReplaceWithModuleName&);
    Handle<Value> startup();

private:
    // functions
    static Handle<Value> Example(const Arguments& args);

    // properties
    static Handle<Value> GetProperty(Local<String> name,
                                         const AccessorInfo& info);
    static void SetProperty(Local<String> name,
                                         Local<Value> value_obj,
                                         const AccessorInfo& info);
};

#endif /* REPLACEWITHMODULENAME_H_ */
