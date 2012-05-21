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
#include "TiUISwitch.h"
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
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createSwitch", this, createSwitch_);
}

Handle<Value> TiUIObject::createTabGroup_(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: finish this
    return Undefined();
}

Handle<Value> TiUIObject::createWindow_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result;
    result = global->NewInstance();
    TiUIWindow* wnd = TiUIWindow::createWindow(obj->objectFactory_, "");
    wnd->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        wnd->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, wnd);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::createLabel_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result;
    result = global->NewInstance();
    TiUILabel* label = TiUILabel::createLabel(obj->objectFactory_);
    label->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        label->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, label);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::createButton_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result;
    result = global->NewInstance();
    TiUIButton* button = TiUIButton::createButton(obj->objectFactory_);
    button->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        button->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, button);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::createSlider_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result;
    result = global->NewInstance();
    TiUISlider* slider = TiUISlider::createSlider(obj->objectFactory_);
    slider->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        slider->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, slider);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::createProgressBar_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result;
    result = global->NewInstance();
    TiUIProgressBar* progressBar = TiUIProgressBar::createProgressBar(obj->objectFactory_);
    progressBar->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        progressBar->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, progressBar);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::createTextField_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle < ObjectTemplate > global = getObjectTemplateFromJsObject(args.Holder());
    Handle < Object > result;
    result = global->NewInstance();
    TiUITextField* textField = TiUITextField::createTextField(obj->objectFactory_);
    textField->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local < Object > settingsObj = Local < Object > ::Cast(args[0]);
        textField->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, textField);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::createImageView_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle < ObjectTemplate > global = getObjectTemplateFromJsObject(args.Holder());
    Handle < Object > result;
    result = global->NewInstance();
    TiUIImageView* imageView = TiUIImageView::createImageView(obj->objectFactory_);
    imageView->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local < Object > settingsObj = Local < Object > ::Cast(args[0]);
        imageView->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, imageView);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::createActivityIndicator_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle < ObjectTemplate > global = getObjectTemplateFromJsObject(args.Holder());
    Handle < Object > result;
    result = global->NewInstance();
    TiUIActivityIndicator* activityIndicator = TiUIActivityIndicator::createActivityIndicator(obj->objectFactory_);
    activityIndicator->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local < Object > settingsObj = Local < Object > ::Cast(args[0]);
        activityIndicator->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, activityIndicator);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::createSwitch_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result;
    result = global->NewInstance();
    TiUISwitch* switchObj = TiUISwitch::createSwitch(obj->objectFactory_);
    switchObj->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        switchObj->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, switchObj);
    return handleScope.Close(result);
}
