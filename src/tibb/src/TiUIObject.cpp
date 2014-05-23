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
#include "TiUIClipboardObject.h"
#include "TiUIPicker.h"
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

    TiGenericFunctionObject::addGenericFunctionToParent(this, "createPicker", this, _createPicker);

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


Handle<Value> TiUIObject::_createPicker(void* userContext, TiObject*, const Arguments& args)
{
    return _createControlHelper(userContext, (CREATEOBJECTCALLBACK)(TiUIPicker::createPicker), args);
}
