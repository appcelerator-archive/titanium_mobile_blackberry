/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIAlertDialog.h"

#include "NativeAlertDialogObject.h"
#include "TiGenericFunctionObject.h"

TiUIAlertDialog::TiUIAlertDialog()
    : TiUIBase("")
{
}

TiUIAlertDialog::~TiUIAlertDialog()
{
}

TiUIAlertDialog* TiUIAlertDialog::createAlertDialog(NativeObjectFactory* nativeObjectFactory)
{
    TiUIAlertDialog* obj = new TiUIAlertDialog;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUIAlertDialog::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "show", this, show_);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "hide", this, hide_);
}

void TiUIAlertDialog::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiProxy::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_ALERTDIALOG, this);
        setNativeObject(obj);
        obj->release();
    }
}

Handle<Value> TiUIAlertDialog::show_(void* userContext, TiObject*, const Arguments&)
{
    HandleScope handleScope;
    TiUIAlertDialog* obj = (TiUIAlertDialog*) userContext;
    NativeAlertDialogObject* no = (NativeAlertDialogObject*)obj->getNativeObject();
    no->show();
    no->release();
    return Undefined();
}

Handle<Value> TiUIAlertDialog::hide_(void* userContext, TiObject*, const Arguments&)
{
    HandleScope handleScope;
    TiUIAlertDialog* obj = (TiUIAlertDialog*) userContext;
    NativeAlertDialogObject* no = (NativeAlertDialogObject*)obj->getNativeObject();
    no->hide();
    no->release();
    return Undefined();
}
