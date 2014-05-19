/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativePageObject.h"

#include <bb/cascades/Container>
#include <bb/cascades/Page>
#include <bb/cascades/TitleBar>

#include "NativeObjectFactory.h"
#include "TiCascadesApp.h"
#include "TiObject.h"
#include "V8Utils.h"

using namespace bb::cascades;
using namespace titanium;

NativePageObject::NativePageObject(TiObject* tiObject)
    : NativeControlObject(tiObject, N_TYPE_WINDOW)
{
    nativeObjectFactory_ = NULL;
    page_ = NULL;
    titleBar_ = NULL;
}

NativePageObject::~NativePageObject()
{
}

NativeObject* NativePageObject::createPage(TiObject* tiObject, NativeObjectFactory* nativeObjectFactory)
{
    NativePageObject* obj = new NativePageObject(tiObject);
    obj->nativeObjectFactory_ = nativeObjectFactory;
    return obj;
}

NATIVE_TYPE NativePageObject::getObjectType() const
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
    Q_ASSERT(nativeObjectFactory_ != NULL);
    Q_ASSERT(nativeObjectFactory_->getCascadeApp() != NULL);
    nativeObjectFactory_->setRootContainer(this);
    // FIXME: currently setting a new scene deletes the previous scene object
    // see TIMOB-10543 for a WIP patch
    nativeObjectFactory_->getCascadeApp()->setScene(this);
    return NATIVE_ERROR_OK;
}

int NativePageObject::removeChildNativeObject(NativeObject* obj)
{
    return removeChildImpl(obj);
}

int NativePageObject::setTitle(TiObject* obj)
{
    QString title = V8ValueToQString(obj->getValue());
    if (titleBar_ == NULL)
    {
        titleBar_ = new bb::cascades::TitleBar();
    }
    titleBar_->setTitle(title);
    page_->setTitleBar(titleBar_);
    return NATIVE_ERROR_OK;
}
