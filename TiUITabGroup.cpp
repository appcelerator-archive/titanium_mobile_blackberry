/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITabGroup.h"
#include "TiGenericFunctionObject.h"
#include "NativeMessageStrings.h"

TiUITabGroup::TiUITabGroup()
    : TiUIBase("")
{
}

TiUITabGroup::~TiUITabGroup()
{
}

TiUITabGroup* TiUITabGroup::createTabGroup(NativeObjectFactory* objectFactory)
{
    TiUITabGroup* obj = new TiUITabGroup;
    obj->setNativeObjectFactory(objectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUITabGroup::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "open", this, _open);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "addTab", this, _addTab);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setActiveTab", this, _setActiveTab);
}

void TiUITabGroup::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_TABGROUP, this);
        setNativeObject(obj);
        obj->release();
    }
}

Handle<Value> TiUITabGroup::_open(void* userContext, TiObject*, const Arguments&)
{
    HandleScope handleScope;
    TiUITabGroup* obj = (TiUITabGroup*) userContext;
    NativeObject* no = obj->getNativeObject();
    no->completeInitialization();
    no->open();
    no->release();
    return Undefined();
}

Handle<Value> TiUITabGroup::_addTab(void* userContext, TiObject* caller, const Arguments& args)
{
    TiUIBase::_add(userContext, caller, args);
    return Undefined();
}

Handle<Value> TiUITabGroup::_setActiveTab(void* userContext, TiObject*, const Arguments& args)
{
    HandleScope handleScope;
    TiUITabGroup* obj = (TiUITabGroup*) userContext;
    NativeObject* no = obj->getNativeObject();
    if ((args.Length() > 0) && args[0]->IsNumber())
    {
        Local<Integer> index = args[0]->ToInteger();
        no->setActiveTab(index->Value());
    }
    else
    {
        HandleScope handleScope;
        if ((args.Length() > 0) && (args[0]->IsObject()))
        {
            TiObject* addObj = getTiObjectFromJsObject(args[0]);
            if ((addObj == NULL) || (!addObj->isUIObject()))
            {
                return Undefined();
            }
            TiUIBase* uiObj = (TiUIBase*) addObj;
            NativeObject* childNO = uiObj->getNativeObject();
            no->setActiveTab(childNO);
            childNO->release();
        }
        else
        {
            ThrowException(String::New(Native::Msg::Expected_argument_of_type_object_or_external));
        }
    }
    no->release();
    return Undefined();
}
