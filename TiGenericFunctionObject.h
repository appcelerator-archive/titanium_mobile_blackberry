/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIGENERICFUNCTIONOBJECT_H_
#define TIGENERICFUNCTIONOBJECT_H_

#include "TiObject.h"

typedef Handle<Value> (*GENERIC_FUNCTION_CALLBACK)(void*, TiObject*, const Arguments&);

class TiGenericFunctionObject : public TiObject
{
public:
    static void addGenericFunctionToParent(TiObject* parent, const char* name, void* userContext,
                                           GENERIC_FUNCTION_CALLBACK callback);
    virtual bool isFunction() const;
protected:
    virtual ~TiGenericFunctionObject();
    virtual Handle<Value> onFunctionCall(const Arguments& args);
private:
    TiGenericFunctionObject();
    TiGenericFunctionObject(const char* name);
    void* context_;
    GENERIC_FUNCTION_CALLBACK callback_;
};

#endif /* TIGENERICFUNCTIONOBJECT_H_ */
