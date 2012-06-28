/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiPlatform.h"

#include "NativeObject.h"
#include "NativePlatformInterface.h"
#include "TiConstants.h"
#include "TiGenericFunctionObject.h"
#include "TiPropertyGetFunctionObject.h"
#include "TiPropertyMapObject.h"

const static TiProperty g_tiProperties[] =
{
    {
        "address", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_ADDRESS
    },

    {
        "architecture", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_ARCHITECTURE
    },

    {
        "availableMemory", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_AVAILABLEMEMORY
    },

    {
        "batteryLevel", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_BATTERYLEVEL
    },

    {
        "batteryMonitoring", TI_PROP_PERMISSION_READ | TI_PROP_PERMISSION_WRITE, N_PLATFORM_PROP_BATTERYMONITORING
    },

    {
        "batteryState", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_BATTERYSTATE
    },

    {
        "displayCaps", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_DISPLAYCAPS
    },

    {
        "id", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_ID
    },

    {
        "locale", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_LOCALE
    },

    {
        "macaddress", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_MACADDRESS
    },

    {
        "model", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_MODEL
    },

    {
        "name", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_NAME
    },

    {
        "netmask", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_NETMASK
    },

    {
        "osname", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_OSNAME
    },

    {
        "ostype", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_OSTYPE
    },

    {
        "processorCount", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_PROCESSORCOUNT
    },

    {
        "runtime", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_RUNTIME
    },

    {
        "username", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_USERNAME
    },

    {
        "version", TI_PROP_PERMISSION_READ, N_PLATFORM_PROP_USERNAME
    }
};

TiPlatform::TiPlatform()
    : TiObject("Platform")
{
}

TiPlatform::~TiPlatform()
{
}

void TiPlatform::addObjectToParent(TiObject* parent)
{
    TiPlatform* obj = new TiPlatform();
    parent->addMember(obj);
    obj->release();
}

void TiPlatform::onCreateStaticMembers()
{
    TiObject::onCreateStaticMembers();
    setTiPlatformMappingProperties(g_tiProperties, sizeof(g_tiProperties) / sizeof(*g_tiProperties));

    // Adding javascript constants from Ti.Platform
    ADD_STATIC_TI_VALUE("BATTERY_STATE_CHARGING", Number::New(Ti::Platform::BATTERY_STATE_CHARGING), this);
    ADD_STATIC_TI_VALUE("BATTERY_STATE_FULL", Number::New(Ti::Platform::BATTERY_STATE_FULL), this);
    ADD_STATIC_TI_VALUE("BATTERY_STATE_UNKNOWN", Number::New(Ti::Platform::BATTERY_STATE_UNKNOWN), this);
    ADD_STATIC_TI_VALUE("BATTERY_STATE_UNPLUGGED", Number::New(Ti::Platform::BATTERY_STATE_UNPLUGGED), this);
}

void TiPlatform::setTiPlatformMappingProperties(const TiProperty* props, int propertyCount)
{
    string name;
    char c[2];
    c[1] = 0;
    for (int i = 0; i < propertyCount; i++)
    {
        TiObject* value = TiPropertyMapObject::addProperty(this, props[i].propertyName, props[i].nativePropertyNumber,
                          _valueGetter, this);
        c[0] = toupper(props[i].propertyName[0]);
        name = "get";
        name += c;
        name += props[i].propertyName + 1;
        TiPropertyGetFunctionObject::addPropertyGetter(this, value, name.c_str());
    }
}

Handle<Value> TiPlatform::_valueGetter(int propertyNumber, void* context)
{
    TiPlatform* self = (TiPlatform*) context;
    return self->getPropertyValue(propertyNumber);
}

Handle<Value> TiPlatform::getPropertyValue(int propertyNumber)
{
    const NativePlatformInterface* platformInterface = NativePlatformInterface::instance();
    return platformInterface->getPropertyValue(propertyNumber);
}
