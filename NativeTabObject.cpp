/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeTabObject.h"

#include <bb/cascades/ActionItem>
#include <bb/cascades/Image>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/NavigationPaneProperties>
#include <bb/cascades/Page>
//#include <bb/cascades/TabbedPaneProperties>

using namespace bb::cascades;

NativeTabObject::NativeTabObject() :
    tabProperties_(NULL),
    navigationPane_(NULL)
{
}

NativeTabObject::~NativeTabObject()
{
    delete tabProperties_;
    tabProperties_ = NULL;
    delete navigationPane_;
    navigationPane_ = NULL;
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
    return navigationPane_;
}

int NativeTabObject::setTitle(TiObject* obj)
{
    QString str;

    int error = NativeControlObject::getString(obj, str);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    // TODO: fix for R6
    //tabProperties_->setTitle(str);
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
    // TODO: fix path
    const bb::cascades::Image image = bb::cascades::Image(QUrl("assets" + str));
    // TODO: fix for R6
    //tabProperties_->setImage(image);
    return NATIVE_ERROR_OK;
}

int NativeTabObject::addChildNativeObject(NativeObject* obj)
{
    if (obj->getObjectType() == N_TYPE_WINDOW)
    {
        bb::cascades::Page* page = (bb::cascades::Page*)obj->getNativeHandle();
        // TODO: fix for R6
        //navigationPane_->setPaneProperties(tabProperties_);
        navigationPane_->push(page);
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeTabObject::openWindowOnTab(NativeObject* obj)
{
    if (obj->getObjectType() == N_TYPE_WINDOW)
    {
        bb::cascades::Page* page = (bb::cascades::Page*)obj->getNativeHandle();
        ActionItem* backAction = ActionItem::create();
        QObject::connect(backAction, SIGNAL(triggered()), navigationPane_, SLOT(pop()));
        page->setPaneProperties(NavigationPaneProperties::create().backButton(backAction));
        navigationPane_->push(page);
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeTabObject::initialize()
{
    // TODO: fix for R6
    //tabProperties_ = TabbedPaneProperties::create();
    navigationPane_ = NavigationPane::create();

    if (tabProperties_ == NULL || navigationPane_ == NULL)
    {
        return NATIVE_ERROR_OUTOFMEMORY;
    }
    return NATIVE_ERROR_OK;
}
