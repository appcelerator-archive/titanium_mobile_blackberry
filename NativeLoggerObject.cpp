/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeLoggerObject.h"

#include "NativeLoggerWorker.h"

#include <QString>


NativeLoggerObject::NativeLoggerObject()
    : nativeLoggerWorker_(new NativeLoggerWorker)
{
    nativeLoggerThread_.start();
    nativeLoggerWorker_->moveToThread(&nativeLoggerThread_);
}

NativeLoggerObject::~NativeLoggerObject()
{
    nativeLoggerThread_.quit();
    nativeLoggerThread_.wait();
    delete nativeLoggerWorker_;
    nativeLoggerWorker_ = NULL;
}

NativeLoggerObject& NativeLoggerObject::getInstance()
{
    static NativeLoggerObject logger;
    return logger;
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
