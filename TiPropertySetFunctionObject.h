/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIPROPERTYSETFUNCTIONOBJECT_H_
#define TIPROPERTYSETFUNCTIONOBJECT_H_

#include "TiObject.h"

class TiPropertySetFunctionObject : public TiObject
{
public:
    static void addPropertySetter(TiObject* parent, TiObject* property, const char* setterName);
    virtual bool isFunction() const;
protected:
    virtual ~TiPropertySetFunctionObject();
    virtual Handle<Value> onFunctionCall(const Arguments& args);
private:
    TiPropertySetFunctionObject(const char* name);
    TiObject* property_;
};

#endif /* TIPROPERTYSETFUNCTIONOBJECT_H_ */
