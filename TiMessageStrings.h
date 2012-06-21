/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIMESSAGESTRINGS_H_
#define TIMESSAGESTRINGS_H_

// Single file to contain the message strings

#ifdef TIMESSAGESTRINGS_DEF_VALUE
#define TIMESSAGESTRINGS_CONST_DEF(T,N,V) const T N=V
#else  // TIMESSAGESTRINGS_DEF_VALUE
#define TIMESSAGESTRINGS_CONST_DEF(T,N,V) extern const T N
#endif // TIMESSAGESTRINGS_DEF_VALUE

namespace Ti
{
namespace Msg
{

TIMESSAGESTRINGS_CONST_DEF(char*, An_error_occurred_converting_to_int, "An error occurred converting to int");
TIMESSAGESTRINGS_CONST_DEF(char*, Expected_argument_of_type_double, "Expected argument of type double");
TIMESSAGESTRINGS_CONST_DEF(char*, Expected_argument_of_type_integer, "Expected argument of type integer");
TIMESSAGESTRINGS_CONST_DEF(char*, Expected_argument_of_type_object_or_external, "Expected argument of type object or external");
TIMESSAGESTRINGS_CONST_DEF(char*, Expected_argument_of_type_string, "Expected argument of type string");
TIMESSAGESTRINGS_CONST_DEF(char*, Expected_argument_of_type_date, "Expected argument of type date");
TIMESSAGESTRINGS_CONST_DEF(char*, Expected_argument_of_type_unsigned_integer, "Expected argument of type unsigned integer");
TIMESSAGESTRINGS_CONST_DEF(char*, INTERNAL__An_error_occurred_while_parsing_the_format_string, "INTERNAL: An error occurred while parsing the format string");
TIMESSAGESTRINGS_CONST_DEF(char*, INTERNAL__Global_String_symbol_is_not_an_object, "INTERNAL: Global String symbol is not an object");
TIMESSAGESTRINGS_CONST_DEF(char*, Missing_argument, "Missing argument");
TIMESSAGESTRINGS_CONST_DEF(char*, Numbered_argument_exceeds_the_length_of_provided_arguments, "Numbered argument exceeds the length of provided arguments");
TIMESSAGESTRINGS_CONST_DEF(char*, Too_many_arguments, "Too many arguments");

}
}

#endif // TIMESSAGESTRINGS_H_
