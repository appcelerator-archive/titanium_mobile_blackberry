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
    struct Element* e = (struct Element*)malloc(sizeof(struct Element));

    if (NULL == e) {
        printf("\n Element creation failed \n");
        return NULL;
    }

    (*e)._layoutCoefficients.width = {NAN, NAN, NAN};
    (*e)._layoutCoefficients.minWidth = {NAN, NAN, NAN};
    (*e)._layoutCoefficients.sandboxWidth = {NAN, NAN, NAN};
    (*e)._layoutCoefficients.height = {NAN, NAN, NAN};
    (*e)._layoutCoefficients.minHeight = {NAN, NAN, NAN};
    (*e)._layoutCoefficients.sandboxHeight = {NAN, NAN, NAN};
    (*e)._layoutCoefficients.left = {NAN, NAN, NAN};
    (*e)._layoutCoefficients.top =  {NAN, NAN, NAN, NAN};
    (*e)._layoutType = layoutType;
    (*e)._defaultHorizontalAlignment = center;
    (*e)._defaultVerticalAlignment = center;

    return e;
}

void addChildElement(Element* parent, Element* child) {

	if (NULL == parent || NULL == child) {
	   printf("\n Element add child failed \n");
	}

	(*parent)._children.push_back(child);
}
