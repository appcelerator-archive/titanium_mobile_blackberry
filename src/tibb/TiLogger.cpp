/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiLogger.h"

#include "NativeLoggerInterface.h"
#include "NativeObjectFactory.h"
#include <cassert>

NativeLoggerInterface* TiLogger::s_nativeLogger = NULL;
static TiLogger* s_tiLogger = NULL;

TiLogger::TiLogger()
{
}

TiLogger::~TiLogger()
{
}

TiLogger& TiLogger::getInstance()
{
    if (s_tiLogger == NULL)
    {
        s_tiLogger = new TiLogger;
    }
    return *s_tiLogger;
}

void TiLogger::deleteInstance()
{
    delete s_tiLogger;
    s_tiLogger = NULL;
    s_nativeLogger->deleteInstance();
    s_nativeLogger = NULL;
}

void TiLogger::initialize(NativeObjectFactory* nativeObjectFactory)
{
    if (s_nativeLogger == NULL)
    {
        s_nativeLogger = (NativeLoggerInterface*)nativeObjectFactory->createNativeObject(N_TYPE_LOGGER, NULL);
    }
}

void TiLogger::log(const char* msg)
{
    assert(s_nativeLogger);
    s_nativeLogger->log(msg);
}
void TiLogger::log(QString msg)
{
	log(msg.toLocal8Bit().constData());
}

void TiLogger::log(const char* tag, const char* msg)
{
    std::stringstream s;
    s << "[" << tag << "] " << msg;
    log(s.str().c_str());
}

