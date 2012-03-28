/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIROOTOBJECT_H_
#define TIROOTOBJECT_H_

#include "TiObject.h"

class TiCascadesApp;

using namespace std;

struct FUNCTION_ENTRY;

class TiRootObject : public TiObject
{
public:
    static TiRootObject* createRootObject();
    int executeScript(TiCascadesApp& app,const char* javaScript);
protected:
    virtual ~TiRootObject();
    virtual void onCreateStaticMembers();
	virtual Handle<ObjectTemplate>* getGlobalTemplate();
private:
    TiRootObject();

    Persistent<Context> context_;
    Handle<ObjectTemplate> globalTemplate_;
};

#endif /* TIROOTOBJECT_H_ */
