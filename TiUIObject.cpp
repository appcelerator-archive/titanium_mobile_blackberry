/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIObject.h"
#include "TiGenericFunctionObject.h"
#include "TiCascadesApp.h"
#include "TiUIWindow.h"
#include "TiUILabel.h"
#include "TiUIButton.h"
#include "TiUISlider.h"
#include "TiUIProgressBar.h"
#include "TiUIImageView.h"
#include "TiUITextField.h"
#include "TiUIActivityIndicator.h"
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
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createButton", this, createButton_);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createSlider", this, createSlider_);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createProgressBar", this, createProgressBar_);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createTextField", this, createTextField_);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createImageView", this, createImageView_);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createActivityIndicator", this, createActivityIndicator_);
}

Handle<Value> TiUIObject::createControlHelper_(void* userContext, CREATEOBJECTCALLBACK createCallback, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result;
    result = global->NewInstance();
    TiUIBase* newControl = (createCallback)(obj->objectFactory_);
    newControl->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        newControl->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, newControl);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::createTabGroup_(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: finish this
    return Undefined();
}

Handle<Value> TiUIObject::createWindow_(void* userContext, TiObject* caller, const Arguments& args)
{
    return createControlHelper_(userContext, TiUIWindow::createWindow, args);
}

Handle<Value> TiUIObject::createLabel_(void* userContext, TiObject* caller, const Arguments& args)
{
    return createControlHelper_(userContext, TiUILabel::createLabel, args);
}

Handle<Value> TiUIObject::createButton_(void* userContext, TiObject* caller, const Arguments& args)
{
    return createControlHelper_(userContext, TiUIButton::createButton, args);
}

Handle<Value> TiUIObject::createSlider_(void* userContext, TiObject* caller, const Arguments& args)
{
    return createControlHelper_(userContext, TiUISlider::createSlider, args);
}

Handle<Value> TiUIObject::createProgressBar_(void* userContext, TiObject* caller, const Arguments& args)
{
    return createControlHelper_(userContext, TiUIProgressBar::createProgressBar, args);
}

Handle<Value> TiUIObject::createTextField_(void* userContext, TiObject* caller, const Arguments& args)
{
    return createControlHelper_(userContext, TiUITextField::createTextField, args);
}

Handle<Value> TiUIObject::createImageView_(void* userContext, TiObject* caller, const Arguments& args)
{
    return createControlHelper_(userContext, TiUIImageView::createImageView, args);
}

Handle<Value> TiUIObject::createActivityIndicator_(void* userContext, TiObject* caller, const Arguments& args)
{
    return createControlHelper_(userContext, TiUIActivityIndicator::createActivityIndicator, args);
}
