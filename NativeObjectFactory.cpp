/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiCascadesApp.h"
#include "NativeObjectFactory.h"
#include "NativeContainerObject.h"
#include "NativeLabelObject.h"
#include "NativeButtonObject.h"
#include "NativeSliderObject.h"
#include "NativeProgressBarObject.h"
#include <bb/cascades/Container>

using namespace bb::cascades;

NativeObjectFactory::NativeObjectFactory(TiCascadesApp* cascadesApp)
{
    cascadesApp_ = NULL;
    eventContainerFactory_ = NULL;
    rootContainer_ = NULL;
}

NativeObjectFactory::~NativeObjectFactory()
{
    if (rootContainer_ != NULL)
    {
        rootContainer_->release();
        rootContainer_ = NULL;
    }
    if (eventContainerFactory_ != NULL)
    {
        delete eventContainerFactory_;
    }
}

NativeObject* NativeObjectFactory::createNativeObject(int type)
{
    NativeObject* obj = NULL;
    switch (type)
    {
    case NO_TYPE_CONTAINER:
        case NO_TYPE_WINDOW:
        obj = NativeContainerObject::createContainer(this);
        break;
    case NO_TYPE_LABEL:
        obj = new NativeLabelObject;
        break;
    case NO_TYPE_BUTTON:
        obj = new NativeButtonObject;
        break;
    case NO_TYPE_SLIDER:
        obj = new NativeSliderObject;
        break;
    case NO_TYPE_PROGRESSBAR:
        obj = new NativeProgressBarObject;
        break;
    }
    if (obj != NULL)
    {
        obj->initialize(eventContainerFactory_);
    }
    return obj;
}

void NativeObjectFactory::setRootContainer(NativeObject* container)
{
    if (container != NULL)
    {
        container->addRef();
    }
    if (rootContainer_ != NULL)
    {
        rootContainer_->release();
    }
    rootContainer_ = container;
}

void NativeObjectFactory::setEventContainerFactory(TiEventContainerFactory* eventContainerFactory)
{
    eventContainerFactory_ = eventContainerFactory;
}

TiEventContainerFactory* NativeObjectFactory::getEventContainerFactory() const
{
    return eventContainerFactory_;
}

NativeObject* NativeObjectFactory::getRootContainer() const
{
    if (rootContainer_ != NULL)
    {
        rootContainer_->addRef();
    }
    return rootContainer_;
}
