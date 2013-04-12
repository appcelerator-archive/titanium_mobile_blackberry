/*
 * Composite.cpp
 *
 *  Created on: Dec 3, 2012
 *      Author: rmcmahon
 */

#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "ParseProperty.h"
#include "Element.h"
#include <vector>
#include <math.h>

struct ComputedSize doVerticalLayout(std::vector<struct Element*> children, double width, double height, bool isWidthSize, bool isHeightSize) {
	struct ComputedSize computedSize = {0, 0};
	struct Element* child;
	int i = 0;
	struct LayoutCoefficients  layoutCoefficients;
	struct ThreeCoefficients widthLayoutCoefficients, heightLayoutCoefficients, sandboxWidthLayoutCoefficients,
		sandboxHeightLayoutCoefficients, leftLayoutCoefficients, minWidthLayoutCoefficients, minHeightLayoutCoefficients;
	struct FourCoefficients topLayoutCoefficients;
	struct ComputedSize childSize;
	double	measuredWidth, measuredHeight, measuredSandboxHeight, measuredSandboxWidth, measuredLeft, measuredTop;
	std::string	pixelUnits = "px";
	std::vector<struct Element*> deferredLeftCalculations;
	double runningHeight = 0;
	int len = children.size();

	// Calculate size and position for the children
	for(i = 0; i < len; i++) {
	    child = children[i];

	    (*child)._measuredRunningHeight = runningHeight;

	    layoutCoefficients = (*child)._layoutCoefficients;
		widthLayoutCoefficients = layoutCoefficients.width;
		heightLayoutCoefficients = layoutCoefficients.height;
		sandboxWidthLayoutCoefficients = layoutCoefficients.sandboxWidth;
		sandboxHeightLayoutCoefficients = layoutCoefficients.sandboxHeight;
		leftLayoutCoefficients = layoutCoefficients.left;
		topLayoutCoefficients = layoutCoefficients.top;

		measuredWidth = widthLayoutCoefficients.x1 * width + widthLayoutCoefficients.x2;
		measuredHeight = heightLayoutCoefficients.x1 * height + heightLayoutCoefficients.x2 * (height - runningHeight) + heightLayoutCoefficients.x3;

		childSize = layoutNode(
							child,
							isNaN(measuredWidth) ? width : measuredWidth - (*child)._borderLeftWidth - (*child)._borderRightWidth,
							isNaN(measuredHeight) ? height : measuredHeight - (*child)._borderTopWidth - (*child)._borderBottomWidth,
							isNaN(measuredWidth),
							isNaN(measuredHeight));

		if (isNaN(measuredWidth)) {
			measuredWidth = childSize.width + (*child)._borderLeftWidth + (*child)._borderRightWidth;
		}

		if (isNaN(measuredHeight)) {
			measuredHeight = childSize.height + (*child)._borderTopWidth + (*child)._borderBottomWidth;
		}

		(*child)._measuredWidth = measuredWidth;
		(*child)._measuredHeight = measuredHeight;

		if (isWidthSize && leftLayoutCoefficients.x1 != 0) {
			deferredLeftCalculations.push_back(child);
		} else {
			measuredLeft = (*child)._measuredLeft = leftLayoutCoefficients.x1 * width + leftLayoutCoefficients.x2 * measuredWidth + leftLayoutCoefficients.x3;
			measuredSandboxWidth = (*child)._measuredSandboxWidth = sandboxWidthLayoutCoefficients.x1 * width + sandboxWidthLayoutCoefficients.x2 + measuredWidth + (isNaN(measuredLeft) ? 0 : measuredLeft);
												measuredSandboxWidth > computedSize.width && (computedSize.width = measuredSandboxWidth);
		}
		(*child)._measuredTop = topLayoutCoefficients.x1 * height + topLayoutCoefficients.x2 + runningHeight;

		measuredSandboxHeight = (*child)._measuredSandboxHeight = sandboxHeightLayoutCoefficients.x1 * height + sandboxHeightLayoutCoefficients.x2 + measuredHeight;

		runningHeight = (computedSize.height += (*child)._measuredSandboxHeight);
	}

