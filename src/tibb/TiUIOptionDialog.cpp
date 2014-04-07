/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIOptionDialog.h"
#include "TiGenericFunctionObject.h"
#include "TiPropertySetGetObject.h"
#include "NativeOptionDialogObject.h"
#include <bb/system/SystemListDialog>
#include <bb/system/SystemUiButton>
#include <bb/system/SystemUiModality>
#include "V8Utils.h"
#include "TiCore.h"

TiUIOptionDialog::TiUIOptionDialog()
    : TiProxy("OptionDialog")
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
	TiProxy::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "show", this, _show);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "hide", this, _hide);

    TiPropertySetGetObject::createProperty(this, "options", this, _setOptions, NULL);
    TiPropertySetGetObject::createProperty(this, "title", this, _setTitle, NULL);
    TiPropertySetGetObject::createProperty(this, "cancel", this, _setCancel, NULL);
    TiPropertySetGetObject::createProperty(this, "selectedIndex", this, _setSelectedIndex, NULL);
    TiPropertySetGetObject::createProperty(this, "destructive", this, _setDestructive, NULL);

}

void TiUIOptionDialog::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
    	TiProxy::initializeTiObject(parentContext);
    	NativeOptionDialogObject* obj = NativeOptionDialogObject::createDialog(this);
        obj->setEventFactory(getNativeObjectFactory()->getEventContainerFactory());
        setNativeObject(obj);
        obj->release();
    }
}

Handle<Value> TiUIOptionDialog::_show(void* userContext, TiObject*, const Arguments&)
{
    TiUIOptionDialog* obj = static_cast<TiUIOptionDialog*>(userContext);
    NativeOptionDialogObject *dialog = static_cast<NativeOptionDialogObject*>(obj->getNativeObject());
    dialog->show();
	return Undefined();
}

Handle<Value> TiUIOptionDialog::_hide(void* userContext, TiObject*, const Arguments&)
{
    TiUIOptionDialog* obj = static_cast<TiUIOptionDialog*>(userContext);
    NativeOptionDialogObject *dialog = static_cast<NativeOptionDialogObject*>(obj->getNativeObject());
    dialog->hide();
    return Undefined();
}

void TiUIOptionDialog::_setCancel(void* userContext, Handle<Value> arg)
{
    Ti::TiHelper::Log("[WARN] Ti.UI.OptionDialog - \"cancel\" not supported");
}

void TiUIOptionDialog::_setSelectedIndex(void* userContext, Handle<Value> arg)
{
    TiUIOptionDialog* obj = static_cast<TiUIOptionDialog*>(userContext);
    NativeOptionDialogObject *dialog = static_cast<NativeOptionDialogObject*>(obj->getNativeObject());

    dialog->setSelectedIndex((int)arg->ToNumber()->Value());
}

void TiUIOptionDialog::_setDestructive(void* userContext, Handle<Value> arg)
{
    Ti::TiHelper::Log("[WARN] Ti.UI.OptionDialog - \"destructive\" not supported");
}

void TiUIOptionDialog::_setTitle(void* userContext, Handle<Value> arg)
{
    TiUIOptionDialog* obj = static_cast<TiUIOptionDialog*>(userContext);
    NativeOptionDialogObject *dialog = static_cast<NativeOptionDialogObject*>(obj->getNativeObject());
    dialog->setTitle(titanium::V8ValueToQString(arg));
}

void TiUIOptionDialog::_setOptions(void* userContext, Handle<Value> arg)
{
    TiUIOptionDialog* obj = static_cast<TiUIOptionDialog*>(userContext);
    NativeOptionDialogObject *dialog = static_cast<NativeOptionDialogObject*>(obj->getNativeObject());
    if(arg->IsArray())
    {
    	Handle<Array> ar = Handle<Array>::Cast(arg);
    	QStringList options;
    	for(int i = 0, len = ar->Length(); i < len; i++)
    	{
    		options.append(titanium::V8ValueToQString(ar->Get(i)));
    	}
    	dialog->setOptions(options);
    }
}
