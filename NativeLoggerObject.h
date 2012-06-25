/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVELOGGEROBJECT_H_
#define NATIVELOGGEROBJECT_H_

#include "NativeLoggerInterface.h"

class NativeLoggerWorker;

#include <QThread>

class QString;


#define N_DEBUG(msg) \
    do { \
        NativeLoggerObject::getInstance().log(QString("[N_DEBUG] ") + __PRETTY_FUNCTION__ + " Line " + __LINE__ + ": " + msg + "\n"); \
    } while(0)

/*
 * NativeLoggerObject
 *
 * Native Logger
 */

class NativeLoggerObject : public NativeLoggerInterface
{
public:
    static NativeLoggerObject& getInstance();
    virtual int getObjectType() const;

    void log(const char* msg);
    void log(const QString& t);

protected:
    virtual ~NativeLoggerObject();

private:
    explicit NativeLoggerObject();
    // Disable copy ctor & assignment operator
    NativeLoggerObject(const NativeLoggerObject& indicator);
    NativeLoggerObject& operator=(const NativeLoggerObject& indicator);

    void queueLog(const QString& msg);

    NativeLoggerWorker* nativeLoggerWorker_;
    QThread nativeLoggerThread_;
};

#endif /* NATIVELOGGEROBJECT_H_ */
