/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiLogger.h"

#include "NativeLoggerInterface.h"
#include "NativeObjectFactory.h"

TiLogger::TiLogger()
{
}

TiLogger::~TiLogger()
{
}

TiLogger& TiLogger::getInstance()
{
    static TiLogger tiLogger;
    return tiLogger;
}

NativeLoggerInterface* TiLogger::s_nativeLogger = NULL;

void TiLogger::initialize(NativeObjectFactory* nativeObjectFactory)
{
    if (s_nativeLogger == NULL)
    {
        s_nativeLogger = (NativeLoggerInterface*)nativeObjectFactory->createNativeObject(N_TYPE_LOGGER);
    }
}

void TiLogger::log(std::string msg)
{
    s_nativeLogger->log(msg.c_str());
}
