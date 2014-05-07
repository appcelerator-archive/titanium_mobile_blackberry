/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIObject.h"

#include "KeyboardType.h"
#include "Scene.h"
#include "TiCascadesApp.h"
#include "TiConstants.h"
#include "TiGenericFunctionObject.h"
#include "TiOrientation.h"
#include "TiUIActivityIndicator.h"
#include "TiUIClipboardObject.h"
#include "TiUIImageView.h"
#include "TiUILabel.h"
#include "TiUIOptionDialog.h"
#include "TiUIPicker.h"
#include "TiUIProgressBar.h"
#include "TiUISlider.h"
#include "TiUIScrollView.h"
#include "TiUISwitch.h"
#include "TiUITextField.h"
#include "TiUITextArea.h"
#include "TiUIAnimation.h"
#include "TiUIEmailDialog.h"
#include "TiUINavigationGroup.h"
#include "TiUIImageButton.h"
#include <string.h>

using namespace titanium;

TiUIObject::TiUIObject()
    : TiProxy("UI")
{
    objectFactory_ = NULL;
    contentContainer_ = NULL;
}

TiUIObject::TiUIObject(NativeObjectFactory* objectFactory)
    : TiProxy("UI")
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
    obj->setAttachedObject(parent);
    obj->release();
}

void TiUIObject::onCreateStaticMembers()
{
    HandleScope scope;

    TiProxy::onCreateStaticMembers();

    TiGenericFunctionObject::addGenericFunctionToParent(this, "createLabel", this, _createLabel);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createImageButton", this, _createImageButton);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createSlider", this, _createSlider);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createProgressBar", this, _createProgressBar);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createTextField", this, _createTextField);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createTextArea", this, _createTextArea);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createImageView", this, _createImageView);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createEmailDialog", this, _createEmailDialog);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createActivityIndicator", this, _createActivityIndicator);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createSwitch", this, _createSwitch);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createOptionDialog", this, _createOptionDialog);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createPicker", this, _createPicker);
//    TiGenericFunctionObject::addGenericFunctionToParent(this, "createView", this, _createView);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createScrollView", this, _createScrollView);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setBackgroundColor", this, _setBackgroundColor);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createAnimation", this, _createAnimation);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "createNavigationGroup", this, _createNavigationGroup);

    // Adding javascript constants from Ti.UI
    ADD_STATIC_TI_VALUE("TEXT_ALIGNMENT_LEFT", Number::New(Ti::UI::TEXT_ALIGNMENT_LEFT), this);
    ADD_STATIC_TI_VALUE("TEXT_ALIGNMENT_CENTER", Number::New(Ti::UI::TEXT_ALIGNMENT_CENTER), this);
    ADD_STATIC_TI_VALUE("TEXT_ALIGNMENT_RIGHT", Number::New(Ti::UI::TEXT_ALIGNMENT_RIGHT), this);
    ADD_STATIC_TI_VALUE("PICKER_TYPE_PLAIN", Number::New(Ti::UI::PICKER_TYPE_PLAIN), this);
    ADD_STATIC_TI_VALUE("PICKER_TYPE_DATE", Number::New(Ti::UI::PICKER_TYPE_DATE), this);
    ADD_STATIC_TI_VALUE("PICKER_TYPE_TIME", Number::New(Ti::UI::PICKER_TYPE_TIME), this);
    ADD_STATIC_TI_VALUE("PICKER_TYPE_DATE_AND_TIME", Number::New(Ti::UI::PICKER_TYPE_DATE_AND_TIME), this);
    ADD_STATIC_TI_VALUE("PICKER_TYPE_COUNT_DOWN_TIMER", Number::New(Ti::UI::PICKER_TYPE_COUNT_DOWN_TIMER), this);
    ADD_STATIC_TI_VALUE("FILL", String::NewSymbol("UI.FILL"), this);
    ADD_STATIC_TI_VALUE("SIZE", String::NewSymbol("UI.SIZE"), this);
    ADD_STATIC_TI_VALUE("LANDSCAPE_LEFT", Integer::New(Orientation::LANDSCAPE_LEFT), this);
    ADD_STATIC_TI_VALUE("LANDSCAPE_RIGHT", Integer::New(Orientation::LANDSCAPE_RIGHT), this);
    ADD_STATIC_TI_VALUE("PORTRAIT", Integer::New(Orientation::PORTRAIT), this);
    ADD_STATIC_TI_VALUE("UPSIDE_PORTRAIT", Integer::New(Orientation::UPSIDE_PORTRAIT), this);
    ADD_STATIC_TI_VALUE("FACE_UP", Integer::New(Orientation::FACE_UP), this);
    ADD_STATIC_TI_VALUE("FACE_DOWN", Integer::New(Orientation::FACE_DOWN), this);
    ADD_STATIC_TI_VALUE("KEYBOARD_DEFAULT", Integer::New(KeyboardType::DEFAULT), this);
    ADD_STATIC_TI_VALUE("KEYBOARD_ASCII", Integer::New(KeyboardType::ASCII), this);
    ADD_STATIC_TI_VALUE("KEYBOARD_EMAIL", Integer::New(KeyboardType::EMAIL), this);
    ADD_STATIC_TI_VALUE("KEYBOARD_NAMEPHONE_PAD", Integer::New(KeyboardType::NAMEPHONE_PAD), this);
    ADD_STATIC_TI_VALUE("KEYBOARD_NUMBERS_PUNCTUATION", Integer::New(KeyboardType::NUMBERS_PUNCTUATION), this);
    ADD_STATIC_TI_VALUE("KEYBOARD_PHONE_PAD", Integer::New(KeyboardType::PHONE_PAD), this);
    ADD_STATIC_TI_VALUE("KEYBOARD_URL", Integer::New(KeyboardType::URL), this);

    TiUIClipboardObject::addObjectToParent(this, objectFactory_);
}

