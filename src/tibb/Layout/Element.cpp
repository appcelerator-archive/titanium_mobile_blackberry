/*
 * Element.cpp
 *
 *  Created on: Dec 3, 2012
 *      Author: rmcmahon
 */

#include <stdlib.h>
#include <stdio.h>
#include "Element.h"
#include <math.h>

struct Element* createElement(enum LayoutType layoutType) {
    struct Element* element = (struct Element*)malloc(sizeof(struct Element));

    if (NULL == element) {
        printf("\n Element creation failed \n");
        return NULL;
    }

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
    (*element)._layoutType = layoutType;
    (*element)._defaultRowAlignment = start;
    (*element)._defaultHorizontalAlignment = center;
    (*element)._defaultVerticalAlignment = center;

    return element;
}

void addChildElement(Element* parent, Element* child) {

	if (NULL == parent || NULL == child) {
	   printf("\n Element add child failed \n");
	}

	(*parent)._children.push_back(child);
}
