/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#include "NativeTimeoutHandler.h"
#include "TiV8Event.h"
#include <QtCore/qtimer.h>

int NativeTimeoutHandler::idGenerator = 0;

NativeTimeoutHandler::NativeTimeoutHandler(Handle<Number> number, Handle<Function> eventFunction, bool interval)
{
    Handle<Object> source;
    event_ = TiV8Event::createEvent("", eventFunction, source);
    event_->setId(generateId());

    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(onEventFired()));
    if (!interval)
    {
        timer_->setSingleShot(true);
    }
    timer_->start((int)number->Value());
}

void NativeTimeoutHandler::clearTimeout()
{
    if (timer_ != NULL)
    {
        timer_->stop();
    }
}

void NativeTimeoutHandler::onEventFired()
{
    if (event_ != NULL)
    {
        event_->fire();
    }
}

int NativeTimeoutHandler::getId()
{
    if (event_ != NULL)
    {
        return event_->getId();
    }
    return -1;
}

int NativeTimeoutHandler::generateId()
{
    if (idGenerator < 1)
    {
        //check against overflow and start from 1
        idGenerator = 1;
    }
    else
    {
        ++idGenerator;
    }
    return idGenerator;
}

NativeTimeoutHandler::~NativeTimeoutHandler()
{
    delete timer_;
    delete event_;
}
