/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEOBJECT_H_
#define NATIVEOBJECT_H_

typedef void* NAHANDLE;

enum NATIVE_ERROR
{
    NATIVE_ERROR_OK
    , NATIVE_ERROR_NOTSUPPORTED
    , NATIVE_ERROR_OUTOFMEMORY
    , NATIVE_ERROR_INVALID_ARG
};

enum NATIVE_TYPE
{
    N_TYPE_UNDEFINED
    , N_TYPE_ACTIVITYINDICATOR
    , N_TYPE_ALERTDIALOG
    , N_TYPE_BLOB
    , N_TYPE_BUFFER
    , N_TYPE_BUTTON
    , N_TYPE_DATE_TIME_PICKER
    , N_TYPE_DROPDOWN
    , N_TYPE_IMAGEVIEW
    , N_TYPE_LABEL
    , N_TYPE_LIST_VIEW
    , N_TYPE_LIST_ITEM
    , N_TYPE_LOGGER
    , N_TYPE_PROGRESSBAR
    , N_TYPE_SLIDER
    , N_TYPE_TAB
    , N_TYPE_TABGROUP
    , N_TYPE_TCPSOCKET
    , N_TYPE_UDPSOCKET
    , N_TYPE_HTTPCLIENT
    , N_TYPE_SCROLL_VIEW
    , N_TYPE_SCROLLABLE_VIEW
    , N_TYPE_TEXT_FIELD
    , N_TYPE_TEXT_AREA
    , N_TYPE_TOGGLEBUTTON
    , N_TYPE_VIEW
    , N_TYPE_WEBVIEW
    , N_TYPE_MAPVIEW
    , N_TYPE_AUDIOPLAYER
    , N_TYPE_AUDIORECORDER
    , N_TYPE_ANNOTATION
    , N_TYPE_WINDOW
    , N_TYPE_DB
    , N_TYPE_RESULTSET
    // ScrollableView
};

enum NATIVE_PROP
{
    N_PROP_UNDEFINED
    , N_PROP_ACTIVE
    , N_PROP_ACTIVE_TAB
    , N_PROP_ANCHOR_POINT
    , N_PROP_ANIMATED_CENTER_POINT
    , N_PROP_AUTO_LINK
    , N_PROP_BACKGROUND_COLOR
    , N_PROP_BACKGROUND_DISABLED_COLOR
    , N_PROP_BACKGROUND_DISABLED_IMAGE
    , N_PROP_BACKGROUND_FOCUSED_COLOR
    , N_PROP_BACKGROUND_FOCUSED_IMAGE
    , N_PROP_BACKGROUND_GRADIANT
    , N_PROP_BACKGROUND_IMAGE
    , N_PROP_BACKGROUND_LEFT_CAP
    , N_PROP_BACKGROUND_PADDING_BOTTOM
    , N_PROP_BACKGROUND_PADDING_LEFT
    , N_PROP_BACKGROUND_PADDING_RIGHT
    , N_PROP_BACKGROUND_PADDING_TOP
    , N_PROP_BACKGROUND_REPEAT
    , N_PROP_BACKGROUND_SELECTED_COLOR
    , N_PROP_BACKGROUND_SELECTED_IMAGE
    , N_PROP_BACKGROUND_TOP_CAP
    , N_PROP_BORDER_COLOR
    , N_PROP_BORDER_RADIUS
    , N_PROP_BORDER_WIDTH
    , N_PROP_BOTTOM
    , N_PROP_BUTTONNAMES
    , N_PROP_CANCEL
    , N_PROP_CENTER
    , N_PROP_CHILDREN
    , N_PROP_COLOR
    , N_PROP_CONTENT_HEIGHT
    , N_PROP_CONTENT_WIDTH
    , N_PROP_DATA
    , N_PROP_ELLIPSIZE
    , N_PROP_ENABLED
    , N_PROP_FOCUSABLE
    , N_PROP_FONT
    , N_PROP_HEIGHT
    , N_PROP_HIGHLIGHTED_COLOR
    , N_PROP_HINT_TEXT
    , N_PROP_ICON
    , N_PROP_IMAGE
    , N_PROP_KEYBOARD_TYPE
    , N_PROP_KEEP_SCREEN_ON
    , N_PROP_LABEL
    , N_PROP_LAYOUT
    , N_PROP_LEFT
    , N_PROP_LEFT_IMAGE
    , N_PROP_MAX
    , N_PROP_MAXDATE
    , N_PROP_MESSAGE
    , N_PROP_MIN
    , N_PROP_MINDATE
    , N_PROP_MINIMUM_FONT_SIZE
    , N_PROP_OPACITY
    , N_PROP_OPTIONS
    , N_PROP_ORIENTATION_MODES
    , N_PROP_PASSWORD_MASK
    , N_PROP_RECT
    , N_PROP_RIGHT
    , N_PROP_SELECTED_INDEX
    , N_PROP_SHADOW_COLOR
    , N_PROP_SHADOW_OFFSET
    , N_PROP_SIZE
    , N_PROP_SOFT_KEYBOARD_ON_FOCUS
    , N_PROP_TABS
    , N_PROP_TEXT
    , N_PROP_TEXT_ALIGN
    , N_PROP_TEXT_ID
    , N_PROP_TITLE
    , N_PROP_TOP
    , N_PROP_TOUCH_ENABLED
    , N_PROP_TRANSFORM
    , N_PROP_TYPE
    , N_PROP_VALUE
    , N_PROP_VISIBLE
    , N_PROP_WIDTH
    , N_PROP_WINDOW
    , N_PROP_WORD_WRAP
    , N_PROP_ZINDEX
    , N_PROP_URL
    // MapView properties
    , N_PROP_MAPTYPE
    , N_PROP_REGION
    , N_PROP_ANNOTATIONS
    /////////////////////
    // Annotation properties
    , N_PROP_PINCOLOR
    , N_PROP_LATITUDE
    , N_PROP_LONGITUDE
    //, N_PROP_TITLE
    , N_PROP_SUBTITLE
    , N_PROP_LEFTVIEW
    , N_PROP_RIGHTVIEW
    ////////////////////////
     // Media properties
    , N_PROP_PLAYING
    , N_PROP_PAUSED
    , N_PROP_RECORDING
    , N_PROP_PROGRESS
    , N_PROP_BITRATE
    , N_PROP_REPEATMODE
    , N_PROP_VOLUME
    ////////////////////////
    //TODO: need to place alphabetically
    , N_PROP_ENABLE_ZOOM_CONTROLS
    , N_PROP_HIDE_LOAD_INDICATOR
    , N_PROP_HTML
    , N_PROP_LOADING
    , N_PROP_PLUGIN_STATE
    , N_PROP_SCALES_TO_FIT
    , N_PROP_SCROLLS_TO_TOP
    , N_PROP_SHOW_SCROLL_BARS
    , N_PROP_USER_AGENT
    , N_PROP_WILL_HANDLE_TOUCHES
    // ScrollableView
    , N_PROP_CURRENT_PAGE
    , N_PROP_DISABLE_BOUNCE
    , N_PROP_OVER_SCROLL_MODE
    , N_PROP_OVERLAY_ENABLED
    , N_PROP_PAGING_CONTROL_ALPHA
    , N_PROP_PAGING_CONTROL_COLOR
    , N_PROP_PAGING_CONTROL_HEIGHT
    , N_PROP_PAGING_CONTROL_ON_TOP
    , N_PROP_PAGING_CONTROL_TIMEOUT
    , N_PROP_SCROLLING_ENABLED
    , N_PROP_SHOW_PAGING_CONTROL
    , N_PROP_VIEWS

