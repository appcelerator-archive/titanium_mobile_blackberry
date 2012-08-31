/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeProxyObject.h"

#include "NativeLoggerObject.h"
#include "NativeMessageStrings.h"
#include "TiEvent.h"

const char* NativeProxyObject::tetACCEPTED = "accepted";
const char* NativeProxyObject::tetCHANGE = "change";
const char* NativeProxyObject::tetCLICK = "click";
const char* NativeProxyObject::tetCONNECTED = "connected";
const char* NativeProxyObject::tetERROR = "error";


NativeProxyObject::NativeProxyObject()
{
}

NativeProxyObject::~NativeProxyObject()
{
}

int NativeProxyObject::fireEvent(const char* name, const TiObject* event) const
{
    EventPairSmartPtr ep = events_.value(name);
    if (ep.get() != NULL && ep->isValid())
    {
        if (event != NULL)
        {
            ep->container->fireEvent(event);
        }
        else
        {
            ep->container->fireEvent();
        }
        return NATIVE_ERROR_OK;
    }
    N_WARNING(Native::Msg::Unsupported_event_name_ << name);
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeProxyObject::setEventHandler(const char* eventName, TiEvent* event)
{
    // TODO: support custom events
    if (events_.contains(eventName))
    {
        event->setId(getNextEventId());
        events_[eventName]->container->addListener(event);
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeProxyObject::removeEventHandler(const char* eventName, int eventId)
{
    if (events_.contains(eventName))
    {
        events_[eventName]->container->removeListener(eventId);
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeProxyObject::getNextEventId()
{
    static int s_nextEventId = 1;

    // Account for overflow.
    if (s_nextEventId < 1)
    {
        // This event id must start at 1 because 0 is reserved. Since
        // V8 will always cast a value of undefined to zero.
        s_nextEventId = 1;
    }
    return s_nextEventId++;
}


/* -- EventPairSmartPtr Implementation -- */
EventPairSmartPtr::EventPairSmartPtr():
    eventPtr_(NULL)
{
}

EventPairSmartPtr::EventPairSmartPtr(const EventPairSmartPtr& eventPtr)
{
    eventPtr_ = eventPtr.eventPtr_;
    if (eventPtr_ != NULL)
    {
        eventPtr_->addRef();
    }
}

EventPairSmartPtr::EventPairSmartPtr(EventPair* eventPtr)
{
    eventPtr_ = eventPtr;
    if (eventPtr_ != NULL)
    {
        eventPtr_->addRef();
    }
}

EventPairSmartPtr::EventPairSmartPtr(TiEventContainer* c, QObject* h)
{
    eventPtr_ = new EventPair(c, h);
}

EventPairSmartPtr::~EventPairSmartPtr()
{
    if (eventPtr_ != NULL)
    {
        eventPtr_->release();
        eventPtr_ = NULL;
    }
}

EventPairSmartPtr& EventPairSmartPtr::operator=(const EventPairSmartPtr& eventPtr)
{
    if (eventPtr.eventPtr_ != NULL)
    {
        eventPtr.eventPtr_->addRef();
    }
    if (eventPtr_ != NULL)
    {
        eventPtr_->release();
    }
    eventPtr_ = eventPtr.eventPtr_;
    return *this;
}

EventPair* EventPairSmartPtr::operator->() const
{
    return eventPtr_;
}

EventPair* EventPairSmartPtr::get() const
{
    return eventPtr_;
}
