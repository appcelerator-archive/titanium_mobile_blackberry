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
 * TiPlatformObject
 *
 * Titanium.Platform namespace
 */
class TiPlatformObject : public TiObject
{
public:
    static void addObjectToParent(TiObject* parent);
    void setTiPlatformMappingProperties(const TiProperty* props, int propertyCount);
protected:
    virtual ~TiPlatformObject();
    virtual void onCreateStaticMembers();

private:
    static Handle<Value> _valueGetter(int propertyNumber, void* context);
    Handle<Value> getPropertyValue(int propertyNumber);
    explicit TiPlatformObject();
    TiPlatformObject(const TiPlatformObject&);
    TiPlatformObject& operator=(const TiPlatformObject&);
};


#endif /* TIPLATFORMOBJECT_H_ */
