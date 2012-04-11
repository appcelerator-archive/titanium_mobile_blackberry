/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIAPIOBJECT_H_
#define TIAPIOBJECT_H_

#include "TiObject.h"

class TiAPIObject : public TiObject
{
public:
    static void addObjectToParent(TiObject* parent);
protected:
    virtual ~TiAPIObject();
    virtual void onCreateStaticMembers();
private:
    TiAPIObject();
    static Handle<Value> debug_(void* userContext, TiObject* caller, const Arguments& args);
};

#endif /* TIAPIOBJECT_H_ */
