/*
 * Common.cpp
 *
 *  Created on: Dec 3, 2012
 *      Author: rmcmahon
 */


#include "Element.h"
#include "Composite.h"
#include "Horizontal.h"
#include "Vertical.h"

bool isNaN(float value) {
	if (value != value)
		return true;
	else
		return false;
}

ComputedSize layoutNode(struct Element* element, double width, double height, bool isWidthSize, bool isHeightSize) {
	ComputedSize computedSize;

	switch ((*element)._layoutType) {
		case composite:
			computedSize = doCompositeLayout((*element)._children, width, height, isWidthSize, isHeightSize);
			break;
		case horizontal:
			computedSize = doHorizontalLayout((*element)._children, width, height, isWidthSize, isHeightSize);
			break;
		case vertical:
			computedSize = doVerticalLayout((*element)._children, width, height, isWidthSize, isHeightSize);
			break;
	}

	return computedSize;
}







