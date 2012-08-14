/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIIOSTREAMOBJECT_H_
#define TIIOSTREAMOBJECT_H_

#include "TiProxy.h"

/*
 * TiIOStreamObject
 *
 * Titanium interface that all stream types implement
 */
class TiIOStreamObject : public TiProxy
{
protected:
    TiIOStreamObject(const char* name);
    TiIOStreamObject();
    virtual ~TiIOStreamObject();

};

#endif /* TIIOSTREAMOBJECT_H_ */
