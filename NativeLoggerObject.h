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

#include <QTextStream>
#include <QThread>

class QString;


#define N_TAGGED_LOG(tag, msg) \
    do { \
        QString s; \
        QTextStream ts(&s); \
        ts << tag " " << __PRETTY_FUNCTION__ << " Line "  << __LINE__ << ": " << msg; \
        NativeLoggerObject::getInstance()->log(s); \
    } while(0)

#define N_TAG_INTERNAL "[N_INTERNAL]"
#define N_TAG_ERROR    "[N_ERROR]"
#define N_TAG_WARNING  "[N_WARNING]"
#define N_TAG_DEBUG    "[N_DEBUG]"
#define N_TAG_INFO     "[N_INFO]"

#define N_INTERNAL(msg) N_TAGGED_LOG(N_TAG_INTERNAL, msg)
#define N_ERROR(msg)    N_TAGGED_LOG(N_TAG_ERROR, msg)
#define N_WARNING(msg)  N_TAGGED_LOG(N_TAG_WARNING, msg)
#define N_DEBUG(msg)    N_TAGGED_LOG(N_TAG_DEBUG, msg)
#define N_INFO(msg)     N_TAGGED_LOG(N_TAG_INFO, msg)


/*
 * NativeLoggerObject
 *
 * Native Logger
 */

class NativeLoggerObject : public NativeLoggerInterface
{
public:
    static NativeLoggerObject* getInstance();
    virtual void deleteInstance();
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
