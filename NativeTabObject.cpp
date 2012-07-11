/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeTabObject.h"

#include <bb/cascades/Image>
#include <bb/cascades/Page>
#include <bb/cascades/TabbedPaneProperties>


using namespace bb::cascades;

NativeTabObject::NativeTabObject() :
    page_(NULL),
    tabProperties_(NULL)
{
}

NativeTabObject::~NativeTabObject()
{
    delete page_;
    page_ = NULL;
    delete tabProperties_;
    tabProperties_ = NULL;
}

NativeObject* NativeTabObject::createTab()
{
    NativeTabObject* obj = new NativeTabObject;
    return obj;
}

int NativeTabObject::getObjectType() const
{
    return N_TYPE_TAB;
}

NAHANDLE NativeTabObject::getNativeHandle() const
{
    return page_;
}

int NativeTabObject::setTitle(TiObject* obj)
{
    QString str;

    int error = NativeControlObject::getString(obj, str);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    tabProperties_->setTitle(str);
    return NATIVE_ERROR_OK;
}

int NativeTabObject::setIcon(TiObject* obj)
{
    QString str;
    int error = NativeControlObject::getString(obj, str);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    const bb::cascades::Image image = bb::cascades::Image(QUrl(str));
    tabProperties_->setImage(image);
    return NATIVE_ERROR_OK;
}

int NativeTabObject::addChildNativeObject(NativeObject* obj)
{
    if (obj->getObjectType() == N_TYPE_WINDOW)
    {
        page_ = (bb::cascades::Page*) obj->getNativeHandle();
        page_->setPaneProperties(tabProperties_);
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeTabObject::initialize(TiEventContainerFactory* containerFactory)
{
    if (page_ != NULL)
    {
        return NATIVE_ERROR_OK;
    }

    tabProperties_ = TabbedPaneProperties::create();

    if (tabProperties_ == NULL)
    {
        return NATIVE_ERROR_OUTOFMEMORY;
    }
    return NATIVE_ERROR_OK;
}
