/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeObjectFactory.h"
#include "NativeTabGroupObject.h"
#include <bb/cascades/TabbedPane>

using namespace bb::cascades;

NativeTabGroupObject::NativeTabGroupObject() :
    nativeObjectFactory_(NULL),
    tabGroup_(NULL)
{
}

NativeTabGroupObject::~NativeTabGroupObject()
{
    delete tabGroup_;
    tabGroup_ = NULL;
}

NativeObject* NativeTabGroupObject::createTabGroup(NativeObjectFactory* nativeObjectFactory)
{
    NativeTabGroupObject* obj = new NativeTabGroupObject;
    obj->nativeObjectFactory_ = nativeObjectFactory;
    return obj;
}

int NativeTabGroupObject::getObjectType() const
{
    return N_TYPE_TABGROUP;
}

NAHANDLE NativeTabGroupObject::getNativeHandle() const
{
    return tabGroup_;
}

int NativeTabGroupObject::initialize()
{
    if (tabGroup_ != NULL)
    {
        return NATIVE_ERROR_OK;
    }

    tabGroup_ = TabbedPane::create();

    if (tabGroup_ == NULL)
    {
        return NATIVE_ERROR_OUTOFMEMORY;
    }
    return NATIVE_ERROR_OK;
}

int NativeTabGroupObject::addChildNativeObject(NativeObject* obj)
{
    if (obj && obj->getObjectType() == N_TYPE_TAB)
    {
        if (obj->getNativeHandle())
        {
            tabGroup_->add((bb::cascades::Tab*) obj->getNativeHandle());
            return NATIVE_ERROR_OK;
        }
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeTabGroupObject::setActiveTab(NativeObject* tab)
{
    if (tab && tab->getObjectType() == N_TYPE_TAB)
    {
        if (tab->getNativeHandle())
        {
            tabGroup_->setActiveTab((bb::cascades::Tab*) tab->getNativeHandle());
            return NATIVE_ERROR_OK;
        }
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeTabGroupObject::setActiveTab(int index)
{
    if (tabGroup_->at(index) != 0)
    {
        tabGroup_->setActiveTab(tabGroup_->at(index));
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeTabGroupObject::open()
{
    nativeObjectFactory_->setRootContainer(this);
    return NATIVE_ERROR_OK;
}
