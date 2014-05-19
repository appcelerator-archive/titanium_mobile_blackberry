/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiV8EventContainerFactory.h"
#include "TiV8EventContainer.h"

TiV8EventContainerFactory::TiV8EventContainerFactory()
{
}

TiV8EventContainerFactory::~TiV8EventContainerFactory()
{
    if (!globalTemplate_.IsEmpty())
    {
        globalTemplate_.Dispose();
    }
}

TiEventContainer* TiV8EventContainerFactory::createEventContainer()
{
    HandleScope handleScope;
    Local<Object> eventData = globalTemplate_->NewInstance();
    TiV8EventContainer* obj = new TiV8EventContainer(eventData);
    return obj;
}

TiV8EventContainerFactory* TiV8EventContainerFactory::createEventContainerFactory(Handle<ObjectTemplate> temp)
{
    TiV8EventContainerFactory* obj = new TiV8EventContainerFactory;
    obj->globalTemplate_ = Persistent<ObjectTemplate>::New(temp);
    return obj;
}
