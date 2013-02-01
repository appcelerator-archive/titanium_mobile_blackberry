/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_V8UTILS_H
#define TI_V8UTILS_H

#include <v8.h>

void DisplayExceptionLine (v8::TryCatch &try_catch);

// Reports an excetion thrown in JavaScript by logging it to stderr.
// If "show_line" is true the line at which the excpetion was thrown is displayed.
void ReportException(v8::TryCatch &try_catch, bool show_line);

#endif
