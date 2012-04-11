/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUTILITY_H_
#define TIUTILITY_H_

class TiUtility
{
public:
    static unsigned int convertHTMLStringToNumber(const char* htmlString);
    static void convertHTMLStringToColorComponents(const char* htmlString, float* r, float* g, float* b, float* a);
    static float convertHexDigitsToFloat(const char* digits, int digitCount);
    TiUtility();
    virtual ~TiUtility();
};

#endif /* TIUTILITY_H_ */
