/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef PLATFORMMODULE_H_
#define PLATFORMMODULE_H_

#include <v8.h>
#include <QObject>
#include "TiCore.h"
#include <bb/device/BatteryChargingState>

using namespace v8;

class TiPlatformModuleSignalHandler;
class TiPlatformModule : public Ti::TiModule
{

public:
	TiPlatformModule(const char*);
	CREATE_MODULE(TiPlatformModule)


	virtual void eventAdded(QString);
	virtual ~TiPlatformModule();

	Ti::TiValue canOpenURL(Ti::TiValue);
	Ti::TiValue createUUID(Ti::TiValue);
	Ti::TiValue openURL(Ti::TiValue);
	Ti::TiValue is24HourTimeFormat(Ti::TiValue);

	EXPOSE_METHOD(TiPlatformModule, canOpenURL)
	EXPOSE_METHOD(TiPlatformModule, createUUID)
	EXPOSE_METHOD(TiPlatformModule, openURL)
	EXPOSE_METHOD(TiPlatformModule, is24HourTimeFormat)

	void setBatteryMonitoring(Ti::TiValue);

	EXPOSE_SETTER(TiPlatformModule, setBatteryMonitoring)

	Ti::TiValue getAddress();
	Ti::TiValue getArchitecture();
	Ti::TiValue getAvailableMemory();
	Ti::TiValue getBatteryLevel();
	Ti::TiValue getBatteryMonitoring();
	Ti::TiValue getBatteryState();
	Ti::TiValue getDisplayCaps();
	Ti::TiValue getId();
	Ti::TiValue getLocale();
	Ti::TiValue getMacaddress();
	Ti::TiValue getManufacturer();
	Ti::TiValue getModel();
	Ti::TiValue getName();
	Ti::TiValue getNetmask();
	Ti::TiValue getOsname();
	Ti::TiValue getOstype();
	Ti::TiValue getProcessorCount();
	Ti::TiValue getRuntime();
	Ti::TiValue getUsername();
	Ti::TiValue getVersion();

	EXPOSE_GETTER(TiPlatformModule, getAddress)
	EXPOSE_GETTER(TiPlatformModule, getArchitecture)
	EXPOSE_GETTER(TiPlatformModule, getAvailableMemory)
	EXPOSE_GETTER(TiPlatformModule, getBatteryLevel)
	EXPOSE_GETTER(TiPlatformModule, getBatteryMonitoring)
	EXPOSE_GETTER(TiPlatformModule, getBatteryState)
	EXPOSE_GETTER(TiPlatformModule, getDisplayCaps)
	EXPOSE_GETTER(TiPlatformModule, getId)
	EXPOSE_GETTER(TiPlatformModule, getLocale)
	EXPOSE_GETTER(TiPlatformModule, getMacaddress)
	EXPOSE_GETTER(TiPlatformModule, getManufacturer)
	EXPOSE_GETTER(TiPlatformModule, getModel)
	EXPOSE_GETTER(TiPlatformModule, getName)
	EXPOSE_GETTER(TiPlatformModule, getNetmask)
	EXPOSE_GETTER(TiPlatformModule, getOsname)
	EXPOSE_GETTER(TiPlatformModule, getOstype)
	EXPOSE_GETTER(TiPlatformModule, getProcessorCount)
	EXPOSE_GETTER(TiPlatformModule, getRuntime)
	EXPOSE_GETTER(TiPlatformModule, getUsername)
	EXPOSE_GETTER(TiPlatformModule, getVersion)

	TiPlatformModuleSignalHandler* _signalHandler;
};


class TiPlatformModuleSignalHandler : public QObject
{
	Q_OBJECT;
public:
	TiPlatformModuleSignalHandler(TiPlatformModule*);
	TiPlatformModule* _module;
public slots:
	// Batter stuff
	void levelChanged (int, bb::device::BatteryChargingState::Type);
};

#endif /* PLATFORMMODULE_H_ */
