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

NativeLoggerInterface* TiLogger::nativeLogger_ = NULL;

void TiLogger::initialize(NativeObjectFactory* nativeObjectFactory)
{
    if (nativeLogger_ == NULL)
    {
        nativeLogger_ = (NativeLoggerInterface*)nativeObjectFactory->createNativeObject(N_TYPE_LOGGER);
    }
}

void TiLogger::log(std::string msg)
{
    nativeLogger_->log(msg.c_str());
}