Handle<Value> TiUIObject::_createControlHelper(void* userContext, CREATEOBJECTCALLBACK createCallback, const Arguments& args)
{
    HandleScope handleScope;
    TiUIObject* obj = (TiUIObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result;
    result = global->NewInstance();
    TiProxy* newControl = (createCallback)(obj->objectFactory_);
    newControl->setAttachedObject(obj);
    newControl->setValue(result);
    newControl->makeWeak();
    if (args.Length() > 0)
    {
    	newControl->applyProperties(args[0]);
    }
    setTiObjectToJsObject(result, newControl);
    return handleScope.Close(result);
}

Handle<Value> TiUIObject::_createLabel(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUILabel::createLabel, args);
}

Handle<Value> TiUIObject::_createImageButton(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUIImageButton::createButton, args);
}

Handle<Value> TiUIObject::_createSlider(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUISlider::createSlider, args);
}

Handle<Value> TiUIObject::_createEmailDialog(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)(TiUIEmailDialog::createEmailDialog), args);
}

Handle<Value> TiUIObject::_createProgressBar(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUIProgressBar::createProgressBar, args);
}

Handle<Value> TiUIObject::_createTextField(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUITextField::createTextField, args);
}

Handle<Value> TiUIObject::_createTextArea(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUITextArea::createTextArea, args);
}

Handle<Value> TiUIObject::_createImageView(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUIImageView::createImageView, args);
}

Handle<Value> TiUIObject::_createActivityIndicator(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)TiUIActivityIndicator::createActivityIndicator, args);
}

Handle<Value> TiUIObject::_createOptionDialog(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)(TiUIOptionDialog::createOptionDialog), args);
}

Handle<Value> TiUIObject::_createSwitch(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)(TiUISwitch::createSwitch), args);
}

Handle<Value> TiUIObject::_createPicker(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)(TiUIPicker::createPicker), args);
}

Handle<Value> TiUIObject::_createView(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)(TiUIBase::createView), args);
}

Handle<Value> TiUIObject::_createScrollView(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)(TiUIScrollView::createScrollView), args);
}

Handle<Value> TiUIObject::_createAnimation(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)(TiUIAnimation::createAnimation), args);
}

Handle<Value> TiUIObject::_createNavigationGroup(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)(TiUINavigationGroup::createProxy), args);
}

Handle<Value> TiUIObject::_setBackgroundColor(void* userContext, TiObject* caller, const Arguments& args)
{
    // Not currently implemented.
    return Undefined();
}
