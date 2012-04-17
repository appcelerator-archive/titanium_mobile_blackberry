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
#include <bb/cascades/Color>
#include <bb/cascades/ProgressIndicator>
#include "TiUtility.h"
#include "NativeObjectFactory.h"

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
    return NO_TYPE_CONTAINER;
}

NAHANDLE NativeContainerObject::getNativeHandle() const
{
    return container_;
}

int NativeContainerObject::initialize(TiEventContainerFactory* containerFactory)
{
    container_ = Container::create();
    if (container_ == NULL)
    {
        return NATIVE_ERROR_OUTOFMEMORY;
    }
    container_->setLayout(StackLayout::create());
    return NATIVE_ERROR_OK;
}

int NativeContainerObject::addChildNativeObject(NativeObject* obj)
{
    bb::cascades::Container* container;
    bb::cascades::Label* label;
    bb::cascades::Button* button;
    bb::cascades::Slider* slider;
    bb::cascades::ProgressIndicator* progressIndicator;
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
        button = (bb::cascades::Button*) obj->getNativeHandle();
        container_->add(button);
        return NATIVE_ERROR_OK;
    case NO_TYPE_SLIDER:
        slider = (bb::cascades::Slider*) obj->getNativeHandle();
        container_->add(slider);
        return NATIVE_ERROR_OK;
    case NO_TYPE_PROGRESSBAR:
        progressIndicator = (bb::cascades::ProgressIndicator*) obj->getNativeHandle();
        container_->add(progressIndicator);
        return NATIVE_ERROR_OK;
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeContainerObject::open()
{
    nativeObjectFactory_->setRootContainer(this);
    return NATIVE_ERROR_OK;
}

int NativeContainerObject::setBackgroundColor(const char* text)
{
    float a;
    float r;
    float g;
    float b;
    TiUtility::convertHTMLStringToColorComponents(text, &r, &g, &b, &a);
    Color color = Color::fromRGBA(r, g, b, a);
    container_->setBackground(color);
    return NATIVE_ERROR_OK;
}
