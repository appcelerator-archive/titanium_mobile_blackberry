/*
 * TiBase.cpp
 *
 *  Created on: 2012-04-23
 *      Author: dcampbell
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
