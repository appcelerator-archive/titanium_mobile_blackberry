/*
 * element.h
 *
 *  Created on: Dec 3, 2012
 *      Author: rmcmahon
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <string>
#include <vector>
#include "Common.h"

struct Element {
    std::vector<struct Element*> _children;
    struct LayoutCoefficients _layoutCoefficients;
    struct ComputedSize _computedSize;
    double _measuredSandboxWidth;
    double _measuredSandboxHeight;
    double _measuredWidth;
    double _measuredHeight;
    double _measuredLeft;
    double _measuredTop;
    double _borderRightWidth;
    double _borderTopWidth;
    double _borderBottomWidth;
    double _borderLeftWidth;
    enum LayoutType _layoutType;
    enum ElementAlignment _defaultHorizontalAlignment;
    enum ElementAlignment _defaultVerticalAlignment;
};

struct Element* createElement(enum LayoutType);
void addChildElement(Element*, Element*);

#endif /* ELEMENT_H_ */
