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
#include "TiUITableView.h"
#include "TiUISwitch.h"
#include "TiUIOptionDialog.h"
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
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createTableView", this, _createTableView);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createTabGroup", this, _createTabGroup);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createWindow", this, _createWindow);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createLabel", this, _createLabel);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createButton", this, _createButton);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createSlider", this, _createSlider);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createProgressBar", this, _createProgressBar);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createTextField", this, _createTextField);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createImageView", this, _createImageView);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createActivityIndicator", this, _createActivityIndicator);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createSwitch", this, _createSwitch);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createOptionDialog", this, _createOptionDialog);
}

Handle<Value> TiUIObject::_createTabGroup(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: finish this
    return Undefined();
}

Handle<Value> TiUIObject::_createWindow(void* userContext, TiObject* caller, const Arguments& args)
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

Handle<Value> TiUIObject::_createLabel(void* userContext, TiObject* caller, const Arguments& args)
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

Handle<Value> TiUIObject::_createButton(void* userContext, TiObject* caller, const Arguments& args)
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

Handle<Value> TiUIObject::_createSlider(void* userContext, TiObject* caller, const Arguments& args)
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

Handle<Value> TiUIObject::_createProgressBar(void* userContext, TiObject* caller, const Arguments& args)
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

Handle<Value> TiUIObject::_createTextField(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result;
    result = global->NewInstance();
    TiUITextField* textField = TiUITextField::createTextField(obj->objectFactory_);
    textField->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        textField->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, textField);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::_createImageView(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result;
    result = global->NewInstance();
    TiUIImageView* imageView = TiUIImageView::createImageView(obj->objectFactory_);
    imageView->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        imageView->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, imageView);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::_createActivityIndicator(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result;
    result = global->NewInstance();
    TiUIActivityIndicator* activityIndicator = TiUIActivityIndicator::createActivityIndicator(obj->objectFactory_);
    activityIndicator->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        activityIndicator->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, activityIndicator);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::_createOptionDialog(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result;
    result = global->NewInstance();
    TiUIOptionDialog* optionDialog = TiUIOptionDialog::createOptionDialog(obj->objectFactory_);
    optionDialog->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        optionDialog->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, optionDialog);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::_createTableView(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle < ObjectTemplate > global = getObjectTemplateFromJsObject(args.Holder());
    Handle < Object > result;
    result = global->NewInstance();
    TiUITableView* tableView = TiUITableView::createTableView(obj->objectFactory_);
    tableView->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local < Object > settingsObj = Local < Object > ::Cast(args[0]);
        tableView->setParametersFromObject(settingsObj);
    }
    setTiObjectToJsObject(result, tableView);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::_createSwitch(void* userContext, TiObject* caller, const Arguments& args)
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
