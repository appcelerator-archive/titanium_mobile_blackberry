/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeException.h"

NativeException::NativeException(const char* msg)
    : msg_(msg)
{
}

NativeException::NativeException(const std::string& msg)
    : msg_(msg)
{
}

const char* NativeException::what()
{
    return msg_.c_str();
}
