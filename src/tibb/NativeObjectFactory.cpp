/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeObjectFactory.h"

#include "NativeAccelerometerObject.h"
#include "NativeActivityIndicatorObject.h"
#include "NativeAlertDialogObject.h"
#include "NativeBlobObject.h"
#include "NativeBufferObject.h"
#include "NativeButtonObject.h"
#include "NativeDateTimePickerObject.h"
#include "NativeDropDownObject.h"
#include "NativeGestureObject.h"
#include "NativeImageViewObject.h"
#include "NativeLabelObject.h"
#include "NativeListItemObject.h"
#include "NativeListViewObject.h"
#include "NativeLoggerObject.h"
#include "NativeProgressBarObject.h"
#include "NativeTabObject.h"
#include "NativeTabGroupObject.h"
#include "NativeSliderObject.h"
#include "NativeStringInterface.h"
#include "NativeTCPSocketObject.h"
#include "NativeUDPSocketObject.h"
#include "NativeTextFieldObject.h"
#include "NativeTextAreaObject.h"
#include "NativeToggleButtonObject.h"
#include "NativeWindowObject.h"
#include "NativeHTTPClientObject.h"
#include "NativeDBObject.h"
#include "NativeResultSetObject.h"
#include "NativeScrollViewObject.h"
#include "NativeScrollableViewObject.h"
#include "NativeWebViewObject.h"
#include "NativeMapViewObject.h"
#include "NativeAnnotationObject.h"
#include "NativeAudioPlayerObject.h"
#include "NativeAudioRecorderObject.h"
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

NativeObject* NativeObjectFactory::createNativeObject(int type, TiObject* tiObj)
{
    /* The NativeObject instances created here live in their TiObject counterpart
       The TiObject takes care of deleting them. */
    NativeObject* obj = NULL;
    switch (type)
    {
    case N_TYPE_WINDOW:
        obj = NativeWindowObject::createWindow(tiObj, this);
        break;

    case N_TYPE_LABEL:
        obj = NativeLabelObject::createLabel(tiObj);
        break;

    case N_TYPE_LOGGER:
        obj = NativeLoggerObject::getInstance();
        break;

    case N_TYPE_BLOB:
        obj = NativeBlobObject::createBlob(tiObj);
        break;

    case N_TYPE_BUFFER:
        obj = NativeBufferObject::createBuffer(tiObj);
        break;

    case N_TYPE_BUTTON:
        obj = NativeButtonObject::createButton(tiObj);
        break;

    case N_TYPE_SLIDER:
        obj = NativeSliderObject::createSlider(tiObj);
        break;

    case N_TYPE_PROGRESSBAR:
        obj = NativeProgressBarObject::createProgressBar(tiObj);
        break;

    case N_TYPE_TEXT_FIELD:
        obj = NativeTextFieldObject::createTextField(tiObj);
        break;

    case N_TYPE_TEXT_AREA:
            obj = NativeTextAreaObject::createTextArea(tiObj);
            break;

    case N_TYPE_IMAGEVIEW:
        obj = NativeImageViewObject::createImageView(tiObj);
        break;

    case N_TYPE_ACTIVITYINDICATOR:
        obj = NativeActivityIndicatorObject::createActivityIndicator(tiObj);
        break;

    case N_TYPE_TOGGLEBUTTON:
        obj = NativeToggleButtonObject::createToggleButton(tiObj);
        break;

    case N_TYPE_DROPDOWN:
        obj = NativeDropDownObject::createDropDown(tiObj);
        break;

    case N_TYPE_LIST_VIEW:
        obj = NativeListViewObject::createListView(tiObj);
        break;

    case N_TYPE_LIST_ITEM:
        obj = new NativeListItemObject(tiObj);
        break;

    case N_TYPE_TAB:
        obj = NativeTabObject::createTab(tiObj);
        break;

    case N_TYPE_TABGROUP:
        obj = NativeTabGroupObject::createTabGroup(tiObj, this);
        break;

    case N_TYPE_TCPSOCKET:
        obj = NativeTCPSocketObject::createTCPSocket(tiObj);
        break;

    case N_TYPE_UDPSOCKET:
        obj = NativeUDPSocketObject::createUDPSocket(tiObj);
        break;

    case N_TYPE_HTTPCLIENT:
        obj = NativeHTTPClientObject::createHTTPClient(tiObj);
        break;

    case N_TYPE_SCROLL_VIEW:
        obj = NativeScrollViewObject::createScrollView(tiObj);
        break;

    case N_TYPE_SCROLLABLE_VIEW:
        obj = NativeScrollableViewObject::createScrollableView(tiObj);
        break;

    case N_TYPE_DB:
        obj = NativeDBObject::createDB(tiObj);
        break;

    case N_TYPE_RESULTSET:
        obj = NativeResultSetObject::createResultSet(tiObj);
        break;

    case N_TYPE_DATE_TIME_PICKER:
        obj = NativeDateTimePickerObject::createDateTimePicker(tiObj);
        break;

    case N_TYPE_ALERTDIALOG:
        obj = NativeAlertDialogObject::createAlertDialog(tiObj);
        break;

    case N_TYPE_VIEW:
        obj = NativeControlObject::createView(tiObj);
        break;

    case N_TYPE_WEBVIEW:
        obj = NativeWebViewObject::createWebView(tiObj);
        break;

    case N_TYPE_MAPVIEW:
        obj = NativeMapViewObject::createMapView(tiObj);
        break;

    case N_TYPE_ANNOTATION:
        obj = NativeAnnotationObject::createAnnotationObject(tiObj);
        break;

    case N_TYPE_AUDIOPLAYER:
        obj = NativeAudioPlayerObject::createAudioPlayerObject(tiObj);
        break;

    case N_TYPE_AUDIORECORDER:
		   obj = NativeAudioRecorderObject::createAudioRecorderObject(tiObj);
		   break;

    case N_TYPE_GESTURE:
       obj = NativeGestureObject::createGesture(tiObj);
       break;

    case N_TYPE_ACCELEROMETER:
        obj = new NativeAccelerometerObject(tiObj);
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
