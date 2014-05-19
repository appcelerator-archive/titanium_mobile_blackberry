/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiBase.h"

TiBase::TiBase()
{
    refCount_ = 1;
}

TiBase::~TiBase()
{
}

void TiBase::addRef()
{
    // TODO: protect this in a multi-threaded environment
    refCount_++;
}

void TiBase::release()
{
    // TODO: protect this in a multi-threaded environment
    if ((--refCount_) < 1)
    {
        delete this;
    }
}
