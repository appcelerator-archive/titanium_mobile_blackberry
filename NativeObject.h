/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEOBJECT_H_
#define NATIVEOBJECT_H_

typedef void* NAHANDLE;

#define NATIVE_ERROR_OK                         0
#define NATIVE_ERROR_NOTSUPPORTED               1
#define NATIVE_ERROR_OUTOFMEMORY                2
#define NATIVE_ERROR_INVALID_ARG                3

#define N_TYPE_CONTAINER                        1
#define N_TYPE_WINDOW                           2
#define N_TYPE_LABEL                            3
#define N_TYPE_BUTTON                           4
#define N_TYPE_SLIDER                           5
#define N_TYPE_PROGRESSBAR                      6
#define N_TYPE_IMAGEVIEW                        7
#define N_TYPE_TEXT_FIELD                       8

#define N_PROP_SET_UNDEFINED                    0
#define N_PROP_SET_ANCHOR_POINT                 1
#define N_PROP_SET_ANIMATED_CENTER_POINT        2
#define N_PROP_SET_BACKGROUND_COLOR             3
#define N_PROP_SET_BACKGROUND_DISABLED_COLOR    4
#define N_PROP_SET_BACKGROUND_DISABLED_IMAGE    5
#define N_PROP_SET_BACKGROUND_FOCUSED_COLOR     6
#define N_PROP_SET_LABEL                        7
#define N_PROP_SET_MAX                          8
#define N_PROP_SET_MIN                          9
#define N_PROP_SET_TEXT                         10
#define N_PROP_SET_TEXT_ALIGN                   11
#define N_PROP_SET_TOP                          12
#define N_PROP_SET_VALUE                        13
#define N_PROP_SET_IMAGE                        14
#define N_PROP_SET_WIDTH                        15
#define N_PROP_SET_HEIGHT                       16
#define N_PROP_SET_LEFT                         17
#define N_PROP_SET_HINT_TEXT                    18


class NativeObjectFactory;
class TiEvent;
class TiEventContainerFactory;

#include "TiEventContainer.h"
#include "TiBase.h"

/*
 * NativeObject
 *
 * Abstract class that represents a native object. A
 * native object represents an object that has been
 * implemented for a specific platform
 * such as a button, label, file, etc...
 */
class NativeObject :
    public TiBase
{
public:
    virtual int getObjectType() const = 0;
    virtual int setPropertyValue(int propertyNumber, const char* value);
    virtual int addChildNativeObject(NativeObject* obj);
    virtual NAHANDLE getNativeHandle() const;
    virtual int open();
    virtual void completeInitialization();
    virtual bool isInitializationComplete() const;
    virtual int setEventHandler(const char* eventName, TiEvent* event);

protected:
    NativeObject();
    virtual ~NativeObject();
    virtual int initialize(TiEventContainerFactory* containerFactory);
    friend class NativeObjectFactory;

private:
    bool isInitializationComplete_;
};

#endif /* NATIVEOBJECT_H_ */
