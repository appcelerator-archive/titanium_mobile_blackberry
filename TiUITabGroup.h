/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUITABGROUP_H_
#define TIUITABGROUP_H_

#include "TiUIBase.h"

/*
 * TiUITabGroup
 *
 * Represents a Titanium tab control object
 *
 * This object can be created by:
 * Titanium.UI.createTabGroup({...});
 */

class TiUITabGroup : public TiUIBase
{
public:
    static TiUIBase* createTabGroup(NativeObjectFactory* objectFactory);

protected:
    virtual ~TiUITabGroup();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();

private:
    static Handle<Value> open_(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> addTab_(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> setActiveTab_(void* userContext, TiObject* caller, const Arguments& args);

    TiUITabGroup();
    //This class is neither copy-constructible nor assignable
    TiUITabGroup(const TiUITabGroup& obj);
    TiUITabGroup& operator=(const TiUITabGroup& obj);
};

#endif /* TIUITABGROUP_H_ */