    /* This MUST be the last element */
    , N_PROP_LAST
};


#include "TiBase.h"
#include <cstddef>

class NativeObjectFactory;
class TiEvent;
class TiEventContainerFactory;
class TiObject;

#define N_SUCCEEDED(x)          ((x)==NATIVE_ERROR_OK)


/*
 * NativeObject
 *
 * Abstract class that represents a native object. A native object represents an
 * object that has been implemented for a specific platform such as a button,
 * label, file, etc...  The NativeObjects are implemented in terms of the
 * Cascades SDK.
 *
 * This class aims at limiting the coupling between the Ti layer and the Native
 * layer by having the Ti layer interact with it and not needing to know the 
 * specializations.  NativeObjects are created using the NativeObjectFactoryi
 * singleton.
 */
class NativeObject : public TiBase
{
public:
    virtual NATIVE_TYPE getObjectType() const = 0;
    virtual int setPropertyValue(std::size_t propertyNumber, TiObject* obj);
    virtual int getPropertyValue(std::size_t propertyNumber, TiObject* obj);
    virtual int addChildNativeObject(NativeObject* obj);
    virtual NAHANDLE getNativeHandle() const;
    virtual int finishLayout();
    virtual int start();
    virtual int startLayout();
    virtual int stop();
    virtual int openWindowOnTab(NativeObject* obj);
    virtual void completeInitialization();
    virtual bool isInitializationComplete() const;
    virtual int setEventHandler(const char* eventName, TiEvent* event);
    virtual int scrollToIndex(int index);
    virtual int setActiveTab(NativeObject* tab);
    virtual int setActiveTab(int index);
    virtual int removeChildNativeObject(NativeObject* obj);
    virtual int removeEventHandler(const char* eventName, int eventId);
    virtual int setVisibility(bool visible);
    virtual int fireEvent(const char* name, const TiObject* event) const;

protected:
    explicit NativeObject(TiObject* tiObject);
    virtual ~NativeObject();

    virtual int initialize();
    virtual void setupEvents(TiEventContainerFactory* containerFactory);
    friend class NativeObjectFactory;

    TiObject* tiObject_;

private:
    // Disable copy ctor & assignment operator
    NativeObject(const NativeObject&);
    void operator=(const NativeObject&);

    bool isInitializationComplete_;
};

#endif /* NATIVEOBJECT_H_ */
