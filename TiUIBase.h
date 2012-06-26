/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIBASE_H_
#define TIUIBASE_H_

#include "TiObject.h"
#include <vector>

using namespace std;

class TiCascadesApp;

/*
 * TiUIBase
 *
 * Titanium base class for all UI objects such as windows, labels, buttons, etc...
 */
class TiUIBase : public TiObject
{
public:
    virtual void setParametersFromObject(Local<Object> obj);
    virtual bool isUIObject() const;
    virtual void setTiMappingProperties(const TiProperty* props, int propertyCount);

protected:
    TiUIBase(const char* name);
    TiUIBase();
    virtual ~TiUIBase();
    virtual bool canAddMembers() const;
    virtual void onCreateStaticMembers();
    virtual void onAddEventListener(const char* eventName, Handle<Function> eventFunction);
    virtual void onRemoveEventListener(const char* eventName, Handle<Function> eventFunction);
    Persistent<Object> createConfig_;
    vector<ObjectEntry> childControls_;

private:
    static VALUE_MODIFY _valueModify(int propertyNumber, TiObject* value, void* context);
    static Handle<Value> _add(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _addEventListener(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _hide(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _removeEventListener(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _getChildren(void* userContext);
};

#endif /* TIUIBASE_H_ */
