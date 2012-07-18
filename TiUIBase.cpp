/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIBase.h"
#include "TiLogger.h"
#include "TiGenericFunctionObject.h"
#include "TiPropertySetFunctionObject.h"
#include "TiPropertyGetFunctionObject.h"
#include "TiPropertyMapObject.h"
#include "TiPropertyGetObject.h"
#include "TiV8Event.h"
#include "TiMessageStrings.h"
#include <string>
#include <ctype.h>

const static TiProperty g_tiProperties[] =
{
    {
        "anchorPoint", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_ANCHOR_POINT
    },

    {
        "animatedCenterPoint", TI_PROP_PERMISSION_READ,
        N_PROP_ANIMATED_CENTER_POINT
    },

    {
        "autoLink", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_AUTO_LINK
    },

    {
        "backgroundColor", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_BACKGROUND_COLOR
    },

    {
        "bottom", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_BOTTOM
    },

    {
        "backgroundDisableColor", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_BACKGROUND_DISABLED_COLOR
    },

    {
        "color", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_COLOR
    },

    {
        "font", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_FONT
    },

    {
        "height", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_HEIGHT
    },

    {
        "hintText", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_HINT_TEXT
    },

    {
        "icon", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_ICON
    },

    {
        "image", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_IMAGE
    },

    {
        "data", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_DATA
    },

    {
        "enabled", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_ENABLED
    },

    {
        "label", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_LABEL
    },

    {
        "left", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_LEFT
    },

    {
        "max", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_MAX
    },

    {
        "maxDate", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_MAXDATE
    },

    {
        "message", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_MESSAGE
    },

    {
        "min", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_MIN
    },

    {
        "minDate", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_MINDATE
    },

    {
        "options", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_OPTIONS
    },

    {
        "right", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_RIGHT
    },

    {
        "selectedIndex", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_SELECTED_INDEX
    },

    {
        "opacity", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_OPACITY
    },

    {
        "text", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_TEXT
    },

    {
        "textAlign", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_TEXT_ALIGN
    },

    {
        "title", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_TITLE
    },

    {
        "top", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_TOP
    },

    {
        "type", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_TYPE
    },

    {
        "value", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_VALUE
    },

    {
        "visible", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_VISIBLE
    },

    {
        "width", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_WIDTH
    },

    {
        "window", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_WINDOW
    },

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

bool TiUIBase::isUIObject() const
{
    return true;
}

bool TiUIBase::canAddMembers() const
{
    return true;
}

void TiUIBase::setTiMappingProperties(const TiProperty* props, int propertyCount)
{
    string name;
    char c[2];
    c[1] = 0;
    for (int i = 0; i < propertyCount; i++)
    {
        TiObject* value = TiPropertyMapObject::addProperty(this, props[i].propertyName, props[i].nativePropertyNumber,
                          _valueModify, this);
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
    setTiMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));
    TiObject* value = TiPropertyGetObject::createGetProperty(this, "children", this, _getChildren);
    TiPropertyGetFunctionObject::addPropertyGetter(this, value, "getChildren");
    value->release();
}

void TiUIBase::setParametersFromObject(void* userContext, Local<Object> obj)
{
    HandleScope handleScope;
    Handle<Value> value;
    Handle<Value> controlValue = getValue();
    if (!controlValue->IsObject())
    {
        return;
    }
    Handle<Array> propNames = obj->GetPropertyNames();
    uint32_t props = propNames->Length();
    Local<Value> propValue;
    for (uint32_t i = 0; i < props; i++)
    {
        Handle<String> propString = Handle<String>::Cast(propNames->Get(Integer::New(i)));
        String::Utf8Value propNameUTF(propString);
        TiObject* foundProp = onLookupMember(*propNameUTF);
        if (foundProp != NULL)
        {
            Local<Value> propValue = obj->Get(propString);
            TiObject* addObj = getTiObjectFromJsObject(propValue);
            if (addObj)
            {
                TiUIBase* obj = (TiUIBase*) userContext;
                TiUIBase* uiObj = (TiUIBase*) addObj;
                NativeObject* childNO = uiObj->getNativeObject();
                NativeObject* parentNO = obj->getNativeObject();
                parentNO->addChildNativeObject(childNO);
                parentNO->release();
            }
            else
            {
                foundProp->setValue(propValue);
            }
        }
    }
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
