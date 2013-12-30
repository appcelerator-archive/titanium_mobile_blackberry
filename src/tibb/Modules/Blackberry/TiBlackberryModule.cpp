/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiBlackberryModule.h"
#include "Notification/ToastNotificationProxy.h"

#include <bb/system/SystemUiModality>
#include <bb/system/SystemUiPosition>

using namespace TiBlackberry;
TiBlackberryModule::TiBlackberryModule(const char* name) : Ti::TiModule(name)
{
    addFunction("createToast", ToastNotificationProxy::CreateProxy);
    addFunction("createToastNotification", ToastNotificationProxy::CreateProxy);

    addNumber("POSITION_TYPE_MIDDLE_CENTER", bb::system::SystemUiPosition::MiddleCenter);
    addNumber("POSITION_TYPE_TOP_CENTER", bb::system::SystemUiPosition::TopCenter);
    addNumber("POSITION_TYPE_BOTTOM_CENTER", bb::system::SystemUiPosition::BottomCenter);

    addNumber("MODALITY_APPLICATION", bb::system::SystemUiModality::Application);
    addNumber("MODALITY_GLOBAL", bb::system::SystemUiModality::Global);

}

TiBlackberryModule::~TiBlackberryModule()
{

}

Ti::TiValue TiBlackberryModule::getModuleId()
{
    Ti::TiValue val;
    val.setString("ti.blackberry");
    return val;
}
Ti::TiValue TiBlackberryModule::getModuleVersion()
{
    Ti::TiValue val;
    val.setString("1.0");
    return val;
}
Ti::TiValue TiBlackberryModule::getModuleName()
{
    Ti::TiValue val;
    val.setString("TiBlackberry");
    return val;
}
