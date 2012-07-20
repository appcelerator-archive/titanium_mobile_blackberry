/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeLoggerObject.h"

#include "NativeLoggerWorker.h"

#include <QString>


static NativeLoggerObject* s_logger;

NativeLoggerObject::NativeLoggerObject()
    : nativeLoggerWorker_(new NativeLoggerWorker)
{
    nativeLoggerThread_.start();
    nativeLoggerWorker_->moveToThread(&nativeLoggerThread_);
}

NativeLoggerObject::~NativeLoggerObject()
{
    // block until the logger queue is flushed
    QMetaObject::invokeMethod(nativeLoggerWorker_, "flush", Qt::BlockingQueuedConnection);

    nativeLoggerThread_.quit();
    nativeLoggerThread_.wait();
    delete nativeLoggerWorker_;
    nativeLoggerWorker_ = NULL;
}

NativeLoggerObject* NativeLoggerObject::getInstance()
{
    if (s_logger == NULL)
    {
        s_logger = new NativeLoggerObject;
    }
    return s_logger;
}

void NativeLoggerObject::deleteInstance()
{
    delete s_logger;
    s_logger = NULL;
}

int NativeLoggerObject::getObjectType() const
{
    return N_TYPE_LOGGER;
}

void NativeLoggerObject::log(const char* msg)
{
    queueLog(msg);
}

void NativeLoggerObject::log(const QString& msg)
{
    queueLog(msg);
}

void NativeLoggerObject::queueLog(const QString& msg)
{
    QMetaObject::invokeMethod(nativeLoggerWorker_, "log", Qt::QueuedConnection, Q_ARG(QString, msg));
}
