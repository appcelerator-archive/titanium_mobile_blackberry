/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIBase.h"

#include "NativeControlObject.h"
#include "TiGenericFunctionObject.h"
#include "TiLogger.h"
#include "TiMessageStrings.h"
#include "TiPropertyGetFunctionObject.h"
#include "TiPropertyGetObject.h"
#include "TiPropertyMapObject.h"
#include "TiPropertySetFunctionObject.h"
#include "TiV8Event.h"
#include <ctype.h>
#include <string>

const static TiProperty g_tiProperties[] =
{
    {
        "active", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_ACTIVE
    },

    {
        "activeTab", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_ACTIVE_TAB
    },

    {
        "anchorPoint", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_ANCHOR_POINT
    },

    {
        "animatedCenterPoint", TI_PROP_PERMISSION_READ,
        N_PROP_ANIMATED_CENTER_POINT
    },

    {
        "autoLink", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_AUTO_LINK
    },

    {
        "backgroundImage", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_BACKGROUND_IMAGE
    },

    {
        "backgroundColor", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_BACKGROUND_COLOR
    },

    {
        "backgroundDisableColor", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_BACKGROUND_DISABLED_COLOR
    },

    {
        "bottom", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_BOTTOM
    },

    {
        "buttonNames", TI_PROP_PERMISSION_READ | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_BUTTONNAMES
    },

    {
        "cancel", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_CANCEL
    },

    {
        "color", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_COLOR
    },

    {
        "contentWidth", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_CONTENT_WIDTH
    },

    {
        "contentHeight", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_CONTENT_HEIGHT
    },

    {
        "data", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_DATA
    },

    {
        "enabled", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_ENABLED
    },

    {
        "font", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_FONT
    },

    {
        "height", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_HEIGHT
    },

    {
        "hintText", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_HINT_TEXT
    },

    {
        "icon", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_ICON
    },

    {
        "image", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_IMAGE
    },

    {
       "keyboardType", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
       N_PROP_KEYBOARD_TYPE
    },

    {
        "label", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_LABEL
    },

    {
        "layout", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_LAYOUT
    },

    {
        "left", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_LEFT
    },

    {
        "leftImage", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_LEFT_IMAGE
    },

    {
        "max", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_MAX
    },

    {
        "maxDate", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_MAXDATE
    },

    {
        "message", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_MESSAGE
    },

    {
        "min", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_MIN
    },

    {
        "minDate", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_MINDATE
    },

    {
        "opacity", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_OPACITY
    },

    {
        "options", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_OPTIONS
    },

    {
        "orientationModes", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_ORIENTATION_MODES
    },

    {
        "passwordMask", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_PASSWORD_MASK
    },

    {
        "rect", TI_PROP_PERMISSION_READ,
        N_PROP_RECT
    },

    {
        "right", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_RIGHT
    },

    {
        "selectedIndex", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_SELECTED_INDEX
    },

    {
        "size", TI_PROP_PERMISSION_READ,
        N_PROP_SIZE
    },

    {
        "text", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_TEXT
    },

    {
        "textAlign", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_TEXT_ALIGN
    },

    {
        "title", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_TITLE
    },

    {
        "top", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_TOP
    },

    {
        "type", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_TYPE
    },

    {
        "value", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_VALUE
    },

    {
        "visible", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_VISIBLE
    },

    {
        "width", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_WIDTH
    },

    {
        "window", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_WINDOW
    },

    {
        "zIndex", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_ZINDEX
    },

    {
		"url", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
		N_PROP_URL
	},

    // MapView properties
    {
		"mapType", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
		N_PROP_MAPTYPE
    },

    {
		"region", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
		N_PROP_REGION
    },

    {
		"annotations", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
		N_PROP_ANNOTATIONS
    },
    ////////////////////

    // Annotation properties
    {
		"pincolor", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
		N_PROP_PINCOLOR
	},

	{
		"latitude", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
		N_PROP_LATITUDE
	},

	{
		"longitude", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
		N_PROP_LONGITUDE
	},

	{
		"title", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
		N_PROP_TITLE
	},

	{
		"subtitle", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
		N_PROP_SUBTITLE
	},

	{
		"rightView", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
		N_PROP_RIGHTVIEW
	},

	{
		"leftView", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
		N_PROP_LEFTVIEW
	},
    /////////////////////


    // Media properties
    {
        "playing", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_PLAYING
    },

    {
        "paused", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_PAUSED
    },

    {
        "progress", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_PROGRESS
    },

    {
        "volume", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_VOLUME
    },
    /////////////////////

    {
        "willHandleTouches", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_WILL_HANDLE_TOUCHES
    },

    {
        "userAgent", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_USER_AGENT
    },

    {
        "showScrollbars", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_SHOW_SCROLL_BARS
    },

    {
        "scrollsToTop", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_SCROLLS_TO_TOP
    },

    {
        "scalesToFit", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_SCALES_TO_FIT
    },

    {
        "pluginState", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_PLUGIN_STATE
    },

    {
        "loading", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_LOADING
    },

    {
        "html", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_HTML
    },

    {
        "hideLoadIndicator", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_HIDE_LOAD_INDICATOR
    },

    {
        "enableZoomControls", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_ENABLE_ZOOM_CONTROLS
    },

    {
        "disableBounce", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE | TI_PROP_FLAG_READ_NO_BRIDGE,
        N_PROP_DISABLE_BOUNCE
    }

};

