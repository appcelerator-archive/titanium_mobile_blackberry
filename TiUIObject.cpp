/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIObject.h"
#include "TiGenericFunctionObject.h"
#include "TiUtility.h"
#include "TiCascadesApp.h"
#include "TiUIWindow.h"
#include "TiUILabel.h"
#include <string.h>

TiUIObject::TiUIObject()
        : TiObject("UI")
{
    objectFactory_ = NULL;
    contentContainer_ = NULL;
}

TiUIObject::TiUIObject(NativeObjectFactory* objectFactory)
        : TiObject("UI")
{
    objectFactory_ = objectFactory;
    contentContainer_ = NULL;
}

TiUIObject::~TiUIObject()
{
}

void TiUIObject::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory)
{
    TiUIObject* obj = new TiUIObject(objectFactory);
    parent->addMember(obj);
    obj->release();
}

void TiUIObject::onCreateStaticMembers()
{
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createTabGroup", this, createTabGroup_);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createWindow", this, createWindow_);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createLabel", this, createLabel_);
}

Handle<Value> TiUIObject::createTabGroup_(void* userContext, TiObject* caller, const Arguments& args)
{
    return Undefined();
}

Handle<Value> TiUIObject::createWindow_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle < ObjectTemplate > global = getObjectTemplateFromJsObject(args.Holder());
    Handle < Object > result;
    result = global->NewInstance();
    TiUIWindow* wnd = TiUIWindow::createWindow(obj->objectFactory_, "");
    wnd->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local < Object > settingsObj = Local < Object > ::Cast(args[0]);
        wnd->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, wnd);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::createLabel_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle < ObjectTemplate > global = getObjectTemplateFromJsObject(args.Holder());
    Handle < Object > result;
    result = global->NewInstance();
    TiUILabel* label = TiUILabel::createLabel(obj->objectFactory_);
    label->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local < Object > settingsObj = Local < Object > ::Cast(args[0]);
        label->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, label);
    return handleScope.Close(result);
}
