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
#define N_TYPE_ACTIVITYINDICATOR                9

#define N_PROP_UNDEFINED                        0
#define N_PROP_ANCHOR_POINT                     1
#define N_PROP_ANIMATED_CENTER_POINT            2
#define N_PROP_AUTO_LINK                        3
#define N_PROP_BACKGROUND_COLOR                 4
#define N_PROP_BACKGROUND_DISABLED_COLOR        5
#define N_PROP_BACKGROUND_DISABLED_IMAGE        6
#define N_PROP_BACKGROUND_FOCUSED_COLOR         7
#define N_PROP_BACKGROUND_FOCUSED_IMAGE         8
#define N_PROP_BACKGROUND_GRADIANT              9
#define N_PROP_BACKGROUND_IMAGE                 10
#define N_PROP_BACKGROUND_LEFT_CAP              11
#define N_PROP_BACKGROUND_PADDING_BOTTOM        12
#define N_PROP_BACKGROUND_PADDING_LEFT          13
#define N_PROP_BACKGROUND_PADDING_RIGHT         14
#define N_PROP_BACKGROUND_PADDING_TOP           15
#define N_PROP_BACKGROUND_REPEAT                16
#define N_PROP_BACKGROUND_SELECTED_COLOR        17
#define N_PROP_BACKGROUND_SELECTED_IMAGE        18
#define N_PROP_BACKGROUND_TOP_CAP               19
#define N_PROP_BORDER_COLOR                     20
#define N_PROP_BORDER_RADIUS                    21
#define N_PROP_BORDER_WIDTH                     22
#define N_PROP_BOTTOM                           23
#define N_PROP_CENTER                           24
#define N_PROP_CHILDREN                         25
#define N_PROP_COLOR                            26
#define N_PROP_ELLIPSIZE                        27
#define N_PROP_FOCUSABLE                        28
#define N_PROP_FONT                             29
#define N_PROP_HEIGHT                           30
#define N_PROP_HIGHLIGHTED_COLOR                31
#define N_PROP_HINT_TEXT                        32
#define N_PROP_HTML                             33
#define N_PROP_IMAGE                            34
#define N_PROP_KEEP_SCREEN_ON                   35
#define N_PROP_LABEL                            36
#define N_PROP_LAYOUT                           37
#define N_PROP_LEFT                             38
#define N_PROP_MAX                              39
#define N_PROP_MIN                              40
#define N_PROP_MINIMUM_FONT_SIZE                41
#define N_PROP_OPACITY                          42
#define N_PROP_RIGHT                            43
#define N_PROP_SHADOW_COLOR                     44
#define N_PROP_SHADOW_OFFSET                    45
#define N_PROP_SIZE                             46
#define N_PROP_SOFT_KEYBOARD_ON_FOCUS           47
#define N_PROP_TEXT                             48
#define N_PROP_TEXT_ALIGN                       49
#define N_PROP_TEXT_ID                          50
#define N_PROP_TOP                              51
#define N_PROP_TOUCH_ENABLED                    52
#define N_PROP_TRANSFORM                        53
#define N_PROP_VALUE                            54
#define N_PROP_VISIBLE                          55
#define N_PROP_WIDTH                            56
#define N_PROP_WORD_WRAP                        57
#define N_PROP_ZINDEX                           58

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
