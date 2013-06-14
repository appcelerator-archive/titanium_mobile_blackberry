/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_V8UTILS_H
#define TI_V8UTILS_H

#include <QString>
#include <v8.h>

namespace titanium {

void DisplayExceptionLine (v8::TryCatch &try_catch);

// Reports an excetion thrown in JavaScript by logging it to stderr.
// If "show_line" is true the line at which the excpetion was thrown is displayed.
void ReportException(v8::TryCatch &try_catch, bool show_line);

// Copies the characters from the V8 String into a new QString.
QString V8StringToQString(v8::Handle<v8::String> v8Str);

inline QString V8ValueToQString(v8::Handle<v8::Value> value) {
    return V8StringToQString(value->ToString());
}

// Looks up a property on an object and calls it.
// The property must be a function, otherwise this will
// return back an empty handle on failure.
v8::Local<v8::Value> CallV8ObjectProperty(
    v8::Handle<v8::Object> object,
    const char* propertyName,
    int argc,
    v8::Handle<v8::Value> argv[]);

}  // namespace titanium

#endif
