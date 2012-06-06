/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIEXCEPTIONSTRINGS_H_
#define TIEXCEPTIONSTRINGS_H_

// Single file to contain the V8 exception strings

#ifdef DEF_VALUE
#define CONST_DEF(T,N,V) const T N=V
#else  // DEF_VALUE
#define CONST_DEF(T,N,V) extern const T N
#endif // DEF_VALUE

namespace Ti
{

CONST_DEF(char*, Expected_argument_of_type_double, "Expected argument of type double");
CONST_DEF(char*, Expected_argument_of_type_integer, "Expected argument of type integer");
CONST_DEF(char*, Expected_argument_of_type_object_or_external, "Expected argument of type object or external");
CONST_DEF(char*, Expected_argument_of_type_string, "Expected argument of type string");
CONST_DEF(char*, Expected_argument_of_type_unsigned_integer, "Expected argument of type unsigned integer");
CONST_DEF(char*, INTERNAL__An_error_occurred_while_parsing_the_format_string, "INTERNAL: An error occurred while parsing the format string");

CONST_DEF(char*, Missing_argument, "Missing argument");
CONST_DEF(char*, Too_many_arguments, "Too many arguments");

}

#endif // TIEXCEPTIONSTRINGS_H_
