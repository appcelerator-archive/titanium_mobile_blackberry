/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeContainerObject.h"
#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/DockLayoutProperties>
#include <bb/cascades/Stacklayout>
#include <bb/cascades/Label>
#include <bb/cascades/Button>
#include <bb/cascades/Slider>
#include "TiUtility.h"

using namespace bb::cascades;

NativeContainerObject::NativeContainerObject()
{
    container_ = NULL;
    root_ = NULL;
}

NativeContainerObject::NativeContainerObject(Container* container)
{
    container_ = container;
    root_ = NULL;
}

NativeContainerObject::~NativeContainerObject()
{
}

NativeObject* NativeContainerObject::createContainer(NativeContainerObject* root)
{
    NativeContainerObject* obj = new NativeContainerObject;
    obj->setRootContainer(root);
    return obj;
}

int NativeContainerObject::getObjectType() const
{
    return NO_TYPE_CONTAINER;
}

NAHANDLE NativeContainerObject::getNativeHandle() const
{
    return container_;
}

int NativeContainerObject::initialize()
{
    container_ = Container::create();
    if (container_ == NULL)
    {
        return NATIVE_ERROR_OUTOFMEMORY;
    }
    container_->setLayout(new DockLayout());
    //container_->setLayout(new StackLayout());
    container_->setLayoutProperties(
            DockLayoutProperties::create().horizontal(HorizontalAlignment::Center).vertical(VerticalAlignment::Center));
    return NATIVE_ERROR_OK;
}

int NativeContainerObject::addChildNativeObject(NativeObject* obj)
{
    bb::cascades::Container* container;
    bb::cascades::Label* label;
    bb::cascades::Button* button;
    bb::cascades::Slider* slider;
    switch (obj->getObjectType())
    {
    case NO_TYPE_CONTAINER:
    case NO_TYPE_WINDOW:
        container = (bb::cascades::Container*) obj->getNativeHandle();
        container_->add(container);
        return NATIVE_ERROR_OK;
    case NO_TYPE_LABEL:
        label = (bb::cascades::Label*) obj->getNativeHandle();
        container_->add(label);
        return NATIVE_ERROR_OK;
    case NO_TYPE_BUTTON:
        button=(bb::cascades::Button*)obj->getNativeHandle();
        container_->add(button);
        return NATIVE_ERROR_OK;
    case NO_TYPE_SLIDER:
        slider=(bb::cascades::Slider*)obj->getNativeHandle();
        container_->add(slider);
        return NATIVE_ERROR_OK;

    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeContainerObject::open()
{
    if (root_ == NULL)
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    bb::cascades::Container* rootContainer = (bb::cascades::Container*) root_->getNativeHandle();
    rootContainer->add(container_);
    return NATIVE_ERROR_OK;
}

void NativeContainerObject::setRootContainer(NativeContainerObject* root)
{
    root_ = root;
}
