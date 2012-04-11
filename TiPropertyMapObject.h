/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIPROPERTYMAPOBJECT_H_
#define TIPROPERTYMAPOBJECT_H_

#include "TiObject.h"

typedef VALUE_MODIFY (*MODIFY_VALUE_CALLBACK)(int, const char*, void*);

class TiPropertyMapObject : public TiObject
{
public:
    static TiPropertyMapObject* addProperty(TiObject* parent, const char* name, int propertyNumber,
                                            MODIFY_VALUE_CALLBACK cb, void* context);
protected:
    virtual ~TiPropertyMapObject();
    virtual VALUE_MODIFY onValueChange(Handle<Value> oldValue, Handle<Value> newValue);
private:
    TiPropertyMapObject(const char* name);
    int propertyNumber_;
    MODIFY_VALUE_CALLBACK callback_;
    void* context_;

};

#endif /* TIPROPERTYMAPOBJECT_H_ */
