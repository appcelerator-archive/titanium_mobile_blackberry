/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIOBJECT_H_
#define TIUIOBJECT_H_

#include "TiObject.h"

class TiUIObject : public TiObject
{
public:
	static void addObjectToParent(TiObject* parent);
protected:
    virtual ~TiUIObject();
    virtual void onCreateStaticMembers();
private:
    TiUIObject();
	static Handle<Value> setBackgroundColor_(void* userContext,TiObject* caller,const Arguments& args);
	static Handle<Value> createTabGroup_(void* userContext,TiObject* caller,const Arguments& args);
};

#endif /* TIUIOBJECT_H_ */
