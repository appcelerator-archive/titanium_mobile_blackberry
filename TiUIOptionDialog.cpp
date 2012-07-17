/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIOptionDialog.h"
#include "TiGenericFunctionObject.h"

TiUIOptionDialog::TiUIOptionDialog()
    : TiUIBase("")
{
}

TiUIOptionDialog::~TiUIOptionDialog()
{
}

TiUIOptionDialog* TiUIOptionDialog::createOptionDialog(NativeObjectFactory* nativeObjectFactory)
{
    TiUIOptionDialog* obj = new TiUIOptionDialog;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUIOptionDialog::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "show", this, _show);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "hide", this, _hide);
}

void TiUIOptionDialog::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiProxy::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_DROPDOWN);
        setNativeObject(obj);
        obj->release();
    }
}

Handle<Value> TiUIOptionDialog::_show(void* userContext, TiObject*, const Arguments&)
{
    TiUIOptionDialog* obj = (TiUIOptionDialog*)userContext;
    NativeObject* rootContainer = obj->getNativeObjectFactory()->getRootContainer();
    if (rootContainer != NULL)
    {
        rootContainer->addChildNativeObject(obj->getNativeObject());
    }
    return Undefined();
}

Handle<Value> TiUIOptionDialog::_hide(void*, TiObject*, const Arguments&)
{
    // TODO: Remove from container
    return Undefined();
}
