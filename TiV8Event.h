/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIV8EVENT_H_
#define TIV8EVENT_H_

#include "TiEvent.h"

#include <v8.h>

using namespace v8;

/*
 * TiV8Event
 *
 * V8 specific event subscriber
 *
 */

class TiV8Event : public TiEvent
{
public:
    static TiV8Event* createEvent(const char* eventName, Handle<Function> eventScript, Handle<Object> source);
    virtual void fire(void* fireDataObject);

protected:
    virtual ~TiV8Event();

private:
    TiV8Event();
    Persistent<Function> function_;
    //Persistent<Object> source_;
    Handle<Object> source_;
};

#endif /* TIV8EVENT_H_ */
