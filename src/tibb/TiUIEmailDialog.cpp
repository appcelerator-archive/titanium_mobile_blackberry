/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIEmailDialog.h"
#include "NativeEmailDialogObject.h"
#include "TiGenericFunctionObject.h"
#include <iostream>

const static TiProperty g_tiProperties[] = {
    { "messageBody", TI_PROP_PERMISSION_READ, N_EMAIL_PROP_MESSAGE },
    { "html", TI_PROP_PERMISSION_READ, N_EMAIL_PROP_HTML },
    { "subject", TI_PROP_PERMISSION_READ, N_EMAIL_PROP_SUBJECT },
    { "toRecipients", TI_PROP_PERMISSION_READ, N_EMAIL_PROP_TO },
    { "ccRecipients", TI_PROP_PERMISSION_READ, N_EMAIL_PROP_CC },
    { "bccRecipients", TI_PROP_PERMISSION_READ, N_EMAIL_PROP_BCC },
    { "fromRecipients", TI_PROP_PERMISSION_READ, N_EMAIL_PROP_FROM }

};

TiUIEmailDialog::TiUIEmailDialog()
    : TiUIBase("")
{
}

TiUIEmailDialog::~TiUIEmailDialog()
{
}

TiUIEmailDialog* TiUIEmailDialog::createEmailDialog(NativeObjectFactory* nativeObjectFactory)
{
    TiUIEmailDialog* obj = new TiUIEmailDialog;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUIEmailDialog::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_EMAILDIALOG, this);
        setNativeObject(obj);
        obj->release();
    }
}

void TiUIEmailDialog::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "open", this, _open);
    TiGenericFunctionObject::addGenericFunctionToParent(this,"addAttachment", this, _addAttachment);
    setTiMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));
}

Handle<Value> TiUIEmailDialog::_open(void* userContext, TiObject*, const Arguments& args)
{
    HandleScope handleScope;
    TiUIEmailDialog* self = static_cast<TiUIEmailDialog*>(userContext);
    NativeEmailDialogObject* emailDialog = static_cast<NativeEmailDialogObject*>(self->getNativeObject());
    emailDialog->open();

    return Undefined();
}

Handle<Value> TiUIEmailDialog::_addAttachment(void* userContext, TiObject*, const Arguments& args)
{
    HandleScope handleScope;
    TiUIEmailDialog* self = static_cast<TiUIEmailDialog*>(userContext);
    NativeEmailDialogObject* emailDialog = static_cast<NativeEmailDialogObject*>(self->getNativeObject());
    emailDialog->addAttachment( /* Ti.Filesystem */);

    return Undefined();
}


