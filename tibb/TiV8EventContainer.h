/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIV8EVENTCONTAINER_H_
#define TIV8EVENTCONTAINER_H_

#include "TiEventContainer.h"
#include <map>

#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <v8.h>
#pragma GCC diagnostic warning "-Wunused-parameter"


/*
 * TiV8EventContainer
 *
 * V8 specific event container
 *
 */

class TiV8EventContainer : public TiEventContainer
{
public:
    TiV8EventContainer(v8::Handle<v8::Object> eventData);
    virtual ~TiV8EventContainer();
    virtual void addListener(TiEvent* listener);
    virtual void removeListener(int id);
    virtual void fireEvent();
    virtual void fireEvent(const TiObject* eventData) const;
    virtual void setDataProperty(const char* propertyName, const char* value);
    virtual void setDataProperty(const char* propertyName, int value);
    virtual void setDataProperty(const char* propertyName, float value);
    virtual void setComplexDataProperty(const char* complexPropertyName, const char* propertyName, const char* value);
    virtual void setV8ValueProperty(const char* propertyName, v8::Handle<v8::Value> data);
    virtual v8::Handle<v8::Value> getV8ValueProperty(const char* propertyName);

private:

    /*
     * TiInternalEventListener
     *
     * Wrapper for scrope management and reference counting
     * for using the vector template class
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

    v8::Persistent<v8::Object> eventData_;
    std::map<int, TiInternalEventListener> listeners_;
};

#endif /* TIV8EVENTCONTAINER_H_ */
