/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIAPPOBJECT_H_
#define TIAPPOBJECT_H_

#include "TiObject.h"

/*
 * TiAppObject
 *
 * Object that represents name space: Titanium.App
 */

class TiAppObject : public TiObject
{
public:
    static void addObjectToParent(TiObject* parent);

protected:
    virtual ~TiAppObject();
    virtual void onCreateStaticMembers();

private:
    TiAppObject();
    TiAppObject(const TiAppObject&);
    TiAppObject& operator=(const TiAppObject&);
};

#endif /* TIAPPOBJECT_H_ */
