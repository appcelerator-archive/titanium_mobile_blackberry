/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIV8EVENTCONTAINER_H_
#define TIV8EVENTCONTAINER_H_

#include "TiEventContainer.h"
#include <v8.h>
#include <vector>

using namespace v8;
using namespace std;

class TiInternalEventListener;

/*
 * TiV8EventContainer
 *
 * V8 specific event container
 *
 */

class TiV8EventContainer : public TiEventContainer
{
public:
    TiV8EventContainer(Handle<Object> eventData);
    virtual ~TiV8EventContainer();
    virtual void addListener(TiEvent* listener);
    virtual void fireEvent();
    virtual void setDataProperty(const char* propertyName, const char* value);
    virtual void setDataProperty(const char* propertyName, int value);
    virtual void setDataProperty(const char* propertyName, float value);
    virtual void setComplexDataProperty(const char* complexPropertyName, const char* propertyName, const char* value);

private:
    Persistent<Object> eventData_;
    vector<TiInternalEventListener> listeners_;
};

/*
 * TiInternalEventListener
 *
 * Wrapper for scrope management and reference counting
 * for using the vector template class
 *
 */

class TiInternalEventListener
{
public:
    TiInternalEventListener();
    TiInternalEventListener(const TiInternalEventListener& listener);
    TiInternalEventListener(TiEvent* listener);
    ~TiInternalEventListener();
    const TiInternalEventListener& operator =(const TiInternalEventListener& listener);
    TiEvent* operator ->() const;
    TiEvent* getListener() const;

private:
    TiEvent* listener_;
};

#endif /* TIV8EVENTCONTAINER_H_ */
