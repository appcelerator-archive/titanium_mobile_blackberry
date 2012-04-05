/*
 * TiUtility.h
 *
 *  Created on: 2012-04-04
 *      Author: dcampbell
 */

#ifndef TIUTILITY_H_
#define TIUTILITY_H_

class TiUtility
{
public:
    static unsigned int convertHTMLStringToNumber(const char* htmlString);
    static void convertHTMLStringToColorComponents(const char* htmlString,float* r,float* g,float* b,float* a);
    static float convertHexDigitsToFloat(const char* digits,int digitCount);
    TiUtility();
    virtual ~TiUtility();
};

#endif /* TIUTILITY_H_ */
