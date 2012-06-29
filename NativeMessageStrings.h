/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEMESSAGESTRINGS_H_
#define NATIVEMESSAGESTRINGS_H_

// Single file to contain the message strings

#ifdef NATIVEMESSAGESTRINGS_DEF_VALUE
#define N_MESSAGESTRINGS_CONST_DEF(T,N,V) const T N=V
#else  // NATIVEMESSAGESTRINGS_DEF_VALUE
#define N_MESSAGESTRINGS_CONST_DEF(T,N,V) extern const T N
#endif // NATIVEMESSAGESTRINGS_DEF_VALUE

namespace Native
{
namespace Msg
{

N_MESSAGESTRINGS_CONST_DEF(char*, Unknown_value_received, "Unknown value received");
N_MESSAGESTRINGS_CONST_DEF(char*, Failed_to_convert_font_size_to_float_with_value, "Failed to convert font size to float with value");
N_MESSAGESTRINGS_CONST_DEF(char*, Unknown_key_value_received, "Unknown key:value received");

}
}

#endif // NATIVEMESSAGESTRINGS_H_
