/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEPLATFORMINTERFACE_H_
#define NATIVEPLATFORMINTERFACE_H_

#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <v8.h>
#pragma GCC diagnostic warning "-Wunused-parameter"

#include <bb/device/BatteryInfo>

using namespace v8;
using namespace std;

enum NATIVE_PLATFORM_PROP
{
    N_PLATFORM_PROP_UNDEFINED
    , N_PLATFORM_PROP_ADDRESS
    , N_PLATFORM_PROP_ARCHITECTURE
    , N_PLATFORM_PROP_AVAILABLEMEMORY
    , N_PLATFORM_PROP_BATTERYLEVEL
    , N_PLATFORM_PROP_BATTERYMONITORING
    , N_PLATFORM_PROP_BATTERYSTATE
    , N_PLATFORM_PROP_DISPLAYCAPS
    , N_PLATFORM_PROP_ID
    , N_PLATFORM_PROP_LOCALE
    , N_PLATFORM_PROP_MACADDRESS
    , N_PLATFORM_PROP_MODEL
    , N_PLATFORM_PROP_NAME
    , N_PLATFORM_PROP_NETMASK
    , N_PLATFORM_PROP_OSNAME
    , N_PLATFORM_PROP_OSTYPE
    , N_PLATFORM_PROP_PROCESSORCOUNT
    , N_PLATFORM_PROP_RUNTIME
    , N_PLATFORM_PROP_USERNAME
    , N_PLATFORM_PROP_VERSION

    /* This MUST be the last element */
    , N_PLATFORM_PROP_LAST
};

/*
 * NativePlatformInterface
 *
 * Native Platform methods
 */
class NativePlatformInterface
{
public:
    static const NativePlatformInterface* instance();
    static Handle<Value> getPropertyValue(int propertyNumber);
    static Handle<Value> getAddress();
    static Handle<Value> getArchitecture();
    static Handle<Value> getAvailableMemory();
    static Handle<Value> getBatteryLevel();
    static Handle<Value> getBatteryMonitoring();
    static Handle<Value> getBatteryState();
    static Handle<Value> getDisplayCaps();
    static Handle<Value> getId();
    static Handle<Value> getLocale();
    static Handle<Value> getMacaddress();
    static Handle<Value> getModel();
    static Handle<Value> getName();
    static Handle<Value> getNetmask();
    static Handle<Value> getOsname();
    static Handle<Value> getOstype();
    static Handle<Value> getProcessorCount();
    static Handle<Value> getRuntime();
    static Handle<Value> getUsername();
    static Handle<Value> getVersion();

private:
    explicit NativePlatformInterface();
    NativePlatformInterface(const NativePlatformInterface&);
    NativePlatformInterface& operator=(const NativePlatformInterface&);
    // Native elements
    bb::device::BatteryInfo batteryInfo_;
};

#endif /* NATIVEPLATFORMINTERFACE_H_ */
