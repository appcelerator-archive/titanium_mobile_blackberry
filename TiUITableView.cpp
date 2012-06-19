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

TiUIBase* TiUITableView::createTableView(NativeObjectFactory* nativeObjectFactory)
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
    TiGenericFunctionObject::addGenericFunctionToParent(this, "scrollToIndex", this, _scrollToIndex);
}

Handle<Value> TiUITableView::_scrollToIndex(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUITableView* obj = (TiUITableView*) userContext;
    NativeObject* no = obj->getNativeObject();
    if (args[0]->IsNumber())
    {
        Local<Integer> index = args[0]->ToInteger();
        no->scrollToIndex(index->Value());
    }
    else
    {
        qDebug() << "TiUITableView::_scrollToIndex - args[0] is not a number.";
    }

    return Undefined();
}
