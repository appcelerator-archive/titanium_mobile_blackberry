/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIPROPERTYMAPOBJECT_H_
#define TIPROPERTYMAPOBJECT_H_

#include "TiObject.h"

typedef VALUE_MODIFY(*MODIFY_VALUE_CALLBACK)(int, TiObject*, void*);
typedef Handle<Value>(*GET_PROPERTY_VALUE_CALLBACK)(int, void*);

/*
 * TiPropertyMapObject
 *
 * Generic representation of Titanium properties
 *
 */

class TiPropertyMapObject : public TiObject
{
public:
    static TiPropertyMapObject* addProperty(TiObject* parent, const char* name, int propertyNumber,
                                            MODIFY_VALUE_CALLBACK cb, void* context);
    static TiPropertyMapObject* addProperty(TiObject* parent, const char* name, int propertyNumber,
                                            GET_PROPERTY_VALUE_CALLBACK cb, void* context);
    virtual Handle<Value> getValue() const;
protected:
    virtual ~TiPropertyMapObject();
    virtual VALUE_MODIFY onValueChange(Handle<Value> oldValue, Handle<Value> newValue);

private:
    TiPropertyMapObject(const char* name);
    int propertyNumber_;
    MODIFY_VALUE_CALLBACK callback_;
    GET_PROPERTY_VALUE_CALLBACK getCallback_;
    void* context_;

};

#endif /* TIPROPERTYMAPOBJECT_H_ */
