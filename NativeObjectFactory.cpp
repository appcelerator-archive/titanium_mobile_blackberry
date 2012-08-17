/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeObjectFactory.h"

#include "NativeActivityIndicatorObject.h"
#include "NativeAlertDialogObject.h"
#include "NativeBufferObject.h"
#include "NativeButtonObject.h"
#include "NativeDateTimePickerObject.h"
#include "NativeDropDownObject.h"
#include "NativeImageViewObject.h"
#include "NativeLabelObject.h"
#include "NativeListViewObject.h"
#include "NativeLoggerObject.h"
#include "NativePageObject.h"
#include "NativeProgressBarObject.h"
#include "NativeTabObject.h"
#include "NativeTabGroupObject.h"
#include "NativeSliderObject.h"
#include "NativeStringInterface.h"
#include "NativeTCPSocketObject.h"
#include "NativeTextFieldObject.h"
#include "NativeToggleButtonObject.h"
#include "TiCascadesApp.h"

#include <bb/cascades/Container>

using namespace bb::cascades;

NativeObjectFactory::NativeObjectFactory(TiCascadesApp* cascadeApp)
{
    cascadesApp_ = cascadeApp;
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
    /* The NativeObject instances created here live in their TiObject counterpart
       The TiObject takes care of deleting them. */
    NativeObject* obj = NULL;
    switch (type)
    {
    case N_TYPE_CONTAINER:

    case N_TYPE_WINDOW:
        obj = NativePageObject::createPage(this);
        break;

    case N_TYPE_LABEL:
        obj = NativeLabelObject::createLabel();
        break;

    case N_TYPE_LOGGER:
        obj = NativeLoggerObject::getInstance();
        break;

    case N_TYPE_BUFFER:
        obj = NativeBufferObject::createBuffer();
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

    case N_TYPE_TAB:
        obj = NativeTabObject::createTab();
        break;

    case N_TYPE_TABGROUP:
        obj = NativeTabGroupObject::createTabGroup(this);
        break;

    case N_TYPE_TCPSOCKET:
        obj = NativeTCPSocketObject::createTCPSocket();
        break;

    case N_TYPE_DATE_TIME_PICKER:
        obj = NativeDateTimePickerObject::createDateTimePicker();
        break;

    case N_TYPE_ALERTDIALOG:
        obj = NativeAlertDialogObject::createAlertDialog();
        break;

    case N_TYPE_VIEW:
        obj = NativeControlObject::createView();
        break;

    }
    if (obj != NULL)
    {
        obj->initialize();
        obj->setupEvents(eventContainerFactory_);
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
