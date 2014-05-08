/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include "Layout/Element.h"
#include <math.h>
#include <QDebug>

namespace Ti
{
namespace Layout
{

void TiElement::elementInitialize(struct Element* element, enum LayoutType layoutType) {
    (*element)._layoutCoefficients.width.x1 = NAN;
    (*element)._layoutCoefficients.width.x2 =  NAN;
    (*element)._layoutCoefficients.width.x3 = NAN;
    (*element)._layoutCoefficients.minWidth.x1 = NAN;
    (*element)._layoutCoefficients.minWidth.x2 = NAN;
    (*element)._layoutCoefficients.minWidth.x3 = NAN;
    (*element)._layoutCoefficients.sandboxWidth.x1 = NAN;
    (*element)._layoutCoefficients.sandboxWidth.x2 = NAN;
    (*element)._layoutCoefficients.sandboxWidth.x3 = NAN;
    (*element)._layoutCoefficients.height.x1 = NAN;
    (*element)._layoutCoefficients.height.x2 =  NAN;
    (*element)._layoutCoefficients.height.x3 =  NAN;
    (*element)._layoutCoefficients.minHeight.x1 = NAN;
    (*element)._layoutCoefficients.minHeight.x2 =  NAN;
    (*element)._layoutCoefficients.minHeight.x3 =  NAN;
    (*element)._layoutCoefficients.sandboxHeight.x1 = NAN;
    (*element)._layoutCoefficients.sandboxHeight.x2 = NAN;
    (*element)._layoutCoefficients.sandboxHeight.x3 = NAN;
    (*element)._layoutCoefficients.left.x1 = NAN;
    (*element)._layoutCoefficients.left.x2 = NAN;
    (*element)._layoutCoefficients.left.x3 = NAN;
    (*element)._layoutCoefficients.top.x1 =  NAN;
    (*element)._layoutCoefficients.top.x2 = NAN;
    (*element)._layoutCoefficients.top.x3 = NAN;
    (*element)._layoutCoefficients.top.x4 = NAN;
    (*element)._layoutType = layoutType;
    (*element)._defaultRowAlignment = Center;
    (*element)._defaultHorizontalAlignment = Center;
    (*element)._defaultVerticalAlignment = Center;
}

void TiElement::addChildElement(Element* parent, Element* child) {
    if (NULL == parent || NULL == child) {
       printf("\n Element add child failed \n");
    }

    if(std::find((*parent)._children.begin(), (*parent)._children.end(), child) != (*parent)._children.end()) {
        // do nothing
    } else {
        (*parent)._children.push_back(child);
    }

}

void TiElement::removeChildElement(struct Element* parent, struct Element* child) {
    std::vector<struct Element*>::iterator i;
    i = std::find(parent->_children.begin(), parent->_children.end(), child);
    if (i != parent->_children.end()) {
        parent->_children.erase(i);
    }
}
}
}
