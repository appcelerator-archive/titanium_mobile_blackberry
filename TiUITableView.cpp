/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUITableView.h"

#include "TiGenericFunctionObject.h"
#include "TiLogger.h"
#include "TiMessageStrings.h"

TiUITableView::TiUITableView()
    : TiUIBase("")
{
}

TiUITableView::~TiUITableView()
{
}

TiUITableView* TiUITableView::createTableView(NativeObjectFactory* nativeObjectFactory)
{
    TiUITableView* obj = new TiUITableView;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUITableView::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_LIST_VIEW, this);
        setNativeObject(obj);
        obj->release();
    }
}

void TiUITableView::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "scrollToIndex", this, _scrollToIndex);
}

Handle<Value> TiUITableView::_scrollToIndex(void* userContext, TiObject*, const Arguments& args)
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
        TI_DEBUG(Ti::Msg::INTERNAL__args0_is_not_a_number);
    }

    return Undefined();
}
