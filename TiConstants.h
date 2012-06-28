/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TICONSTANTS_H_
#define TICONSTANTS_H_

namespace Ti
{

namespace UI
{

// Text alignment constants
enum N_TEXT_ALIGNMENT
{
    TEXT_ALIGNMENT_LEFT,
    TEXT_ALIGNMENT_CENTER,
    TEXT_ALIGNMENT_RIGHT
};

enum TI_PICKER_TYPE
{
    PICKER_TYPE_COUNT_DOWN_TIMER,
    PICKER_TYPE_TIME,
    PICKER_TYPE_DATE_AND_TIME,
    PICKER_TYPE_PLAIN,
    PICKER_TYPE_DATE
};

}

namespace Platform
{

// Battery states constants
enum N_BATTERY_STATE
{
    BATTERY_STATE_UNKNOWN,
    BATTERY_STATE_CHARGING,
    BATTERY_STATE_UNPLUGGED,
    BATTERY_STATE_FULL
};

}

}


#endif /* TICONSTANTS_H_ */
