/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIPLATFORMOBJECT_H_
#define TIPLATFORMOBJECT_H_

#include "TiObject.h"

/*
 * TiPlatform
 *
 * Titanium.Platform namespace
 */
class TiPlatform : public TiObject
{
public:
    static void addObjectToParent(TiObject* parent);
    void setTiPlatformMappingProperties(const TiProperty* props, int propertyCount);
protected:
    virtual ~TiPlatform();
    virtual void onCreateStaticMembers();

private:
    static Handle<Value> _valueGetter(int propertyNumber, void* context);
    Handle<Value> getPropertyValue(int propertyNumber);
    explicit TiPlatform();
    TiPlatform(const TiPlatform&);
    TiPlatform& operator=(const TiPlatform&);
};


#endif /* TIPLATFORMOBJECT_H_ */
