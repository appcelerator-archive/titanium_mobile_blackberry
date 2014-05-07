/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiPlatformModule.h"
#include <QUuid>
#include <QtNetwork/QNetworkAddressEntry>
#include <bb/MemoryInfo>
#include <bb/device/BatteryInfo>
#include <bb/device/DisplayInfo>
#include <bb/device/HardwareInfo>
#include <bps/deviceinfo.h>
#include <bb/pim/calendar/CalendarSettings>
#include <QLocale>
#include <QNetworkInterface>

static float const MMPERINCH = 25.4f;

TiPlatformModule::TiPlatformModule(const char* name) :
	Ti::TiModule(name)
{

   addNumber("BATTERY_STATE_CHARGING", bb::device::BatteryChargingState::Charging);
   addNumber("BATTERY_STATE_FULL", bb::device::BatteryChargingState::Full);
   addNumber("BATTERY_STATE_UNKNOWN", bb::device::BatteryChargingState::Unknown);
   addNumber("BATTERY_STATE_UNPLUGGED", bb::device::BatteryChargingState::Discharging);
   addNumber("BATTERY_STATE_NOT_CHARGING", bb::device::BatteryChargingState::NotCharging);
   addNumber("BATTERY_STATE_DISCHARGING", bb::device::BatteryChargingState::Discharging);


	createPropertyFunction("canOpenURL", _canOpenURL);
	createPropertyFunction("createUUID", _createUUID);
	createPropertyFunction("openURL", _openURL);
	createPropertyFunction("is24HourTimeFormat", _is24HourTimeFormat);

	createPropertySetter("batteryMonitoring", _setBatteryMonitoring);

	createPropertyGetter("address", _getAddress);
	createPropertyGetter("architecture", _getArchitecture);
	createPropertyGetter("availableMemory", _getAvailableMemory);
	createPropertyGetter("batteryLevel", _getBatteryLevel);
	createPropertyGetter("batteryMonitoring", _getBatteryMonitoring);
	createPropertyGetter("batteryState", _getBatteryState);
	createPropertyGetter("displayCaps", _getDisplayCaps);
	createPropertyGetter("id", _getId);
	createPropertyGetter("locale", _getLocale);
	createPropertyGetter("macaddress", _getMacaddress);
	createPropertyGetter("manufacturer", _getManufacturer);
	createPropertyGetter("model", _getModel);
	createPropertyGetter("name", _getName);
	createPropertyGetter("netmask", _getNetmask);
	createPropertyGetter("osname", _getOsname);
	createPropertyGetter("ostype", _getOstype);
	createPropertyGetter("processorCount", _getProcessorCount);
	createPropertyGetter("runtime", _getRuntime);
	createPropertyGetter("username", _getUsername);
	createPropertyGetter("version", _getVersion);


	_signalHandler = new TiPlatformModuleSignalHandler(this);
}

TiPlatformModule::~TiPlatformModule()
{
	delete _signalHandler;
}

Ti::TiValue TiPlatformModule::canOpenURL(Ti::TiValue value)
{
	Ti::TiValue val;
	val.setBool(false);
	return val;
}
Ti::TiValue TiPlatformModule::createUUID(Ti::TiValue)
{
	Ti::TiValue val;
	QString uid = QUuid::createUuid().toString();
	uid.replace("{", ""); uid.replace("}", "");
	val.setString(uid);
	return val;
}
Ti::TiValue TiPlatformModule::openURL(Ti::TiValue value)
{
	Ti::TiValue val;
	val.setBool(false);
	return val;
}
Ti::TiValue TiPlatformModule::is24HourTimeFormat(Ti::TiValue value)
{
	Ti::TiValue val;
	bb::pim::calendar::CalendarSettings calSettings;
	val.setBool(calSettings.is24HourFormat());
	return val;
}

void TiPlatformModule::setBatteryMonitoring(Ti::TiValue value)
{
	Ti::TiHelper::Log("[WARN] Batter Monitoring not supported");
}