TiUIBase::TiUIBase()
{
}

TiUIBase::~TiUIBase()
{
    if (!createConfig_.IsEmpty())
    {
        createConfig_.Dispose();
    }
}

TiUIBase::TiUIBase(const char* name)
    : TiProxy(name)
{
}

TiUIBase* TiUIBase::createView(NativeObjectFactory* nativeObjectFactory)
{
    TiUIBase* obj = new TiUIBase("TiUIBase");
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);

    return obj;
}

void TiUIBase::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiProxy::initializeTiObject(parentContext);
        /* Don't create a native view object for derived classes */
        if (string("TiUIBase") == getName())
        {
            NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_VIEW, this);
            setNativeObject(obj);
            obj->release();
        }
    }
}


bool TiUIBase::isUIObject() const
{
    return true;
}

bool TiUIBase::canAddMembers() const
{
    return true;
}

/**
 * FIXME: This function has been duplicated in sibling classes with a modified
 * name (setTi*MappingProperties).  It should really be moved to a common parent
 * class (TiProxy) and shared amongst all classes needing it.  Also consider
 * sharing _valueModify and _getValue
 */
void TiUIBase::setTiMappingProperties(const TiProperty* props, int propertyCount)
{
    string name;
    char c[2];
    c[1] = 0;
    for (int i = 0; i < propertyCount; i++)
    {
        TiObject* value = TiPropertyMapObject::addProperty(this, props[i].propertyName, props[i].nativePropertyNumber,
                          (props[i].permissions & TI_PROP_FLAG_WRITE_NO_BRIDGE) ? NULL : _valueModify,
                          (props[i].permissions & TI_PROP_FLAG_READ_NO_BRIDGE) ? NULL : _getValue, this);
        // For all properties that have write permissions, add a setter method, e.g., myLabel.text=<my text>; myLabel.setText(<my text>);
        if (props[i].permissions & TI_PROP_PERMISSION_WRITE)
        {
            c[0] = toupper(props[i].propertyName[0]);
            name = "set";
            name += c;
            name += props[i].propertyName + 1;
            TiPropertySetFunctionObject::addPropertySetter(this, value, name.c_str());
        }
        // For all properties that have read permissions, add a getter method, e.g., var test=myLabel.text; var test=myLabel.getText();
        if (props[i].permissions & TI_PROP_PERMISSION_READ)
        {
            c[0] = toupper(props[i].propertyName[0]);
            name = "get";
            name += c;
            name += props[i].propertyName + 1;
            TiPropertyGetFunctionObject::addPropertyGetter(this, value, name.c_str());
        }
        value->release();
    }
}

void TiUIBase::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "add", this, _add);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "hide", this, _hide);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "remove", this, _remove);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "show", this, _show);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "startLayout", this, _startLayout);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "finishLayout", this, _finishLayout);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "updateLayout", this, _updateLayout);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "focus", this, _focus);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "blur", this, _blur);
    setTiMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));
    TiObject* value = TiPropertyGetObject::createGetProperty(this, "children", this, _getChildren);
    TiPropertyGetFunctionObject::addPropertyGetter(this, value, "getChildren");
    value->release();
}

Handle<Value> TiUIBase::_getValue(int propertyNumber, void* context)
{

    TiUIBase* self = (TiUIBase*) context;
    NativeObject* object = self->getNativeObject();
    TiObject value;
    if (object != NULL)
    {
        object->getPropertyValue(propertyNumber, &value);
    }
    return value.getValue();
}

VALUE_MODIFY TiUIBase::_valueModify(int propertyNumber, TiObject* value, void* context)
{
    TiUIBase* self = (TiUIBase*) context;
    NativeObject* object = self->getNativeObject();
    if (object == NULL)
    {
        return VALUE_MODIFY_NOT_SUPPORTED;
    }
    VALUE_MODIFY modify = VALUE_MODIFY_ALLOW;
    switch (object->setPropertyValue(propertyNumber, value))
    {
    case NATIVE_ERROR_OK:
        modify = VALUE_MODIFY_ALLOW;
        break;
    case NATIVE_ERROR_NOTSUPPORTED:
        modify = VALUE_MODIFY_NOT_SUPPORTED;
        break;
    default:
        modify = VALUE_MODIFY_INVALID;
        break;
    }
    object->release();
    return modify;
}

