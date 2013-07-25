/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TILOGGER_H_
#define TILOGGER_H_

class NativeLoggerInterface;
class NativeObjectFactory;

#include <sstream>
#include <string>
#include <QString>

#define TI_TAGGED_LOG(tag, msg) \
    do { \
        stringstream ss; \
        ss << tag " " << __PRETTY_FUNCTION__ << " Line " << __LINE__ << ": " << msg; \
        TiLogger::getInstance().log(ss.str().c_str()); \
    } while(0)

#define TI_TAG_INTERNAL "[TI_INTERNAL]"
#define TI_TAG_ERROR    "[TI_ERROR]"
#define TI_TAG_WARNING  "[TI_WARNING]"
#define TI_TAG_DEBUG    "[TI_DEBUG]"
#define TI_TAG_INFO     "[TI_INFO]"

#define TI_INTERNAL(msg) TI_TAGGED_LOG(TI_TAG_INTERNAL, msg)
#define TI_ERROR(msg)    TI_TAGGED_LOG(TI_TAG_ERROR, msg)
#define TI_WARNING(msg)  TI_TAGGED_LOG(TI_TAG_WARNING, msg)
#define TI_DEBUG(msg)    TI_TAGGED_LOG(TI_TAG_DEBUG, msg)
#define TI_INFO(msg)     TI_TAGGED_LOG(TI_TAG_INFO, msg)


/*
 * TiLogger
 *
 * Logger to be used from the Ti* classes.  This logger is meant to
 * be used via the TI_* macros such as TI_DEBUG.  The macros accept string
 * concatenation in the parameter using the '<<' operator.
 *
 * See NativeLoggerObject.h for logging from the Native* classes.
 */

class TiLogger
{
public:
    static TiLogger& getInstance();
    static void deleteInstance();
    static void initialize(NativeObjectFactory* nativeObjectFactory);

    void log(const char* msg);
    void log(QString msg);
    void log(const char* tag, const char* msg);

protected:
    virtual ~TiLogger();

private:
    // Disable ctor, copy ctor, and assignment operator
    TiLogger();
    TiLogger(const TiLogger&);
    TiLogger& operator=(const TiLogger&);

    static NativeLoggerInterface* s_nativeLogger;
};

#endif /* TILOGGER_H_ */
