/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIObject.h"

#include "TiCascadesApp.h"
#include "TiConstants.h"
#include "TiGenericFunctionObject.h"
#include "TiUIActivityIndicator.h"
#include "TiUIAlertDialog.h"
#include "TiUIButton.h"
#include "TiUIImageView.h"
#include "TiUILabel.h"
#include "TiUIOptionDialog.h"
#include "TiUIPicker.h"
#include "TiUIProgressBar.h"
#include "TiUISlider.h"
#include "TiUISwitch.h"
#include "TiUITab.h"
#include "TiUITabGroup.h"
#include "TiUITableView.h"
#include "TiUITextField.h"
#include "TiUIWindow.h"

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
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createTab", this, _createTab);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createPicker", this, _createPicker);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createAlertDialog", this, _createAlertDialog);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createView", this, _createView);

    // Adding javascript constants from Ti.UI
    ADD_STATIC_TI_VALUE("TEXT_ALIGNMENT_LEFT", Number::New(Ti::UI::TEXT_ALIGNMENT_LEFT), this);
    ADD_STATIC_TI_VALUE("TEXT_ALIGNMENT_CENTER", Number::New(Ti::UI::TEXT_ALIGNMENT_CENTER), this);
    ADD_STATIC_TI_VALUE("TEXT_ALIGNMENT_RIGHT", Number::New(Ti::UI::TEXT_ALIGNMENT_RIGHT), this);
    ADD_STATIC_TI_VALUE("PICKER_TYPE_PLAIN", Number::New(Ti::UI::PICKER_TYPE_PLAIN), this);
    ADD_STATIC_TI_VALUE("PICKER_TYPE_DATE", Number::New(Ti::UI::PICKER_TYPE_DATE), this);
    ADD_STATIC_TI_VALUE("PICKER_TYPE_TIME", Number::New(Ti::UI::PICKER_TYPE_TIME), this);
    ADD_STATIC_TI_VALUE("PICKER_TYPE_DATE_AND_TIME", Number::New(Ti::UI::PICKER_TYPE_DATE_AND_TIME), this);
    ADD_STATIC_TI_VALUE("PICKER_TYPE_COUNT_DOWN_TIMER", Number::New(Ti::UI::PICKER_TYPE_COUNT_DOWN_TIMER), this);
}

Handle<Value> TiUIObject::_createControlHelper(void* userContext, CREATEOBJECTCALLBACK createCallback, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result;
    result = global->NewInstance();
    TiProxy* newControl = (createCallback)(obj->objectFactory_);
    newControl->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        newControl->setParametersFromObject(newControl, settingsObj);
    }
    setTiObjectToJsObject(result, newControl);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::_createWindow(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUIWindow::createWindow, args);
}

Handle<Value> TiUIObject::_createLabel(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUILabel::createLabel, args);
}

Handle<Value> TiUIObject::_createButton(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUIButton::createButton, args);
}

Handle<Value> TiUIObject::_createSlider(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUISlider::createSlider, args);
}

Handle<Value> TiUIObject::_createProgressBar(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUIProgressBar::createProgressBar, args);
}

Handle<Value> TiUIObject::_createTextField(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUITextField::createTextField, args);
}

Handle<Value> TiUIObject::_createImageView(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUIImageView::createImageView, args);
}

Handle<Value> TiUIObject::_createActivityIndicator(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUIActivityIndicator::createActivityIndicator, args);
}

Handle<Value> TiUIObject::_createTab(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUITab::createTab, args);
}

Handle<Value> TiUIObject::_createTabGroup(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUITabGroup::createTabGroup, args);
}

Handle<Value> TiUIObject::_createOptionDialog(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)(TiUIOptionDialog::createOptionDialog), args);
}

Handle<Value> TiUIObject::_createTableView(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)(TiUITableView::createTableView), args);
}

Handle<Value> TiUIObject::_createSwitch(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)(TiUISwitch::createSwitch), args);
}

Handle<Value> TiUIObject::_createPicker(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)(TiUIPicker::createPicker), args);
}

Handle<Value> TiUIObject::_createAlertDialog(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)(TiUIAlertDialog::createAlertDialog), args);
}

Handle<Value> TiUIObject::_createView(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)(TiUIBase::createView), args);
}
