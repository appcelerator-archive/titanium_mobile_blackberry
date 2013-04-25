/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIScrollableView.h"
#include "TiGenericFunctionObject.h"
#include "NativeScrollableViewObject.h"
#include "TiLogger.h"
#include "TiMessageStrings.h"
#include "NativeObject.h"
#include <iostream>

TiUIScrollableView::~TiUIScrollableView()
{
}

TiUIScrollableView::TiUIScrollableView()
    : TiUIBase("")
{
}

TiUIScrollableView::TiUIScrollableView(const char* name)
    : TiUIBase(name)
{
}

TiUIScrollableView* TiUIScrollableView::createScrollableView(NativeObjectFactory* nativeObjectFactory)
{
    TiUIScrollableView* obj = new TiUIScrollableView;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUIScrollableView::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "addView", this, _addView);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "moveNext", this, _moveNext);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "movePrevious", this, _movePrevious);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "scrollToView", this, _scrollToView);
}

void TiUIScrollableView::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_SCROLLABLE_VIEW, this);
        setNativeObject(obj);
        obj->release();
    }
}

Handle<Value> TiUIScrollableView::_moveNext(void* userContext, TiObject*, const Arguments& args)
{
    TiUIScrollableView* self = static_cast<TiUIScrollableView*>(userContext);
    NativeScrollableViewObject* scrollableView = static_cast<NativeScrollableViewObject*>(self->getNativeObject());
    scrollableView->moveNext();
    return Undefined();

}
Handle<Value> TiUIScrollableView::_movePrevious(void* userContext, TiObject*, const Arguments& args)
{
    TiUIScrollableView* self = static_cast<TiUIScrollableView*>(userContext);
    NativeScrollableViewObject* scrollableView = static_cast<NativeScrollableViewObject*>(self->getNativeObject());
    scrollableView->movePrevious();
    return Undefined();
}
Handle<Value> TiUIScrollableView::_addView(void* userContext, TiObject*, const Arguments& args)
{
    TiUIScrollableView* self = static_cast<TiUIScrollableView*>(userContext);
    NativeScrollableViewObject* scrollableView = static_cast<NativeScrollableViewObject*>(self->getNativeObject());

    TiObject* tiObj = TiObject::getTiObjectFromJsObject(args[0]);
	NativeObject* view = (NativeObject*)tiObj->getNativeObject();
    scrollableView->addChildNativeObject(view);
    return Undefined();
}

Handle<Value> TiUIScrollableView::_scrollToView(void* userContext, TiObject*, const Arguments& args)
{
    TiUIScrollableView* self = static_cast<TiUIScrollableView*>(userContext);
    NativeScrollableViewObject* scrollableView = static_cast<NativeScrollableViewObject*>(self->getNativeObject());

    bool animated = true;
    if(args.Length() > 1) {
        Local<Boolean> _animated = args[1]->ToBoolean();
        animated = _animated->Value();
    }

    if (args[0]->IsNumber())
    {
        Local<Integer> index = args[0]->ToInteger();
        scrollableView->scrollToIndex(index->Value(), animated);
    }
    else
    {
    	TiObject* tiObj = TiObject::getTiObjectFromJsObject(args[0]);
    	scrollableView->scrollToView((NativeObject*)tiObj, animated);
    }


    return Undefined();
}