	// Calculate the preliminary sandbox widths (missing left, since one of these widths may end up impacting all the lefts)
	len = deferredLeftCalculations.size();
	for(i = 0; i < len; i++) {
		child = deferredLeftCalculations[i];
		sandboxWidthLayoutCoefficients = (*child)._layoutCoefficients.sandboxWidth;
		measuredSandboxWidth = (*child)._measuredSandboxWidth = sandboxWidthLayoutCoefficients.x1 * width + sandboxWidthLayoutCoefficients.x2 + (*child)._measuredWidth;
											measuredSandboxWidth > computedSize.width && (computedSize.width = measuredSandboxWidth);
	}

	// Second pass, if necessary, to determine the left values
	for(i = 0; i < len; i++) {
		child = deferredLeftCalculations[i];

		leftLayoutCoefficients = (*child)._layoutCoefficients.left;
		sandboxWidthLayoutCoefficients = (*child)._layoutCoefficients.sandboxWidth;
		measuredWidth = (*child)._measuredWidth;
		measuredSandboxWidth = (*child)._measuredSandboxWidth;

		measuredSandboxWidth > computedSize.width && (computedSize.width = measuredSandboxWidth);
		measuredLeft = (*child)._measuredLeft = leftLayoutCoefficients.x1 * computedSize.width + leftLayoutCoefficients.x2 * measuredWidth + leftLayoutCoefficients.x3;
									(*child)._measuredSandboxWidth += (isNaN(measuredLeft) ? 0 : measuredLeft);
	}

	return computedSize;
}

