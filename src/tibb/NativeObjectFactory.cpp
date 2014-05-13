/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeObjectFactory.h"

#include "NativeAccelerometerObject.h"
#include "NativeActivityIndicatorObject.h"
#include "NativeBlobObject.h"
#include "NativeBufferObject.h"
#include "NativeImageButtonObject.h"
#include "NativeDateTimePickerObject.h"
#include "NativeDropDownObject.h"
#include "NativeGestureObject.h"
#include "NativeProgressBarObject.h"
#include "NativeStringInterface.h"
#include "NativeTCPSocketObject.h"
#include "NativeUDPSocketObject.h"
#include "NativeHTTPClientObject.h"
#include "NativeDBObject.h"
#include "NativeResultSetObject.h"
#include "NativeMapViewObject.h"
#include "NativeAnnotationObject.h"
#include "NativeAudioPlayerObject.h"
#include "NativeAudioRecorderObject.h"
#include "NativeVideoPlayerObject.h"
#include "NativeAnimationObject.h"
#include "NativeEmailDialogObject.h"
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
    case N_TYPE_BLOB:
        obj = NativeBlobObject::createBlob(tiObj);
        break;

    case N_TYPE_BUFFER:
        obj = NativeBufferObject::createBuffer(tiObj);
        break;

    case N_TYPE_IMAGE_BUTTON:
        obj = NativeImageButtonObject::createButton(tiObj);
        break;

    case N_TYPE_PROGRESSBAR:
        obj = NativeProgressBarObject::createProgressBar(tiObj);
        break;

    case N_TYPE_ACTIVITYINDICATOR:
        obj = NativeActivityIndicatorObject::createActivityIndicator(tiObj);
        break;

    case N_TYPE_EMAILDIALOG:
        obj = NativeEmailDialogObject::createEmailDialog(tiObj);
        break;

    case N_TYPE_DROPDOWN:
        obj = NativeDropDownObject::createDropDown(tiObj);
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

    case N_TYPE_DB:
        obj = NativeDBObject::createDB(tiObj);
        break;

    case N_TYPE_RESULTSET:
        obj = NativeResultSetObject::createResultSet(tiObj);
        break;

    case N_TYPE_DATE_TIME_PICKER:
        obj = NativeDateTimePickerObject::createDateTimePicker(tiObj);
        break;

    case N_TYPE_VIEW:
        obj = NativeControlObject::createView(tiObj);
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

    case N_TYPE_VIDEOPLAYER:
		obj = NativeVideoPlayerObject::createVideoPlayerObject(tiObj);
		break;

    case N_TYPE_GESTURE:
       obj = NativeGestureObject::createGesture(tiObj);
       break;

    case N_TYPE_ANIMATION:
           obj = NativeAnimationObject::createAnimation(tiObj);
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
