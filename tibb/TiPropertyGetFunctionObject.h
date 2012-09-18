/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIPROPERTYGETFUNCTIONOBJECT_H_
#define TIPROPERTYGETFUNCTIONOBJECT_H_

#include "TiObject.h"

/*
 * TiPropertyGetFunctionObject
 *
 * Represents getter methods for Titanium properties.
 *
 */

class TiPropertyGetFunctionObject : public TiObject
{
public:
    static void addPropertyGetter(TiObject* parent, TiObject* property, const char* getterName);
    virtual bool isFunction() const;

protected:
    virtual ~TiPropertyGetFunctionObject();
    virtual Handle<Value> onFunctionCall(const Arguments& args);

private:
    TiPropertyGetFunctionObject(const char* name);
    TiObject* property_;
};

#endif /* TIPROPERTYGETFUNCTIONOBJECT_H_ */
