/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIPROXY_H_
#define TIPROXY_H_

#include "TiObject.h"

class TiProxy : public TiObject
{
public:
protected:
    TiProxy();
    TiProxy(const char* name);
    virtual ~TiProxy();
private:
    // Disable copy ctor & assignment operator
    TiProxy(const TiProxy& obj);
    TiProxy& operator=(const TiProxy& obj);
};

#endif /* TIPROXY_H_ */
