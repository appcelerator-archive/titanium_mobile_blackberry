/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIBase.h"
#include "TiGenericFunctionObject.h"
#include "TiPropertySetFunctionObject.h"
#include "TiPropertyGetFunctionObject.h"
#include "TiPropertyMapObject.h"
#include "TiV8Event.h"
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
        "min", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_MIN
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
        "width", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE,
        N_PROP_WIDTH
    }
};

TiUIBase::TiUIBase()
{
    nativeObjectFactory_ = NULL;
    nativeObject_ = NULL;
}

TiUIBase::~TiUIBase()
{
    if (!createConfig_.IsEmpty())
    {
        createConfig_.Dispose();
    }
    if (nativeObject_ != NULL)
    {
        nativeObject_->release();
        nativeObject_ = NULL;
    }
}

TiUIBase::TiUIBase(NativeObjectFactory* nativeObjectFactory, const char* name)
    : TiObject(name)
{
    nativeObjectFactory_ = nativeObjectFactory;
    nativeObject_ = NULL;
}

void TiUIBase::onStartMessagePump()
{
    if (nativeObject_ != NULL)
    {
        nativeObject_->completeInitialization();
    }
    TiObject::onStartMessagePump();
}

bool TiUIBase::isUIObject() const
{
    return true;
}

NativeObjectFactory* TiUIBase::getNativeObjectFactory() const
{
    return nativeObjectFactory_;
}

bool TiUIBase::canAddMembers() const
{
    return true;
}

NativeObject* TiUIBase::getNativeObject() const
{
    if (nativeObject_ != NULL)
    {
        nativeObject_->addRef();
    }
    return nativeObject_;
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

void TiUIBase::setNativeObject(NativeObject* nativeObject)
{
    if (nativeObject != NULL)
    {
        nativeObject->addRef();
    }
    if (nativeObject_ != NULL)
    {
        nativeObject_->release();
    }
    nativeObject_ = nativeObject;
}

void TiUIBase::onCreateStaticMembers()
{
    TiObject::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "add", this, _add);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "addEventListener", this, _addEventListener);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "hide", this, _hide);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "removeEventListener", this, _removeEventListener);
    setTiMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));
}

void TiUIBase::setParametersFromObject(Local<Object> obj)
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
            foundProp->setValue(propValue);
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

void TiUIBase::onAddEventListener(const char* eventName, Handle<Function> eventFunction)
{
    HandleScope handleScope;
    NativeObject* no = getNativeObject();
    if (no == NULL)
    {
        return;
    }
    Handle<Object> source = Handle<Object>::Cast(getValue());
    TiV8Event* event = TiV8Event::createEvent(eventName, eventFunction, source);
    no->setEventHandler(eventName, event);
    int id = event->getId();
    eventFunction->SetHiddenValue(String::New("_event_ptr_"), External::New(event));
    eventFunction->SetHiddenValue(String::New("_event_id_"), Integer::New(id));
}

void TiUIBase::onRemoveEventListener(const char* eventName, Handle<Function> eventFunction)
{
    HandleScope handleScope;
    NativeObject* no = getNativeObject();
    if (no == NULL)
    {
        return;
    }
    // Get the event subscriber's id so we know which to remove from the event container.
    Handle<Int32> v8id = eventFunction->GetHiddenValue(String::New("_event_id_"))->ToInt32();
    if ((v8id.IsEmpty()) || (v8id->Value() == 0))
    {
        return;
    }
    // Make sure that the function being removed has been added to this event container.
    Handle<Value> v8extValue = eventFunction->GetHiddenValue(String::New("_event_ptr_"));
    if ((!v8extValue.IsEmpty()) || (!v8extValue->IsExternal()))
    {
        return;
    }
    Handle<External> v8ext = Handle<External>::Cast(v8extValue);
    TiUIBase* referencedControl = (TiUIBase*)v8ext->Value();
    if (referencedControl != this)
    {
        // User was attempting to remove an event handler from a control that it
        // doesn't belong to.
        return;
    }
    no->removeEventHandler(v8id->Value());
}

Handle<Value> TiUIBase::_add(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIBase* obj = (TiUIBase*) userContext;
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        TiObject* addObj = getTiObjectFromJsObject(args[0]);
        if ((addObj == NULL) || (!addObj->isUIObject()))
        {
            return Undefined();
        }
        TiUIBase* uiObj = (TiUIBase*) addObj;
        NativeObject* childNO = uiObj->getNativeObject();
        NativeObject* parentNO = obj->getNativeObject();
        parentNO->addChildNativeObject(childNO);
        childNO->release();
        parentNO->release();
    }
    else
    {
        // TODO: expand this exception
    }
    return Undefined();
}

Handle<Value> TiUIBase::_addEventListener(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    // JavaScript usage:
    //
    // arg[0] = event name (string)
    // arg[1] = event function (function)
    //
    // myobject.addEventListener('myevent',function(e) {...});
    //
    if ((args.Length() != 2) || (!args[0]->IsString()) || (!args[1]->IsFunction()))
    {
        return Undefined();
    }
    TiUIBase* obj = (TiUIBase*) userContext;
    Handle<String> eventName = Handle<String>::Cast(args[0]);
    Handle<Function> func = Handle<Function>::Cast(args[1]);
    String::Utf8Value eventNameUTF(eventName);
    obj->onAddEventListener(*eventNameUTF, func);
    return Undefined();
}

Handle<Value> TiUIBase::_hide(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIBase* obj = (TiUIBase*) userContext;
    NativeObject* no = obj->getNativeObject();
    no->setVisibility(false);
    return Undefined();
}

Handle<Value> TiUIBase::_removeEventListener(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    // JavaScript usage:
    //
    // arg[0] = event name (string)
    // arg[1] = event function (function)
    //
    // myobject.removeEventListener('myevent',function(e) {...});
    //
    if ((args.Length() != 2) || (!args[0]->IsString()) || (!args[1]->IsFunction()))
    {
        return Undefined();
    }
    TiUIBase* obj = (TiUIBase*) userContext;
    Handle<String> eventName = Handle<String>::Cast(args[0]);
    Handle<Function> func = Handle<Function>::Cast(args[1]);
    String::Utf8Value eventNameUTF(eventName);
    obj->onRemoveEventListener(*eventNameUTF, func);
    return Undefined();
}
