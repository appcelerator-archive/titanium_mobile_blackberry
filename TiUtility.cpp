/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUtility.h"
#include <stdio.h>
#include <string.h>

#ifndef min
#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#endif

struct COLOR_NAME_MAPPING
{
    const char* name;
    unsigned int value;
};

const static COLOR_NAME_MAPPING g_mapping[] =
        {
                {"white", 0xFFFFFFFF}, {"silver", 0xFFC0C0C0}, {"gray", 0xFF808080},
                {"black", 0xFF000000}, {"red", 0xFFFF0000}, {"maroon", 0xFF800000},
                {"yellow", 0xFFFFFF00}, {"olive", 0xFF808000}, {"lime", 0xFF00FF00},
                {"green", 0xFF008000}, {"aqua", 0xFF00FFFF}, {"teal", 0xFF008080},
                {"blue", 0xFF0000FF}, {"navy", 0xFF000080}, {"fuchsia", 0xFFFF00FF},
                {"purple", 0xFF800080}, {"cyan", 0xFF00FFFF}
        };

TiUtility::TiUtility()
{
}

TiUtility::~TiUtility()
{
}

unsigned int TiUtility::convertHTMLStringToNumber(const char* htmlString)
{
    if ((htmlString == NULL) || (htmlString[0] == 0) || (htmlString[0] != '#'))
    {
        return 0;
    }
    htmlString++;
    int len = min(strlen(htmlString),8);
    unsigned int val = 0;
    if (len == 3)
    {
        val = 0xFF000000;
    }
    else if (len == 4)
    {

    }
    else if (len == 6)
    {
        val = 0xFF000000;
    }
    else if (len == 8)
    {
    }
    const char* ptr = htmlString + strlen(htmlString) - 1;
    int i;
    int mul = 1;
    for (i = 0; i < len; i++)
    {
        if ((ptr[0] >= '0') && (ptr[0] <= '9'))
        {
            val += mul * ((int) (ptr[0] - '0'));
        }
        else if ((ptr[0] >= 'a') && (ptr[0] <= 'f'))
        {
            val += mul * ((int) (ptr[0] - 'a' + 10));
        }
        else if ((ptr[0] >= 'A') && (ptr[0] <= 'F'))
        {
            val += mul * ((int) (ptr[0] - 'A' + 10));
        }
        else
        {
            break;
        }
        ptr--;
        mul <<= 4;
    }
    return val;
}

void TiUtility::convertHTMLStringToColorComponents(const char* htmlString, float* r, float* g, float* b, float* a)
{
    *a = 1.0f;
    *r = 0.0f;
    *g = 0.0f;
    *b = 0.0f;
    if ((htmlString == NULL) || (htmlString[0] == 0))
    {
        return;
    }
    if (htmlString[0] != '#')
    {
        for (int i = 0; i < (int) (sizeof(g_mapping) / sizeof(*g_mapping)); i++)
        {
            if (stricmp(htmlString, g_mapping[i].name) == 0)
            {
                *a = ((float) ((g_mapping[i].value >> 24) & 0x000000FF)) / 255.0f;
                *r = ((float) ((g_mapping[i].value >> 16) & 0x000000FF)) / 255.0f;
                *g = ((float) ((g_mapping[i].value >> 8) & 0x000000FF)) / 255.0f;
                *b = ((float) (g_mapping[i].value & 0x000000FF)) / 255.0f;
                break;
            }
        }
        return;
    }
    htmlString++;
    int len = min(strlen(htmlString),8);
    if ((len == 1) || (len == 2))
    {
        float val = convertHexDigitsToFloat(htmlString, len);
        *r = val;
        *g = val;
        *b = val;
    }
    else if (len == 3)
    {
        *r = convertHexDigitsToFloat(htmlString++, 1);
        *g = convertHexDigitsToFloat(htmlString++, 1);
        *b = convertHexDigitsToFloat(htmlString++, 1);
    }
    else if (len == 4)
    {
        *a = convertHexDigitsToFloat(htmlString++, 1);
        *r = convertHexDigitsToFloat(htmlString++, 1);
        *g = convertHexDigitsToFloat(htmlString++, 1);
        *b = convertHexDigitsToFloat(htmlString++, 1);
    }
    else if (len == 6)
    {
        *r = convertHexDigitsToFloat(htmlString, 2);
        htmlString += 2;
        *g = convertHexDigitsToFloat(htmlString, 2);
        htmlString += 2;
        *b = convertHexDigitsToFloat(htmlString, 2);
        htmlString += 2;
    }
    else if (len == 8)
    {
        *a = convertHexDigitsToFloat(htmlString, 2);
        htmlString += 2;
        *r = convertHexDigitsToFloat(htmlString, 2);
        htmlString += 2;
        *g = convertHexDigitsToFloat(htmlString, 2);
        htmlString += 2;
        *b = convertHexDigitsToFloat(htmlString, 2);
        htmlString += 2;
    }
}

float TiUtility::convertHexDigitsToFloat(const char* digits, int digitCount)
{
    float div;
    int mul;
    int value = 0;
    int i;
    if (digitCount == 1)
    {
        div = 15.0f;
        mul = 1;
    }
    else if (digitCount == 2)
    {
        div = 255.0f;
        mul = 16;
    }
    else
    {
        return 0.0f;
    }
    for (i = 0; i < digitCount; i++)
    {
        if ((digits[i] >= '0') && (digits[i] <= '9'))
        {
            value += mul * ((int) (digits[i] - '0'));
        }
        else if ((digits[i] >= 'a') && (digits[i] <= 'f'))
        {
            value += mul * ((int) (digits[i] - 'a' + 10));
        }
        else if ((digits[i] >= 'A') && (digits[i] <= 'F'))
        {
            value += mul * ((int) (digits[i] - 'A' + 10));
        }
        else
        {
            break;
        }
        mul >>= 4;
    }
    return ((float) value) / div;
}
