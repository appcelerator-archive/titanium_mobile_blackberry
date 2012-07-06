/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativePlatformInterface.h"
#include "TiConstants.h"
#include <vector>

#define PROP_GETTING_FUNCTION(NAME)     prop_##NAME

#define PROP_GETTER(NAME)               static Handle<Value> prop_##NAME(const NativePlatformInterface* instance) \
    {\
        return instance->NAME();\
    }

typedef Handle<Value> (*NATIVE_PROPGET_CALLBACK)(const NativePlatformInterface* instance);

// Prototypes
static vector<NATIVE_PROPGET_CALLBACK> initFunctionMap();

// Statics
static const vector<NATIVE_PROPGET_CALLBACK> s_functionMap = initFunctionMap();

const NativePlatformInterface* NativePlatformInterface::instance()
{
    static NativePlatformInterface s_theInstance;
    return &s_theInstance;
}

NativePlatformInterface::NativePlatformInterface()
{
}

PROP_GETTER(getAddress)
Handle<Value> NativePlatformInterface::getAddress()
{
    // TODO: Finish this when will be available in SDK
    return Undefined();
}

PROP_GETTER(getArchitecture)
Handle<Value> NativePlatformInterface::getArchitecture()
{
    // TODO: Finish this when will be available in SDK
    return Undefined();
}

PROP_GETTER(getAvailableMemory)
Handle<Value> NativePlatformInterface::getAvailableMemory()
{
    // TODO: Finish this when will be available in SDK
    return Undefined();
}

PROP_GETTER(getBatteryLevel)
Handle<Value> NativePlatformInterface::getBatteryLevel()
{
    return v8::Integer::New(NativePlatformInterface::instance()->batteryInfo_.level());
}

PROP_GETTER(getBatteryMonitoring)
Handle<Value> NativePlatformInterface::getBatteryMonitoring()
{
    // TODO: Finish this when will be available in SDK
    return Undefined();
}

PROP_GETTER(getBatteryState)
Handle<Value> NativePlatformInterface::getBatteryState()
{
    bb::device::BatteryInfo::ChargingState bState = NativePlatformInterface::instance()->batteryInfo_.chargingState();
    Ti::Platform::TI_BATTERY_STATE tiState = Ti::Platform::BATTERY_STATE_UNKNOWN;
    switch (bState)
    {
    case bb::device::BatteryInfo::UnknownChargingState:
        tiState = Ti::Platform::BATTERY_STATE_UNKNOWN;
        break;
    case bb::device::BatteryInfo::NotCharging:
        tiState = Ti::Platform::BATTERY_STATE_UNKNOWN;
        break;
    case bb::device::BatteryInfo::Full:
        tiState = Ti::Platform::BATTERY_STATE_FULL;
        break;
    case bb::device::BatteryInfo::Discharging:
        tiState = Ti::Platform::BATTERY_STATE_UNPLUGGED;
        break;
    case bb::device::BatteryInfo::Charging:
        tiState = Ti::Platform::BATTERY_STATE_CHARGING;
        break;
    }
    return v8::Integer::New(tiState);
}

PROP_GETTER(getDisplayCaps)
Handle<Value> NativePlatformInterface::getDisplayCaps()
{
    // TODO: Finish this when will be available in SDK
    return Undefined();
}

PROP_GETTER(getId)
Handle<Value> NativePlatformInterface::getId()
{
    // TODO: Finish this when will be available in SDK
    return Undefined();
}

PROP_GETTER(getLocale)
Handle<Value> NativePlatformInterface::getLocale()
{
    // TODO: Finish this when will be available in SDK
    return Undefined();
}

PROP_GETTER(getMacaddress)
Handle<Value> NativePlatformInterface::getMacaddress()
{
    // TODO: Finish this when will be available in SDK
    return Undefined();
}

PROP_GETTER(getModel)
Handle<Value> NativePlatformInterface::getModel()
{
    // TODO: Finish this when will be available in SDK
    return Undefined();
}

PROP_GETTER(getName)
Handle<Value> NativePlatformInterface::getName()
{
    return String::New("blackberry");
}

PROP_GETTER(getNetmask)
Handle<Value> NativePlatformInterface::getNetmask()
{
    // TODO: Finish this when will be available in SDK
    return Undefined();
}

PROP_GETTER(getOsname)
Handle<Value> NativePlatformInterface::getOsname()
{
    return String::New("blackberry");
}

PROP_GETTER(getOstype)
Handle<Value> NativePlatformInterface::getOstype()
{
    // TODO: Finish this when will be available in SDK
    return Undefined();
}

PROP_GETTER(getProcessorCount)
Handle<Value> NativePlatformInterface::getProcessorCount()
{
    // TODO: Finish this when will be available in SDK
    return Undefined();
}

PROP_GETTER(getRuntime)
Handle<Value> NativePlatformInterface::getRuntime()
{
    return String::New("v8");
}

PROP_GETTER(getUsername)
Handle<Value> NativePlatformInterface::getUsername()
{
    // TODO: Finish this when will be available in SDK
    return Undefined();
}

PROP_GETTER(getVersion)
Handle<Value> NativePlatformInterface::getVersion()
{
    // TODO: Finish this when will be available in SDK
    return Undefined();
}

Handle<Value> NativePlatformInterface::getPropertyValue(int propertyNumber)
{
    if ((propertyNumber >= s_functionMap.size()) || (s_functionMap[propertyNumber] == NULL))
    {
        return Undefined();
    }
    Handle<Value> result = (s_functionMap[propertyNumber])(NativePlatformInterface::instance());
    return result;
}

static vector<NATIVE_PROPGET_CALLBACK> initFunctionMap()
{
    vector<NATIVE_PROPGET_CALLBACK> vect;
    vect.resize(N_PLATFORM_PROP_LAST);

    vect[N_PLATFORM_PROP_UNDEFINED]                = NULL;
    vect[N_PLATFORM_PROP_ADDRESS]                  = NULL;
    vect[N_PLATFORM_PROP_ARCHITECTURE]             = NULL;
    vect[N_PLATFORM_PROP_AVAILABLEMEMORY]          = NULL;
    vect[N_PLATFORM_PROP_BATTERYLEVEL]             = PROP_GETTING_FUNCTION(getBatteryLevel);
    vect[N_PLATFORM_PROP_BATTERYMONITORING]        = NULL;
    vect[N_PLATFORM_PROP_BATTERYSTATE]             = PROP_GETTING_FUNCTION(getBatteryState);
    vect[N_PLATFORM_PROP_DISPLAYCAPS]              = NULL;
    vect[N_PLATFORM_PROP_ID]                       = NULL;
    vect[N_PLATFORM_PROP_LOCALE]                   = NULL;
    vect[N_PLATFORM_PROP_MACADDRESS]               = NULL;
    vect[N_PLATFORM_PROP_MODEL]                    = NULL;
    vect[N_PLATFORM_PROP_NAME]                     = PROP_GETTING_FUNCTION(getName);
    vect[N_PLATFORM_PROP_NETMASK]                  = NULL;
    vect[N_PLATFORM_PROP_OSNAME]                   = PROP_GETTING_FUNCTION(getOsname);
    vect[N_PLATFORM_PROP_OSTYPE]                   = NULL;
    vect[N_PLATFORM_PROP_PROCESSORCOUNT]           = NULL;
    vect[N_PLATFORM_PROP_RUNTIME]                  = PROP_GETTING_FUNCTION(getRuntime);
    vect[N_PLATFORM_PROP_USERNAME]                 = NULL;
    vect[N_PLATFORM_PROP_VERSION]                  = NULL;
    return vect;
}
