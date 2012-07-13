/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TITIMEOUTMANAGER_H_
#define TITIMEOUTMANAGER_H_

#include <map>

#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <v8.h>
#pragma GCC diagnostic warning "-Wunused-parameter"

using namespace v8;

class NativeTimeoutHandler;

/**
 * TiTimeoutManager
 */
class TiTimeoutManager
{
public:
    static TiTimeoutManager* instance();
    void clearTimeout(int id, bool interval);
    int createTimeout(int number, Handle<Function> eventFunction, bool interval = false);
    ~TiTimeoutManager();

private:
    TiTimeoutManager();
    std::map<std::pair<int, bool>, NativeTimeoutHandler*> timeoutList_;
    static TiTimeoutManager* timeoutManager_;
};


#endif /* TITIMEOUTMANAGER_H_ */
