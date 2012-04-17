/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIEVENT_H_
#define TIEVENT_H_

#include "TiBase.h"

/*
 * TiEvent
 *
 * Abstract class the represents an event subscriber
 *
 */

class TiEvent : public TiBase
{
public:
    virtual void fire(void* fireDataObject)=0;

protected:
    virtual ~TiEvent();
    TiEvent();
};

#endif /* TIEVENT_H_ */
