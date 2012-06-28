/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeObjectFactory.h"

#include "NativeActivityIndicatorObject.h"
#include "NativeButtonObject.h"
#include "NativeContainerObject.h"
#include "NativeDateTimePickerObject.h"
#include "NativeDropDownObject.h"
#include "NativeImageViewObject.h"
#include "NativeLabelObject.h"
#include "NativeListViewObject.h"
#include "NativeProgressBarObject.h"
#include "NativeSliderObject.h"
#include "NativeStringInterface.h"
#include "NativeTextFieldObject.h"
#include "NativeToggleButtonObject.h"
#include "TiCascadesApp.h"
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
    delete eventContainerFactory_;
    eventContainerFactory_ = NULL;
}

NativeObject* NativeObjectFactory::createNativeObject(int type)
{
    NativeObject* obj = NULL;
    switch (type)
    {
    case N_TYPE_CONTAINER:

    case N_TYPE_WINDOW:
        obj = NativeContainerObject::createContainer(this);
        break;

    case N_TYPE_LABEL:
        obj = NativeLabelObject::createLabel();
        break;

    case N_TYPE_BUTTON:
        obj = new NativeButtonObject;
        break;

    case N_TYPE_SLIDER:
        obj = new NativeSliderObject;
        break;

    case N_TYPE_PROGRESSBAR:
        obj = NativeProgressBarObject::createProgressBar();
        break;

    case N_TYPE_TEXT_FIELD:
        obj = NativeTextFieldObject::createTextField();
        break;

    case N_TYPE_IMAGEVIEW:
        obj = NativeImageViewObject::createImageView();
        break;

    case N_TYPE_ACTIVITYINDICATOR:
        obj = NativeActivityIndicatorObject::createActivityIndicator();
        break;

    case N_TYPE_TOGGLEBUTTON:
        obj = NativeToggleButtonObject::createToggleButton();
        break;

    case N_TYPE_DROPDOWN:
        obj = NativeDropDownObject::createDropDown();
        break;

    case N_TYPE_LIST_VIEW:
        obj = NativeListViewObject::createListView();
        break;

    case N_TYPE_DATE_TIME_PICKER:
        obj = NativeDateTimePickerObject::createDateTimePicker();
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
    if (eventContainerFactory_ != NULL)
    {
        delete eventContainerFactory_;
    }
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

const NativeStringInterface* NativeObjectFactory::getNativeStringInterface()
{
    return NativeStringInterface::instance();
}
