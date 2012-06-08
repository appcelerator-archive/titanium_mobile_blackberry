/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIObject.h"
#include "TiGenericFunctionObject.h"
#include "TiCascadesApp.h"
#include "TiConstants.h"
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

    // Adding javascript constants from Ti.UI
    ADD_STATIC_TI_VALUE("TEXT_ALIGNMENT_LEFT", Number::New(Ti::UI::TEXT_ALIGNMENT_LEFT), this);
    ADD_STATIC_TI_VALUE("TEXT_ALIGNMENT_CENTER", Number::New(Ti::UI::TEXT_ALIGNMENT_CENTER), this);
    ADD_STATIC_TI_VALUE("TEXT_ALIGNMENT_RIGHT", Number::New(Ti::UI::TEXT_ALIGNMENT_RIGHT), this);
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

Handle<Value> TiUIObject::_createButton(void* userContext, TiObject* caller, const Arguments& args)
{
    return createControlHelper_(userContext, TiUIButton::createButton, args);
}

Handle<Value> TiUIObject::_createSlider(void* userContext, TiObject* caller, const Arguments& args)
{
    return createControlHelper_(userContext, TiUISlider::createSlider, args);
}

Handle<Value> TiUIObject::_createProgressBar(void* userContext, TiObject* caller, const Arguments& args)
{
    return createControlHelper_(userContext, TiUIProgressBar::createProgressBar, args);
}

Handle<Value> TiUIObject::_createTextField(void* userContext, TiObject* caller, const Arguments& args)
{
    return createControlHelper_(userContext, TiUITextField::createTextField, args);
    HandleScope handleScope;
}

Handle<Value> TiUIObject::_createImageView(void* userContext, TiObject* caller, const Arguments& args)
{
    return createControlHelper_(userContext, TiUIImageView::createImageView, args);
}

Handle<Value> TiUIObject::_createActivityIndicator(void* userContext, TiObject* caller, const Arguments& args)
{
    return createControlHelper_(userContext, TiUIActivityIndicator::createActivityIndicator, args);
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
