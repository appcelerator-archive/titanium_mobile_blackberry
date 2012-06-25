/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeContainerObject.h"
#include "NativeObjectFactory.h"
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/ActivityIndicator>
#include <bb/cascades/Button>
#include <bb/cascades/Color>
#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/DockLayoutProperties>
#include <bb/cascades/ImageView>
#include <bb/cascades/Label>
#include <bb/cascades/ListView>
#include <bb/cascades/ProgressIndicator>
#include <bb/cascades/Slider>
#include <bb/cascades/Stacklayout>
#include <bb/cascades/TextField>
#include <bb/cascades/ToggleButton>
#include <bb/cascades/ActivityIndicator>
#include <bb/cascades/DropDown>
#include <qtgui/QColor>

using namespace bb::cascades;

NativeContainerObject::NativeContainerObject()
{
    container_ = NULL;
    nativeObjectFactory_ = NULL;
}

NativeContainerObject::NativeContainerObject(Container* container)
{
    container_ = container;
    nativeObjectFactory_ = NULL;
}

NativeContainerObject::~NativeContainerObject()
{
}

NativeObject* NativeContainerObject::createContainer(NativeObjectFactory* nativeObjectFactory)
{
    NativeContainerObject* obj = new NativeContainerObject;
    obj->nativeObjectFactory_ = nativeObjectFactory;
    return obj;
}

int NativeContainerObject::getObjectType() const
{
    return N_TYPE_CONTAINER;
}

NAHANDLE NativeContainerObject::getNativeHandle() const
{
    return container_;
}

int NativeContainerObject::initialize(TiEventContainerFactory* containerFactory)
{
    if (container_ != NULL)
    {
        return NATIVE_ERROR_OK;
    }
    container_ = Container::create();
    if (container_ == NULL)
    {
        return NATIVE_ERROR_OUTOFMEMORY;
    }
    return NATIVE_ERROR_OK;
}

int NativeContainerObject::addChildNativeObject(NativeObject* obj)
{
    bb::cascades::Control* control = (bb::cascades::Control*) obj->getNativeHandle();
    container_->add(control);
    return NATIVE_ERROR_OK;
}

int NativeContainerObject::open()
{
    container_->setLayout(new AbsoluteLayout());
    nativeObjectFactory_->setRootContainer(this);
    return NATIVE_ERROR_OK;
}

int NativeContainerObject::setBackgroundColor(TiObject* obj)
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
    container_->setBackground(cscolor);
    return NATIVE_ERROR_OK;
}
