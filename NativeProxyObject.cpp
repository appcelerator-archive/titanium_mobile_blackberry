/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeProxyObject.h"
#include "TiEvent.h"

// NativeProxyObject

NativeProxyObject::NativeProxyObject()
{
}

NativeProxyObject::~NativeProxyObject()
{
}

int NativeProxyObject::fireEvent(const char* name, const TiObject* event) const
{
	QString qstr(name);
	if(!events_.contains(qstr))
	{
		return NativeObject::fireEvent(name,event);
	}
	EventPairSmartPtr ptr=events_[qstr];
	if(!ptr->isValid())
	{
		return NativeObject::fireEvent(name,event);
	}
    ptr->container->fireEvent(event);
    return NATIVE_ERROR_OK;
}

int NativeProxyObject::setEventHandler(const char* eventName, TiEvent* event)
{
    if (events_.contains(eventName))
    {
        event->setId(getNextEventId());
        events_[eventName]->container->addListener(event);
        return NATIVE_ERROR_OK;
    }
    return NativeObject::setEventHandler(eventName,event);
}

// EventPairSmartPtr
EventPairSmartPtr::EventPairSmartPtr():
		eventPtr_(NULL)
{
}

EventPairSmartPtr::EventPairSmartPtr(const EventPairSmartPtr& eventPtr)
{
	eventPtr_=eventPtr.eventPtr_;
	if (eventPtr_!=NULL)
	{
		eventPtr_->addRef();
	}
}

EventPairSmartPtr::EventPairSmartPtr(EventPair* eventPtr)
{
	eventPtr_=eventPtr;
	if(eventPtr_!=NULL)
	{
		eventPtr_->addRef();
	}
}

EventPairSmartPtr::EventPairSmartPtr(TiEventContainer* c, QObject* h)
{
	eventPtr_=new EventPair(c, h);
}

EventPairSmartPtr::~EventPairSmartPtr()
{
	if(eventPtr_!=NULL)
	{
		eventPtr_->release();
		eventPtr_=NULL;
	}
}

const EventPairSmartPtr& EventPairSmartPtr::operator = (const EventPairSmartPtr& eventPtr)
{
	if(eventPtr.eventPtr_!=NULL)
	{
		eventPtr.eventPtr_->addRef();
	}
	if(eventPtr_!=NULL)
	{
		eventPtr_->release();
	}
	eventPtr_=eventPtr.eventPtr_;
	return(*this);
}

EventPair* EventPairSmartPtr::operator -> () const
{
	return eventPtr_;
}
