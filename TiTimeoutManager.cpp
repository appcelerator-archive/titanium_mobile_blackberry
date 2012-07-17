/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiTimeoutManager.h"

#include "NativeTimeoutHandler.h"

TiTimeoutManager* TiTimeoutManager::instance()
{
    static TiTimeoutManager instance;
    return &instance;
}

int TiTimeoutManager::createTimeout(int number, Handle<Function> eventFunction, bool interval)
{
    NativeTimeoutHandler* timeout = new NativeTimeoutHandler(number, eventFunction, interval);
    timeoutList_.insert(std::make_pair(std::make_pair(timeout->getId(), interval), timeout));
    return timeout->getId();
}

void TiTimeoutManager::clearTimeout(int id, bool interval)
{
    std::map<std::pair<int, bool>, NativeTimeoutHandler*>::iterator itr = timeoutList_.find(std::make_pair(id, interval));
    if (itr != timeoutList_.end() && itr->second != NULL)
    {
        if (itr->first.second == interval)
        {
            itr->second->clearTimeout();
            delete itr->second;
            timeoutList_.erase(itr);
        }
    }
}

TiTimeoutManager::~TiTimeoutManager()
{
    std::map<std::pair<int, bool>, NativeTimeoutHandler*>::iterator itr = timeoutList_.begin();
    for (; itr != timeoutList_.end(); itr++)
    {
        if (itr != timeoutList_.end() && itr->second != NULL)
        {
            itr->second->clearTimeout();
            delete itr->second;
        }
    }
}

TiTimeoutManager::TiTimeoutManager()
{
}
