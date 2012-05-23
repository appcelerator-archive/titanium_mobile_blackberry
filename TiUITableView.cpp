/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITableView.h"
#include "TiGenericFunctionObject.h"

TiUITableView::TiUITableView(NativeObjectFactory* nativeObjectFactory)
    : TiUIBase(nativeObjectFactory, "")
{
}

TiUITableView::~TiUITableView()
{
}

TiUITableView* TiUITableView::createTableView(NativeObjectFactory* nativeObjectFactory)
{
    TiUITableView* obj = new TiUITableView(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUITableView::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_LIST_VIEW);
        setNativeObject(obj);
        obj->release();
    }
}

void TiUITableView::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "scrollToIndex", this, scrollToIndex_);
}

Handle<Value> TiUITableView::scrollToIndex_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUITableView* obj = (TiUITableView*) userContext;
    NativeObject* no = obj->getNativeObject();

    Local<String> str = args[0]->ToString();
    String::Utf8Value index(str);
    no->scrollToIndex(*index);
    return Undefined();
}
