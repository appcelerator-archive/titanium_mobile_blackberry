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

#define N_PROP_UNDEFINED                        0
#define N_PROP_ANCHOR_POINT                     1
#define N_PROP_ANIMATED_CENTER_POINT            2
#define N_PROP_BACKGROUND_COLOR                 3
#define N_PROP_BACKGROUND_DISABLED_COLOR        4
#define N_PROP_BACKGROUND_DISABLED_IMAGE        5
#define N_PROP_BACKGROUND_FOCUSED_COLOR         6
#define N_PROP_BACKGROUND_FOCUSED_IMAGE         7
#define N_PROP_BACKGROUND_GRADIANT              8
#define N_PROP_BACKGROUND_IMAGE                 9
#define N_PROP_BACKGROUND_LEFT_CAP              10
#define N_PROP_BACKGROUND_PADDING_BOTTOM        11
#define N_PROP_BACKGROUND_PADDING_LEFT          12
#define N_PROP_BACKGROUND_PADDING_RIGHT         13
#define N_PROP_BACKGROUND_PADDING_TOP           14
#define N_PROP_BACKGROUND_REPEAT                15
#define N_PROP_BACKGROUND_SELECTED_COLOR        16
#define N_PROP_BACKGROUND_SELECTED_IMAGE        17
#define N_PROP_BACKGROUND_TOP_CAP               18
#define N_PROP_BORDER_COLOR                     19
#define N_PROP_BORDER_RADIUS                    20
#define N_PROP_BORDER_WIDTH                     21
#define N_PROP_BOTTOM                           22
#define N_PROP_CENTER                           23
#define N_PROP_CHILDREN                         24
#define N_PROP_COLOR                            25
#define N_PROP_ELLIPSIZE                        26
#define N_PROP_FOCUSABLE                        27
#define N_PROP_FONT                             28
#define N_PROP_HEIGHT                           29
#define N_PROP_HIGHLIGHTED_COLOR                30
#define N_PROP_HTML                             31
#define N_PROP_KEEP_SCREEN_ON                   32
#define N_PROP_LAYOUT                           33
#define N_PROP_LEFT                             34
#define N_PROP_MAX                              35
#define N_PROP_MIN                              36
#define N_PROP_MINIMUM_FONT_SIZE                37
#define N_PROP_OPACITY                          38
#define N_PROP_RIGHT                            39
#define N_PROP_SHADOW_COLOR                     40
#define N_PROP_SHADOW_OFFSET                    41
#define N_PROP_SIZE                             42
#define N_PROP_SOFT_KEYBOARD_ON_FOCUS           43
#define N_PROP_TEXT                             44
#define N_PROP_TEXT_ALIGN                       45
#define N_PROP_TEXT_ID                          46
#define N_PROP_TOP                              47
#define N_PROP_TOUCH_ENABLED                    48
#define N_PROP_TRANSFORM                        49
#define N_PROP_VALUE                            50
#define N_PROP_VISIBLE                          51
#define N_PROP_WIDTH                            52
#define N_PROP_WORD_WRAP                        53
#define N_PROP_ZINDEX                           54

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
    virtual int getObjectType() const=0;
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
