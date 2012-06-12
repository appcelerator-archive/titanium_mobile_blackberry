/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIPROPERTYMAPOBJECT_H_
#define TIPROPERTYMAPOBJECT_H_

#include "TiObject.h"

class TiUIBase;
class NativeObject;

typedef VALUE_MODIFY(*MODIFY_VALUE_CALLBACK)(int, TiObject*, void*);

/*
 * TiPropertyMapObject
 *
 * Generic representation of Titanium properties
 *
 */

class TiPropertyMapObject : public TiObject
{
public:
    static TiPropertyMapObject* addProperty(TiUIBase* parent, const char* name, int propertyNumber,
                                            MODIFY_VALUE_CALLBACK cb, void* context);

protected:
    virtual ~TiPropertyMapObject();
    virtual VALUE_MODIFY onValueChange(Handle<Value> oldValue, Handle<Value> newValue);
    virtual Handle<Value> getValue() const;
private:
    TiPropertyMapObject(const char* name);
    int propertyNumber_;
    MODIFY_VALUE_CALLBACK callback_;
    void* context_;
    NativeObject* nativeObject_;
    TiUIBase* parentObject_;

};

#endif /* TIPROPERTYMAPOBJECT_H_ */
