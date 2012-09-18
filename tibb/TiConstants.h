/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TICONSTANTS_H_
#define TICONSTANTS_H_

#include <string>

namespace Ti
{

const std::string TopDir = "app/native";
const std::string AssetsDir = "app/native/assets";

namespace Codec
{
enum TI_BYTE_ORDER
{
    UNDEFINED = -1,
    BIG_ENDIAN,
    LITTLE_ENDIAN
}; // enum TI_BYTE_ORDER
} // namespace Codec

namespace Network
{
namespace Socket
{
// Socket states constants
enum TI_SOCKET_STATE
{
    SOCKET_STATE_CLOSED,
    SOCKET_STATE_CONNECTED,
    SOCKET_STATE_ERROR,
    SOCKET_STATE_INITIALIZED,
    SOCKET_STATE_LISTENING,
}; // enum TI_SOCKET_STATE
} // namespace Socket
} // namespace Network

namespace Platform
{
// Battery states constants
enum TI_BATTERY_STATE
{
    BATTERY_STATE_UNKNOWN,
    BATTERY_STATE_CHARGING,
    BATTERY_STATE_UNPLUGGED,
    BATTERY_STATE_FULL
}; // enum TI_BATTERY_STATE
} // namespace Platform

namespace Stream
{
// Stream open modes
enum TI_OPEN_MODE
{
    MODE_APPEND,
    MODE_READ,
    MODE_WRITE,
}; // enum TI_OPEN_MODE
} // namespace Platform

namespace UI
{
// Text alignment constants
enum N_TEXT_ALIGNMENT
{
    TEXT_ALIGNMENT_LEFT,
    TEXT_ALIGNMENT_CENTER,
    TEXT_ALIGNMENT_RIGHT
}; // enum N_TEXT_ALIGNMENT

enum TI_PICKER_TYPE
{
    PICKER_TYPE_COUNT_DOWN_TIMER,
    PICKER_TYPE_TIME,
    PICKER_TYPE_DATE_AND_TIME,
    PICKER_TYPE_PLAIN,
    PICKER_TYPE_DATE
}; // enum TI_PICKER_TYPE
} // namespace UI

} // namespace Ti


#endif /* TICONSTANTS_H_ */
