/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIBASE_H_
#define TIUIBASE_H_

#include "TiObject.h"
#include "TiCascadesApp.h"

#ifndef _WIN32
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/Control>
#endif

class TiCascadesApp;

class TiUIBase : public TiObject
{
public:
	virtual void setParametersFromObject(Local<Object> obj);
protected:
    TiUIBase(TiCascadesApp& app,const char* name);
    TiUIBase();
    virtual ~TiUIBase();
    virtual TiCascadesApp* getCascadesApp() const;
    virtual bool canAddMembers() const;
    virtual UIHANDLE getContainerHandle() const;
    virtual void setContainerHandle(UIHANDLE container);
    virtual void onSetProperty(const char* color,Local<Value> value);
    virtual void onSetBackgroundColor(const char* color);
	Persistent<Object> createConfig_;
private:
    static Handle<Value> setBackgroundColor_(void* userContext,
                                             TiObject* caller,
                                             const Arguments& args);

    TiCascadesApp* cascadesApp_;
    UIHANDLE container_;
};

#endif /* TIUIBASE_H_ */
