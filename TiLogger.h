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


#define Ti_DEBUG(msg) \
    do { \
        stringstream ss; \
        ss << __LINE__; \
        TiLogger::getInstance().log(std::string("[Ti_DEBUG] ") + __PRETTY_FUNCTION__ + " Line " + ss.str() + ": " + msg + "\n"); \
    } while(0)


/*
 * TiLogger
 */

class TiLogger
{
public:
    static TiLogger& getInstance();
    static void initialize(NativeObjectFactory* nativeObjectFactory);

    void log(std::string msg);

protected:
    virtual ~TiLogger();

private:
    // Disable ctor, copy ctor, and assignment operator
    TiLogger();
    TiLogger(const TiLogger&);
    TiLogger& operator=(const TiLogger&);

    static NativeLoggerInterface* nativeLogger_;
};

#endif /* TILOGGER_H_ */
