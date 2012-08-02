/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeMessageStrings.h"
#include "TiCascadesApp.h"
#include "TiGenericFunctionObject.h"
#include "TiUITab.h"

TiUITab::TiUITab()
    : TiUIBase("")
{
}

TiUITab::~TiUITab()
{
}

TiUITab* TiUITab::createTab(NativeObjectFactory* nativeObjectFactory)
{
    TiUITab* obj = new TiUITab;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUITab::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "open", this, open_);
}

void TiUITab::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_TAB);
        setNativeObject(obj);
        obj->release();
    }
}

Handle<Value> TiUITab::open_(void* userContext, TiObject*, const Arguments& args)
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
        NativeObject* win = uiObj->getNativeObject();
        TiUITab* obj = (TiUITab*) userContext;
        NativeObject* tab = obj->getNativeObject();
        tab->openWindowOnTab(win);
        tab->release();
        win->release();
    }
    else
    {
        return ThrowException(String::New(Native::Msg::Expected_argument_of_type_object_or_external));
    }
    return Undefined();
}
