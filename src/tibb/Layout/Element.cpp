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

    (*element)._layoutCoefficients.width = {NAN, NAN, NAN};
    (*element)._layoutCoefficients.minWidth = {NAN, NAN, NAN};
    (*element)._layoutCoefficients.sandboxWidth = {NAN, NAN, NAN};
    (*element)._layoutCoefficients.height = {NAN, NAN, NAN};
    (*element)._layoutCoefficients.minHeight = {NAN, NAN, NAN};
    (*element)._layoutCoefficients.sandboxHeight = {NAN, NAN, NAN};
    (*element)._layoutCoefficients.left = {NAN, NAN, NAN};
    (*element)._layoutCoefficients.top =  {NAN, NAN, NAN, NAN};
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