void measureNodeForVerticalLayout(struct LayoutProperties layoutProperties, struct Element* element) {
	enum ValueType widthType = layoutProperties.width.valueType;
	double widthValue = layoutProperties.width.value;
	enum ValueType heightType = layoutProperties.height.valueType;
	double heightValue = layoutProperties.height.value;
	enum ValueType leftType = layoutProperties.left.valueType;
	double leftValue = layoutProperties.left.value;
	enum ValueType topType = layoutProperties.top.valueType;
	double topValue = layoutProperties.top.value;
	enum ValueType centerXType = layoutProperties.centerX.valueType;
	double centerXValue = layoutProperties.centerX.value;
	enum ValueType centerYType = layoutProperties.centerY.valueType;
	double centerYValue = layoutProperties.centerY.value;
	enum ValueType rightType = layoutProperties.right.valueType;
	double rightValue = layoutProperties.right.value;
	enum ValueType bottomType = layoutProperties.bottom.valueType;
	double bottomValue = layoutProperties.bottom.value;
	enum ValueType minWidthType = layoutProperties.minWidth.valueType;
	double minWidthValue = layoutProperties.minWidth.value;
	enum ValueType minHeightType = layoutProperties.minHeight.valueType;
	double minHeightValue = layoutProperties.minHeight.value;

	double x1 = 0;
	double x2 = 0;
	double x3 = 0;

	// Width rule evaluation
	if (widthType == Size) {
		x1 = x2 = NAN;
	} else if (widthType == Fill) {
		x1 = 1;
		if (leftType == Percent) {
			x1 -= leftValue;
		} else if (leftType == Fixed) {
			x2 = -leftValue;
		} else if (rightType == Percent) {
			x1 -= rightValue;
		} else if (rightType == Fixed) {
			x2 = -rightValue;
		}
	} else if (widthType == Percent) {
		x1 = widthValue;
	} else if (widthType == Fixed) {
		x2 = widthValue;
	} else if (leftType == Percent) {
		if (centerXType == Percent) {
			x1 = 2 * (centerXValue - leftValue);
		} else if (centerXType == Fixed) {
			x1 = -2 * leftValue;
			x2 = 2 * centerXValue;
		} else if (rightType == Percent) {
			x1 = 1 - leftValue - rightValue;
		} else if (rightType == Fixed) {
			x1 = 1 - leftValue;
			x2 = -rightValue;
		}
	} else if (leftType == Fixed) {
		if (centerXType == Percent) {
			x1 = 2 * centerXValue;
			x2 = -2 * leftValue;
		} else if (centerXType == Fixed) {
			x2 = 2 * (centerXValue - leftValue);
		} else if (rightType == Percent) {
			x1 = 1 - rightValue;
			x2 = -leftValue;
		} else if (rightType == Fixed) {
			x1 = 1;
			x2 = -rightValue - leftValue;
		}
	} else if (centerXType == Percent) {
		if (rightType == Percent) {
			x1 = 2 * (rightValue - centerXValue);
		} else if (rightType == Fixed) {
			x1 = -2 * centerXValue;
			x2 = 2 * rightValue;
		}
	} else if (centerXType == Fixed) {
		if (rightType == Percent) {
			x1 = 2 * rightValue;
			x2 = -2 * centerXValue;
		} else if (rightType == Fixed) {
			x2 = 2 * (rightValue - centerXValue);
		}
	}
	(*element)._layoutCoefficients.width.x1 = x1;
	(*element)._layoutCoefficients.width.x2 = x2;

	// Sandbox width/height rule evaluation
	(*element)._layoutCoefficients.sandboxWidth.x1 = rightType == Percent ? rightValue : 0;
	(*element)._layoutCoefficients.sandboxWidth.x2 = rightType == Fixed ? rightValue : 0;

	// Height rule calculation
	x1 = x2 = x3 = 0;
	if (heightType == Size) {
		x1 = x2 = x3 = NAN;
	} else if (heightType == Fill) {
		x2 = 1;
		topType == Percent && (x1 = -topValue);
		topType == Fixed && (x3 = -topValue);
		bottomType == Percent && (x1 = -bottomValue);
		bottomType == Fixed && (x3 = -bottomValue);
	} else if (heightType == Percent) {
		x1 = heightValue;
	} else if (heightType == Fixed) {
		x3 = heightValue;
	}
	(*element)._layoutCoefficients.height.x1 = x1;
	(*element)._layoutCoefficients.height.x2 = x2;
	(*element)._layoutCoefficients.height.x3 = x3;

	// Sandbox height rule calculation
	x1 = x2 = 0;
	topType == Percent && (x1 = topValue);
	topType == Fixed && (x2 = topValue);
	bottomType == Percent && (x1 += bottomValue);
	bottomType == Fixed && (x2 += bottomValue);
	(*element)._layoutCoefficients.sandboxHeight.x1 = x1;
	(*element)._layoutCoefficients.sandboxHeight.x2 = x2;

	// Left rule calculation
	x1 = x2 = x3 = 0;
	if (leftType == Percent) {
		x1 = leftValue;
	} else if(leftType == Fixed) {
		x3 = leftValue;
	} else if (centerXType == Percent) {
		x1 = centerXValue;
		x2 = -0.5;
	} else if (centerXType == Fixed) {
		x2 = -0.5;
		x3 = centerXValue;
	} else if (rightType == Percent) {
		x1 = 1 - rightValue;
		x2 = -1;
	} else if (rightType == Fixed) {
		x1 = 1;
		x2 = -1;
		x3 = -rightValue;
	} else {
		switch((*element)._defaultHorizontalAlignment) {
			case Center:
				x1 = 0.5;
				x2 = -0.5;
				break;
			case End:
				x1 = 1;
				x2 = -1;
				break;
		}
	}
	(*element)._layoutCoefficients.left.x1 = x1;
	(*element)._layoutCoefficients.left.x2 = x2;
	(*element)._layoutCoefficients.left.x3 = x3;

	// Top rule calculation
	(*element)._layoutCoefficients.top.x1 = topType == Percent ? topValue : 0;
	(*element)._layoutCoefficients.top.x2 = topType == Fixed ? topValue : 0;
}





