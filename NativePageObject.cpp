/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativePageObject.h"
#include "NativeObjectFactory.h"
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/ActivityIndicator>
#include <bb/cascades/Button>
#include <bb/cascades/Color>
#include <bb/cascades/Container>
#include <bb/cascades/DateTimePicker>
#include <bb/cascades/DockLayout>
#include <bb/cascades/DockLayoutProperties>
#include <bb/cascades/DropDown>
#include <bb/cascades/ImageView>
#include <bb/cascades/Label>
#include <bb/cascades/ListView>
#include <bb/cascades/ProgressIndicator>
#include <bb/cascades/Slider>
#include <bb/cascades/Stacklayout>
#include <bb/cascades/TextField>
#include <bb/cascades/ToggleButton>
#include <qtgui/QColor>

using namespace bb::cascades;

NativePageObject::NativePageObject()
{
    container_ = NULL;
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

int NativePageObject::initialize(TiEventContainerFactory* containerFactory)
{
    if (container_ != NULL || page_ != NULL)
    {
        return NATIVE_ERROR_OK;
    }

    //TODO separate the logic of container and page in different classes
    container_ = Container::create();
    setContainer(container_);
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
    Q_ASSERT(container_ != NULL);
    bb::cascades::Control* control = (bb::cascades::Control*) obj->getNativeHandle();
    container_->add(control);
    return NATIVE_ERROR_OK;
}

int NativePageObject::open()
{
    Q_ASSERT(container_ != NULL);
    container_->setLayout(new AbsoluteLayout());
    nativeObjectFactory_->setRootContainer(this);
    return NATIVE_ERROR_OK;
}

int NativePageObject::removeChildNativeObject(NativeObject* obj)
{
    Q_ASSERT(container_ != NULL);
    bb::cascades::Control* control = (bb::cascades::Control*) obj->getNativeHandle();
    container_->remove(control);
    return NATIVE_ERROR_OK;
}

int NativePageObject::setBackgroundColor(TiObject* obj)
{
    float r;
    float g;
    float b;
    float a;

    int error = NativeControlObject::getColorComponents(obj, &r, &g, &b, &a);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    bb::cascades::Color cscolor = bb::cascades::Color::fromRGBA(r, g, b, a);
    Q_ASSERT(container_ != NULL);
    container_->setBackground(cscolor);
    return NATIVE_ERROR_OK;
}
