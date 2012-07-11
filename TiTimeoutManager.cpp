/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiTimeoutManager.h"

#include "NativeTimeoutHandler.h"

TiTimeoutManager* TiTimeoutManager::timeoutManager_ = NULL;

TiTimeoutManager* TiTimeoutManager::instance()
{
    if (!timeoutManager_)
    {
        timeoutManager_ = new TiTimeoutManager;
    }
    return timeoutManager_;
}

int TiTimeoutManager::createTimeout(Handle<Number> number, Handle<Function> eventFunction, bool interval)
{
    NativeTimeoutHandler* timeout = new NativeTimeoutHandler(number, eventFunction, interval);
    timeoutList_.insert(std::make_pair(std::make_pair(timeout->getId(), interval), timeout));
    return timeout->getId();
}

void TiTimeoutManager::clearTimeout(int id, bool interval)
{
    std::map<std::pair<int, bool>, NativeTimeoutHandler*>::iterator itr = timeoutList_.find(std::make_pair(id, interval));
    if (itr != timeoutList_.end() && itr->second)
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
        if (itr != timeoutList_.end() && itr->second)
        {
            itr->second->clearTimeout();
            delete itr->second;
        }
    }
}

TiTimeoutManager::TiTimeoutManager()
{
}
