/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiEvent.h"

TiEvent::TiEvent()
{
    id_ = 0;
}

TiEvent::~TiEvent()
{
}

void TiEvent::setId(int id)
{
    id_ = id;
}

int TiEvent::getId() const
{
    return id_;
}