Ti::TiValue TiPlatformModule::getAddress()
{
	Ti::TiValue val;
	QNetworkAddressEntry _network;
	val.setString(_network.ip().toString());
	return val;
}
Ti::TiValue TiPlatformModule::getArchitecture()
{
	//TODO: Finish this
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiPlatformModule::getAvailableMemory()
{
	Ti::TiValue val;
	bb::MemoryInfo _memoryinfo;
	val.setNumber(_memoryinfo.availableDeviceMemory());
	return val;
}
Ti::TiValue TiPlatformModule::getBatteryLevel()
{
	Ti::TiValue val;
	bb::device::BatteryInfo _batteryInfo;
	val.setNumber(_batteryInfo.level());
	return val;
}
Ti::TiValue TiPlatformModule::getBatteryMonitoring()
{
	Ti::TiHelper::Log("[WARN] Batter Monitoring not supported");
	Ti::TiHelper::Log("[WARN] Use Ti.Platform.addEventListener('battery', .. ) instead");
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiPlatformModule::getBatteryState()
{
	Ti::TiValue val;
	bb::device::BatteryInfo _batteryInfo;
	val.setNumber(_batteryInfo.chargingState());
	return val;
}
Ti::TiValue TiPlatformModule::getDisplayCaps()
{
    bb::device::DisplayInfo display;

    QSize pixelSize = display.pixelSize();
    QSizeF physicalSize = display.physicalSize();

    const float physicalWidth = physicalSize.width();
    const float physicalHeight = physicalSize.height();
    const float pixelWidth = pixelSize.width();
    const float pixelHeight = pixelSize.height();

    float xdpi = 0.0f, ydpi = 0.0f;
    // Calculate pixel per inch in x/y dimensions
    if (physicalWidth != 0.0f && physicalHeight != 0.0f)
    {
        xdpi = (pixelWidth / physicalWidth) * MMPERINCH;
        ydpi = (pixelHeight / physicalHeight) * MMPERINCH;
    }

    // Calculate pixels density
    // TODO: Use the supplied one if it ever becomes available.
    const float diagonalWidth = sqrtf(physicalWidth * physicalWidth + physicalHeight * physicalHeight) / MMPERINCH;
    const float diagonalPixels = sqrtf(pixelWidth * pixelWidth + pixelHeight * pixelHeight);

	Ti::TiValue val;

    QMap<QString, Ti::TiValue> obj;

    Ti::TiValue valueDensity;
    valueDensity.setString("high");
    obj["density"] = valueDensity;

    Ti::TiValue valueDpi;
    valueDpi.setNumber(diagonalPixels / diagonalWidth);
    obj["dpi"] = valueDpi;

    // TODO: Find out do we need this 'logicalDensityFactor' for BB. Defaulting to 1.0 for now
    Ti::TiValue valueLogicalDensityFactor;
    valueLogicalDensityFactor.setNumber(1.0);
    obj["logicalDensityFactor"] = valueLogicalDensityFactor;

    Ti::TiValue valuePlatformWidth;
    valuePlatformWidth.setNumber(pixelWidth);
    obj["platformWidth"] = valuePlatformWidth;

    Ti::TiValue valuePlatformHeight;
    valuePlatformHeight.setNumber(pixelHeight);
    obj["platformHeight"] = valuePlatformHeight;

    Ti::TiValue valueXdpi;
    valueXdpi.setNumber(xdpi);
    obj["xdpi"] = valueXdpi;

    Ti::TiValue valueYdpi;
    valueYdpi.setNumber(ydpi);
    obj["ydpi"] = valueYdpi;

    val.setMap(obj);
	return val;
}
Ti::TiValue TiPlatformModule::getId()
{
	Ti::TiValue val;
	bb::device::HardwareInfo hdi;
	val.setString(hdi.pin());
	return val;
}
Ti::TiValue TiPlatformModule::getLocale()
{
	QLocale locale;
	Ti::TiValue val;
	val.setString(locale.name());
	return val;
}
Ti::TiValue TiPlatformModule::getMacaddress()
{
	Ti::TiValue val;
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for(int i = 0, len = interfaces.size(); i < len; i++)
    {
    	QNetworkInterface interface = interfaces.at(i);
    	if(interface.hardwareAddress().length() > 0)
    	{
    		val.setString(interface.hardwareAddress());
    		return val;
    	}
    }
	val.setString("");
	return val;
}
Ti::TiValue TiPlatformModule::getManufacturer()
{
	Ti::TiValue val;
	val.setString("blackberry");
	return val;
}
Ti::TiValue TiPlatformModule::getModel()
{
	Ti::TiValue val;
	bb::device::HardwareInfo info;
	val.setString(info.modelName());
	return val;
}
Ti::TiValue TiPlatformModule::getName()
{
	Ti::TiValue val;
	bb::device::HardwareInfo info;
	val.setString(info.deviceName());
	return val;
}
Ti::TiValue TiPlatformModule::getNetmask()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiPlatformModule::getOsname()
{
	Ti::TiValue val;
	val.setString("blackberry");
	return val;
}
Ti::TiValue TiPlatformModule::getOstype()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiPlatformModule::getProcessorCount()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiPlatformModule::getRuntime()
{
	Ti::TiValue val;
	val.setString("v8");
	return val;
}
Ti::TiValue TiPlatformModule::getUsername()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiPlatformModule::getVersion()
{
	Ti::TiValue val;
    deviceinfo_data_t deviceInfo;
    if (BPS_SUCCESS == deviceinfo_get_data(&deviceInfo))
    {
        QString deviceOsVersion(deviceInfo.scm_bundle);
        deviceinfo_free_data(&deviceInfo);
        val.setString(deviceOsVersion);
    }
    else
    {
    	val.setUndefined();
    }
	return val;
}


void TiPlatformModule::eventAdded(QString str)
{
	if(str == QString("battery"))
	{
		bb::device::BatteryInfo _batteryInfo;
		QObject::connect(&_batteryInfo, SIGNAL(levelChanged(int, bb::device::BatteryChargingState::Type)),
				_signalHandler, SLOT(levelChanged(int, bb::device::BatteryChargingState::Type)));
	}
}

TiPlatformModuleSignalHandler::TiPlatformModuleSignalHandler(TiPlatformModule* module)
{
	_module = module;
}

void TiPlatformModuleSignalHandler::levelChanged(int level, bb::device::BatteryChargingState::Type newChargingState)
{
	Ti::TiEventParameters params;
	params.addParam("level", level);
	params.addParam("state", (int)newChargingState);
	_module->fireEvent("battery", params);
}
