/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIPROPERTYSETGETOBJECT_H_
#define TIPROPERTYSETGETOBJECT_H_

#include "TiObject.h"

typedef void(*SET_PROPERTY_CALLBACK)(void*, Handle<Value>);
typedef Handle<Value>(*GET_PROPERTY_CALLBACK)(void*);


class TiPropertySetGetObject : public TiObject
{
public:
    static void createProperty(TiObject* parent, const char* name, void* context,
    		SET_PROPERTY_CALLBACK scb, GET_PROPERTY_CALLBACK gcb);

    virtual VALUE_MODIFY setValue(Handle<Value> value);
    virtual Handle<Value> getValue() const;

protected:
    virtual ~TiPropertySetGetObject();
    virtual VALUE_MODIFY onValueChange(Handle<Value> oldValue, Handle<Value> newValue);

private:
    TiPropertySetGetObject(const char* propertyName);
    /* Not copiable; Not assignable */
    TiPropertySetGetObject(const TiPropertySetGetObject&);
    const TiPropertySetGetObject& operator = (const TiPropertySetGetObject&);

    void* context_;
    SET_PROPERTY_CALLBACK setCallback_;
    GET_PROPERTY_CALLBACK getCallback_;

};

#endif /* TIPROPERTYSETGETOBJECT_H_ */
