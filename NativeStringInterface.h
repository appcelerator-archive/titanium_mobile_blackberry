/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVESTRINGINTERFACE_H_
#define NATIVESTRINGINTERFACE_H_

#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <v8.h>
#pragma GCC diagnostic warning "-Wunused-parameter"


/*
 * NativeStringInterface
 *
 * Native String methods
 */
class NativeStringInterface
{
public:
    static const NativeStringInterface* instance();

    static v8::Handle<v8::Value> format(const v8::Arguments& args);
    static v8::Handle<v8::Value> formatCurrency(const v8::Arguments& args);
    static v8::Handle<v8::Value> formatDate(const v8::Arguments& args);
    static v8::Handle<v8::Value> formatDecimal(const v8::Arguments& args);
    static v8::Handle<v8::Value> formatTime(const v8::Arguments& args);
};

#endif /* NATIVESTRINGINTERFACE_H_ */
