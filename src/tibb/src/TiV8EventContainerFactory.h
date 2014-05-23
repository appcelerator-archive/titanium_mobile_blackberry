/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIV8EVENTCONTAINERFACTORY_H_
#define TIV8EVENTCONTAINERFACTORY_H_

#include "TiEventContainerFactory.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <v8.h>
#pragma GCC diagnostic warning "-Wunused-parameter"

using namespace v8;

/*
 * TiV8EventContainerFactory
 *
 * V8 specific container factory
 */

class TiV8EventContainerFactory : public TiEventContainerFactory
{
public:
    static TiV8EventContainerFactory* createEventContainerFactory(Handle<ObjectTemplate> temp);
    virtual TiEventContainer* createEventContainer();
    virtual ~TiV8EventContainerFactory();

protected:
    TiV8EventContainerFactory();

private:
    Persistent<ObjectTemplate> globalTemplate_;
};

#endif /* TIV8EVENTCONTAINERFACTORY_H_ */
