/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativePageObject.h"

#include "NativeObjectFactory.h"
#include <bb/cascades/Container>
#include <bb/cascades/Page>

using namespace bb::cascades;

NativePageObject::NativePageObject()
{
    nativeObjectFactory_ = NULL;
    page_ = NULL;
}

NativePageObject::~NativePageObject()
{
}

NativeObject* NativePageObject::createPage(NativeObjectFactory* nativeObjectFactory)
{
    NativePageObject* obj = new NativePageObject;
    obj->nativeObjectFactory_ = nativeObjectFactory;
    return obj;
}

int NativePageObject::getObjectType() const
{
    return N_TYPE_WINDOW;
}

NAHANDLE NativePageObject::getNativeHandle() const
{
    return page_;
}

int NativePageObject::initialize()
{
    if (container_ != NULL || page_ != NULL)
    {
        return NATIVE_ERROR_OK;
    }

    /* Special case: UI.Windows only needs the container; setControl will create it */
    setControl(NULL);
    container_->resetLayoutProperties();
    page_ = Page::create();
    page_->setContent(container_);

    if (container_ == NULL || page_ == NULL)
    {
        return NATIVE_ERROR_OUTOFMEMORY;
    }
    return NATIVE_ERROR_OK;
}

int NativePageObject::addChildNativeObject(NativeObject* obj)
{
    return addChildImpl(obj);
}

int NativePageObject::open()
{
    nativeObjectFactory_->setRootContainer(this);
    return NATIVE_ERROR_OK;
}

int NativePageObject::removeChildNativeObject(NativeObject* obj)
{
    return removeChildImpl(obj);
}
