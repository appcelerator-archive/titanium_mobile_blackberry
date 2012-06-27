/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIPROPERTYGETOBJECT_H_
#define TIPROPERTYGETOBJECT_H_

#include "TiObject.h"

typedef Handle<Value>(*GET_PROPERTY_CALLBACK)(void*);

class TiPropertyGetObject : public TiObject
{
public:
    static TiObject* createGetProperty(TiObject* parent, const char* name, void* context,
                                       GET_PROPERTY_CALLBACK cb);
    virtual Handle<Value> getValue() const;
protected:
    virtual ~TiPropertyGetObject();
    virtual VALUE_MODIFY onValueChange(Handle<Value> oldValue, Handle<Value> newValue);

private:
    TiPropertyGetObject(const char* propertyName);
    /* Not copiable; Not assignable */
    TiPropertyGetObject(const TiPropertyGetObject&);
    const TiPropertyGetObject& operator = (const TiPropertyGetObject&);

    void* context_;
    GET_PROPERTY_CALLBACK getCallback_;
};

#endif /* TIPROPERTYGETOBJECT_H_ */
