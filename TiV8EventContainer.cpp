/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiV8EventContainer.h"

#include "TiEvent.h"
#include "TiObject.h"

using namespace v8;
using namespace std;

TiV8EventContainer::TiV8EventContainer(Handle<Object> eventData)
{
    eventData_ = Persistent<Object>::New(eventData);
}

TiV8EventContainer::~TiV8EventContainer()
{
    if (!eventData_.IsEmpty())
    {
        eventData_.Dispose();
    }
}

void TiV8EventContainer::addListener(TiEvent* listener)
{
    TiInternalEventListener ctnListener(listener);
    int id = listener->getId();
    listeners_[id] = ctnListener;
}

void TiV8EventContainer::removeListener(int id)
{
    listeners_.erase(id);
}

void TiV8EventContainer::fireEvent()
{
    map<int, TiInternalEventListener>::const_iterator it;
    for (it = listeners_.begin(); it != listeners_.end(); it++)
    {
        it->second.getListener()->fire(&eventData_);
    }
}

void TiV8EventContainer::fireEvent(const TiObject* eventData) const
{
    map<int, TiInternalEventListener>::const_iterator it;
    Handle<Object> ed(eventData->getValue()->ToObject());
    for (it = listeners_.begin(); it != listeners_.end(); it++)
    {
        it->second.getListener()->fire(&ed);
    }
}

void TiV8EventContainer::setDataProperty(const char* propertyName, const char* value)
{
    HandleScope handleScope;
    eventData_->Set(String::New(propertyName), String::New(value));
}

void TiV8EventContainer::setDataProperty(const char* propertyName, int value)
{
    HandleScope handleScope;
    eventData_->Set(String::New(propertyName), Integer::New(value));
}

void TiV8EventContainer::setDataProperty(const char* propertyName, float value)
{
    HandleScope handleScope;
    eventData_->Set(String::New(propertyName), Number::New(value));
}

void TiV8EventContainer::setComplexDataProperty(const char* complexPropertyName, const char* propertyName, const char* value)
{
    HandleScope handleScope;
    Persistent<Object> complex =  Persistent<Object>::New(eventData_);
    complex->Set(String::New(propertyName), String::New(value));
    eventData_->Set(String::New(complexPropertyName), complex);
}

void TiV8EventContainer::setV8ValueProperty(const char* propertyName, Handle<Value> data)
{
    eventData_->Set(String::New(propertyName), data);
}

Handle<Value> TiV8EventContainer::getDataProperty(const char* propertyName)
{
    return eventData_->Get(v8::String::New(propertyName));
}

// TiInternalEventListener
TiV8EventContainer::TiInternalEventListener::TiInternalEventListener()
{
    listener_ = NULL;
}

TiV8EventContainer::TiInternalEventListener::TiInternalEventListener(const TiInternalEventListener& listener)
{
    listener_ = listener.listener_;
    if (listener_ != NULL)
    {
        listener_->addRef();
    }
}

TiV8EventContainer::TiInternalEventListener::TiInternalEventListener(TiEvent* listener)
{
    listener_ = listener;
    if (listener_ != NULL)
    {
        listener_->addRef();
    }
}

TiV8EventContainer::TiInternalEventListener::~TiInternalEventListener()
{
    if (listener_ != NULL)
    {
        listener_->release();
        listener_ = NULL;
    }
}

const TiV8EventContainer::TiInternalEventListener& TiV8EventContainer::TiInternalEventListener::operator =
(const TiV8EventContainer::TiInternalEventListener& listener)
{
    if (listener.listener_ != NULL)
    {
        listener.listener_->addRef();
    }
    if (listener_ != NULL)
    {
        listener_->release();
    }
    listener_ = listener.listener_;
    return (*this);
}

TiEvent* TiV8EventContainer::TiInternalEventListener::operator ->() const
{
    return listener_;
}

TiEvent* TiV8EventContainer::TiInternalEventListener::getListener() const
{
    return listener_;
}
