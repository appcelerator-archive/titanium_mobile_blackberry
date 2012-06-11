/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIDATEOBJECT_H_
#define TIDATEOBJECT_H_

#include "TiObject.h"

/*
 * TiDateObject
 */
class TiDateObject : public TiObject
{
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);

protected:
    virtual ~TiDateObject();
    virtual void onCreateStaticMembers();
    virtual bool canAddMembers() const;

private:
    explicit TiDateObject();
    explicit TiDateObject(NativeObjectFactory* objectFactory);

    /* Not copiable; Not assignable */
    TiDateObject(const TiDateObject& date);
    TiDateObject& operator=(const TiDateObject& date);

    NativeObjectFactory* objectFactory_;
};

#endif /* TIDATEOBJECT_H_ */
