/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEEXCEPTION_H_
#define NATIVEEXCEPTION_H_

#include <exception>
#include <string>


/*
 * NativeException
 *
 * Exception to be thrown by the Native layer
 */

class NativeException : public std::exception
{
public:
    explicit NativeException(const char* msg);
    explicit NativeException(const std::string& msg);
    virtual const char* what();

private:
    std::string msg_;
};

#endif /* NATIVEEXCEPTION_H_ */