Handle<Value> TiUIBase::_add(void* userContext, TiObject*, const Arguments& args)
{
    HandleScope handleScope;
    TiUIBase* obj = (TiUIBase*) userContext;
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        TiObject* addObj = getTiObjectFromJsObject(args[0]);
        if ((addObj == NULL) || (!addObj->isUIObject()))
        {
            return ThrowException(String::New(Ti::Msg::Invalid_add_argument));
        }
        TiUIBase* uiObj = (TiUIBase*) addObj;
        NativeObject* childNO = uiObj->getNativeObject();
        if (childNO == NULL)
        {
            return ThrowException(String::New(Ti::Msg::Invalid_add_argument));
        }
        NativeObject* parentNO = obj->getNativeObject();
        if (N_SUCCEEDED(parentNO->addChildNativeObject(childNO)))
        {
            ObjectEntry entry = addObj;
            obj->childControls_.push_back(entry);
        }
        childNO->release();
        parentNO->release();
    }
    else
    {
        // TODO: expand this exception
    }
    return Undefined();
}

Handle<Value> TiUIBase::_hide(void* userContext, TiObject*, const Arguments&)
{
    TiUIBase* obj = (TiUIBase*) userContext;
    NativeObject* no = obj->getNativeObject();
    no->setVisibility(false);
    no->release();
    return Undefined();
}

Handle<Value> TiUIBase::_remove(void* userContext, TiObject*, const Arguments& args)
{
    HandleScope handleScope;
    // JavaScript usage:
    //
    // arg[0] = Titanium.UI.View
    //
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsObject())
    {
        return ThrowException(String::New(Ti::Msg::Invalid_remove_argument));
    }

    TiUIBase* obj = (TiUIBase*) userContext;
    TiObject* removeObject = TiObject::getTiObjectFromJsObject(args[0]);
    if (removeObject == NULL)
    {
        return ThrowException(String::New(Ti::Msg::Invalid_remove_argument));
    }
    NativeObject* parentControl = obj->getNativeObject();
    if (parentControl == NULL)
    {
        return ThrowException(String::New(Ti::Msg::INTERNAL__Missing_native_object));
    }
    vector<ObjectEntry>::const_iterator it;
    bool foundChild = false;
    for (it = obj->childControls_.begin(); it != obj->childControls_.end(); it++)
    {
        if ((*it).isSameInstance(removeObject))
        {
            NativeObject* childControl = (*it)->getNativeObject();
            if (childControl == NULL)
            {
                parentControl->release();
                return ThrowException(String::New(Ti::Msg::INTERNAL__Missing_native_object));
            }
            parentControl->removeChildNativeObject(childControl);
            childControl->release();
            foundChild = true;
            break;
        }
    }
    parentControl->release();
    if (!foundChild)
    {
        TI_WARNING(Ti::Msg::Remove_child_warning);
    }
    return Undefined();
}

Handle<Value> TiUIBase::_getChildren(void* userContext)
{
    TiUIBase* obj = (TiUIBase*) userContext;
    Handle<Array> array = Array::New(obj->childControls_.size());
    int i = 0;
    vector<ObjectEntry>::const_iterator it;
    for (it = obj->childControls_.begin(); it != obj->childControls_.end(); it++)
    {
        array->Set(Integer::New(i++), (*it)->getValue());
    }
    return array;
}

Handle<Value> TiUIBase::_show(void* userContext, TiObject*, const Arguments&)
{
    TiUIBase* obj = (TiUIBase*) userContext;
    NativeObject* no = obj->getNativeObject();
    no->setVisibility(true);
    return Undefined();
}

Handle<Value> TiUIBase::_startLayout(void* userContext, TiObject*, const Arguments&)
{
    TiUIBase* obj = (TiUIBase*) userContext;
    NativeObject* no = obj->getNativeObject();
    no->startLayout();
    return Undefined();
}

Handle<Value> TiUIBase::_finishLayout(void* userContext, TiObject*, const Arguments&)
{
    TiUIBase* obj = (TiUIBase*) userContext;
    NativeObject* no = obj->getNativeObject();
    no->finishLayout();
    return Undefined();
}

Handle<Value> TiUIBase::_updateLayout(void* userContext, TiObject*, const Arguments& args)
{
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        TiUIBase* obj = (TiUIBase*) userContext;
        obj->setParametersFromObject(obj, settingsObj);
    }
    return Undefined();
}

Handle<Value> TiUIBase::_focus(void* userContext, TiObject* caller, const Arguments& args)
{
    TiUIBase* obj = static_cast<TiUIBase*>(userContext);
    NativeControlObject* control = static_cast<NativeControlObject*>(obj->getNativeObject());
    control->focus();
    return Undefined();
}

Handle<Value> TiUIBase::_blur(void* userContext, TiObject* caller, const Arguments& args)
{
    TiUIBase* obj = static_cast<TiUIBase*>(userContext);
    NativeControlObject* control = static_cast<NativeControlObject*>(obj->getNativeObject());
    control->blur();
    return Undefined();
}

