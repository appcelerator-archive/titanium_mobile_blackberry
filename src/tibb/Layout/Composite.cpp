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
#include <stack>
#include <math.h>

struct ComputedSize doCompositeLayout(std::vector<struct Element*> children, double width, double height, bool isWidthSize, bool isHeightSize) {
	struct ComputedSize computedSize = {0, 0};
	struct Element* child;
	int i = 0;
	struct LayoutCoefficients  layoutCoefficients;
	struct ThreeCoefficients widthLayoutCoefficients, heightLayoutCoefficients, sandboxWidthLayoutCoefficients,
	    sandboxHeightLayoutCoefficients, leftLayoutCoefficients, minWidthLayoutCoefficients, minHeightLayoutCoefficients;
	struct FourCoefficients topLayoutCoefficients;
	struct ComputedSize childSize;
	double	measuredWidth, measuredHeight, measuredSandboxHeight, measuredSandboxWidth, measuredLeft, measuredTop;
	std::vector<struct Element*> deferredLeftCalculations;
	std::vector<struct Element*> deferredTopCalculations;
	int len = children.size();

	// Calculate size and position for the children
	for(i = 0; i < len; i++) {
	    child = children[i];
		layoutCoefficients = (*child)._layoutCoefficients;
		widthLayoutCoefficients = layoutCoefficients.width;
		minWidthLayoutCoefficients = layoutCoefficients.minWidth;
		heightLayoutCoefficients = layoutCoefficients.height;
		minHeightLayoutCoefficients = layoutCoefficients.minHeight;
		sandboxWidthLayoutCoefficients = layoutCoefficients.sandboxWidth;
		sandboxHeightLayoutCoefficients = layoutCoefficients.sandboxHeight;
		leftLayoutCoefficients = layoutCoefficients.left;
		topLayoutCoefficients = layoutCoefficients.top;

		measuredWidth = widthLayoutCoefficients.x1 * width + widthLayoutCoefficients.x2;
		if (!(isNaN(minWidthLayoutCoefficients.x1))) {
			measuredWidth = std::max(measuredWidth, minWidthLayoutCoefficients.x1 * width + minWidthLayoutCoefficients.x2);
		}

		if (!(isNaN(minHeightLayoutCoefficients.x1))) {
			measuredHeight = std::max(measuredHeight, minHeightLayoutCoefficients.x1 * height + minHeightLayoutCoefficients.x2);
		}

		childSize = layoutNode(child,
                isNaN(measuredWidth) ? width : measuredWidth - (*child)._borderLeftWidth - (*child)._borderRightWidth,
				isNaN(measuredHeight) ? height : measuredHeight - (*child)._borderTopWidth - (*child)._borderBottomWidth,
				isNaN(measuredWidth),
				isNaN(measuredHeight));

		if (isNaN(measuredWidth)) {
			measuredWidth = childSize.width + (*child)._borderLeftWidth + (*child)._borderRightWidth;
			if (!(isNaN(minWidthLayoutCoefficients.x1))) {
				measuredWidth = std::max(measuredWidth, minWidthLayoutCoefficients.x1 * width + minWidthLayoutCoefficients.x2);
			}
		}

		if (isNaN(measuredHeight)) {
			measuredHeight = childSize.height + (*child)._borderTopWidth + (*child)._borderBottomWidth;
			if (!(isNaN(minHeightLayoutCoefficients.x1))) {
				measuredHeight = std::max(measuredHeight, minHeightLayoutCoefficients.x1 * height + minHeightLayoutCoefficients.x2);
			}
		}

		if (isWidthSize && leftLayoutCoefficients.x1 != 0) {
			deferredLeftCalculations.push_back(child);
		} else {
			measuredLeft = leftLayoutCoefficients.x1 * width + leftLayoutCoefficients.x2 * measuredWidth + leftLayoutCoefficients.x3;
		}
		if (isHeightSize && topLayoutCoefficients.x1 != 0) {
			deferredTopCalculations.push_back(child);
		} else {
			measuredTop = topLayoutCoefficients.x1 * height + topLayoutCoefficients.x2 * measuredHeight + topLayoutCoefficients.x3;
		}

		(*child)._measuredSandboxWidth = measuredSandboxWidth = sandboxWidthLayoutCoefficients.x1 * height + sandboxWidthLayoutCoefficients.x2 + measuredWidth + (isNaN(measuredLeft) ? 0 : measuredLeft);
		(*child)._measuredSandboxHeight = measuredSandboxHeight = sandboxHeightLayoutCoefficients.x1 * height + sandboxHeightLayoutCoefficients.x2 + measuredHeight + (isNaN(measuredTop) ? 0 : measuredTop);

		// Update the size of the component
		measuredSandboxWidth > computedSize.width && (computedSize.width = measuredSandboxWidth);
		measuredSandboxHeight > computedSize.height && (computedSize.height = measuredSandboxHeight);

		(*child)._measuredWidth = measuredWidth;
		(*child)._measuredHeight = measuredHeight;
		(*child)._measuredLeft = measuredLeft;
		(*child)._measuredTop = measuredTop;
    }

	// Second pass, if necessary, to determine the left/top values
	len = deferredLeftCalculations.size();
	for(i = 0; i < len; i++) {
		child = deferredLeftCalculations[i];
		leftLayoutCoefficients = (*child)._layoutCoefficients.left;
		sandboxWidthLayoutCoefficients = (*child)._layoutCoefficients.sandboxWidth;
		(*child)._measuredLeft = measuredLeft = leftLayoutCoefficients.x1 * computedSize.width + leftLayoutCoefficients.x2 * measuredWidth + leftLayoutCoefficients.x3;
		(*child)._measuredSandboxWidth = measuredSandboxWidth = sandboxWidthLayoutCoefficients.x1 * height + sandboxWidthLayoutCoefficients.x2 + (*child)._measuredWidth + measuredLeft;

		// Update the size of the component
		measuredSandboxWidth = (*child)._measuredSandboxWidth;
		measuredSandboxWidth > computedSize.width && (computedSize.width = measuredSandboxWidth);
	}
	len = deferredTopCalculations.size();
	for(i = 0; i < len; i++) {
		child = deferredTopCalculations[i];
		topLayoutCoefficients = (*child)._layoutCoefficients.top;
		sandboxHeightLayoutCoefficients = (*child)._layoutCoefficients.sandboxHeight;
		(*child)._measuredTop = measuredTop = topLayoutCoefficients.x1 * computedSize.height + topLayoutCoefficients.x2 * measuredHeight + topLayoutCoefficients.x3;
		(*child)._measuredSandboxHeight = measuredSandboxHeight = sandboxHeightLayoutCoefficients.x1 * height + sandboxHeightLayoutCoefficients.x2 + (*child)._measuredHeight + measuredTop;

		// Update the size of the component
		measuredSandboxHeight = (*child)._measuredSandboxHeight;
		measuredSandboxHeight > computedSize.height && (computedSize.height = measuredSandboxHeight);
	}

	/*
	// Position the children
	len = children.length;
	for(i = 0; i < len; i++) {
		child = children[i];
		if (child._markedForLayout) {
			UI._elementLayoutCount++;
			style = child.domNode.style;
			style.zIndex = child.zIndex;
			style.left = round(child._measuredLeft) + pixelUnits;
			style.top = round(child._measuredTop) + pixelUnits;
			style.width = round(child._measuredWidth - child._borderLeftWidth - child._borderRightWidth) + pixelUnits;
			style.height = round(child._measuredHeight - child._borderTopWidth - child._borderBottomWidth) + pixelUnits;
			child._markedForLayout = false;
			child.fireEvent("postlayout");
		}
	}
	*/

	return computedSize;
}

void measureNodeForCompositeLayout(struct LayoutProperties layoutProperties, struct Element* element) {
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

	double x1 = 0;
	double x2 = 0;
	double x3 = 0;
	if (widthType == size) {
		x1 = x2 = NAN;
	} else if (widthType == fill) {
		x1 = 1;
		if (widthType == percent) {
			x1 -= leftValue;
		} else if (widthType == fixed) {
			x2 = -leftValue;
		} else if (rightType == percent) {
			x1 -= rightValue;
		} else if (rightType == fixed) {
			x2 = -rightValue;
		}
	} else if (widthType == percent) {
		x1 = widthValue;
	} else if (widthType == fixed) {
		x2 = widthValue;
	} else if (widthType == percent) {
		if (centerXType == percent) {
			x1 = 2 * (centerXValue - leftValue);
		} else if (centerXType == fixed) {
			x1 = -2 * leftValue;
			x2 = 2 * centerXValue;
		} else if (rightType == percent) {
			x1 = 1 - leftValue - rightValue;
		} else if (rightType == fixed) {
			x1 = 1 - leftValue;
			x2 = -rightValue;
		}
	} else if (widthType == fixed) {
		if (centerXType == percent) {
			x1 = 2 * centerXValue;
			x2 = -2 * leftValue;
		} else if (centerXType == fixed) {
			x2 = 2 * (centerXValue - leftValue);
		} else if (rightType == percent) {
			x1 = 1 - rightValue;
			x2 = -leftValue;
		} else if (rightType == fixed) {
			x1 = 1;
			x2 = -rightValue - leftValue;
		}
	} else if (centerXType == percent) {
		if (rightType == percent) {
			x1 = 2 * (rightValue - centerXValue);
		} else if (rightType == fixed) {
			x1 = -2 * centerXValue;
			x2 = 2 * rightValue;
		}
	} else if (centerXType == fixed) {
		if (rightType == percent) {
			x1 = 2 * rightValue;
			x2 = -2 * centerXValue;
		} else if (rightType == fixed) {
			x2 = 2 * (rightValue - centerXValue);
		}
	}

	(*element)._layoutCoefficients.width.x1 = x1;
	(*element)._layoutCoefficients.width.x2 = x2;

	x1 = x2 = 0;
	if (heightType == size) {
		x1 = x2 = NAN;
	} else if (heightType == fill) {
		x1 = 1;
		if (topType == percent) {
			x1 -= topValue;
		} else if (topType == fixed) {
			x2 = -topValue;
		} else if (bottomType == percent) {
			x1 -= bottomValue;
		} else if (bottomType == fixed) {
			x2 = -bottomValue;
		}
	} else if (heightType == percent) {
		x1 = heightValue;
	} else if (heightType == fixed) {
		x2 = heightValue;
	} else if (topType == percent) {
		if (centerYType == percent) {
			x1 = 2 * (centerYValue - topValue);
		} else if (centerYType == fixed) {
			x1 = -2 * topValue;
			x2 = 2 * centerYValue;
		} else if (bottomType == percent) {
			x1 = 1 - topValue - bottomValue;
		} else if (bottomType == fixed) {
			x1 = 1 - topValue;
			x2 = -bottomValue;
		}
	} else if (topType == fixed) {
		if (centerYType == percent) {
			x1 = 2 * centerYValue;
			x2 = -2 * topValue;
		} else if (centerYType == fixed) {
			x2 = 2 * (centerYValue - topValue);
		} else if (bottomType == percent) {
			x1 = 1 - bottomValue;
			x2 = -topValue;
		} else if (bottomType == fixed) {
			x1 = 1;
			x2 = -bottomValue - topValue;
		}
	} else if (centerYType == percent) {
		if (bottomType == percent) {
			x1 = 2 * (bottomValue - centerYValue);
		} else if (bottomType == fixed) {
			x1 = -2 * centerYValue;
			x2 = 2 * bottomValue;
		}
	} else if (centerYType == fixed) {
		if (bottomType == percent) {
			x1 = 2 * bottomValue;
			x2 = -2 * centerYValue;
		} else if (bottomType == fixed) {
			x2 = 2 * (bottomValue - centerYValue);
		}
	}

	(*element)._layoutCoefficients.width.x1 = x1;
	(*element)._layoutCoefficients.width.x2 = x2;

	x1 = x2 = x3 = 0;
	if (minWidthType == size) {
		x1 = x2 = NAN;
	} else if (minWidthType == fill) {
		x1 = 1;
		if (leftType == percent) {
			x1 -= leftValue;
		} else if (leftType == fixed) {
			x2 = -leftValue;
		} else if (rightType == percent) {
			x1 -= rightValue;
		} else if (rightType == fixed) {
			x2 = -rightValue;
		}
	} else if (minWidthType == percent) {
		x1 = minWidthValue;
	} else if (minWidthType == fixed) {
		x2 = minWidthValue;
	} else {
		x1 = x2 = x3 = NAN;
	}

	(*element)._layoutCoefficients.minWidth.x1 = x1;
    (*element)._layoutCoefficients.minWidth.x2 = x2;
    (*element)._layoutCoefficients.minWidth.x3 = x3;

    x1 = x2 = x3 = 0;
	if (heightType == size) {
		x1 = x2 = NAN;
	} else if (heightType == fill) {
		x1 = 1;
		if (topType == percent) {
			x1 -= topValue;
		} else if (topType == fixed) {
			x2 = -topValue;
		} else if (bottomType == percent) {
			x1 -= bottomValue;
		} else if (bottomType == fixed) {
			x2 = -bottomValue;
		}
	} else if (heightType == percent) {
		x1 = heightValue;
	} else if (heightType == fixed) {
		x2 = heightValue;
	} else {
		x1 = x2 = x3 = NAN;
	}

	(*element)._layoutCoefficients.minHeight.x1 = x1;
	(*element)._layoutCoefficients.minHeight.x2 = x2;
	(*element)._layoutCoefficients.minHeight.x3 = x3;

	x1 = x2 = x3 = 0;
	if (leftType == percent) {
		x1 = leftValue;
	} else if(leftType == fixed) {
		x3 = leftValue;
	} else if (centerXType == percent) {
		x1 = centerXValue;
		x2 = -0.5;
	} else if (centerXType == fixed) {
		x2 = -0.5;
		x3 = centerXValue;
	} else if (rightType == percent) {
		x1 = 1 - rightValue;
		x2 = -1;
	} else if (rightType == fixed) {
		x1 = 1;
		x2 = -1;
		x3 = -rightValue;
	} else {
		switch((*element)._defaultHorizontalAlignment) {
			case center:
				x1 = 0.5;
				x2 = -0.5;
				break;
			case end:
				x1 = 1;
				x2 = -1;
			break;
		}
	}

	(*element)._layoutCoefficients.left.x1 = x1;
    (*element)._layoutCoefficients.left.x2 = x2;
	(*element)._layoutCoefficients.left.x3 = x3;

	x1 = x2 = x3 = 0;
	if (topType == percent) {
		x1 = topValue;
	} else if(topType == fixed) {
		x3 = topValue;
	} else if (centerYType == percent) {
		x1 = centerYValue;
		x2 = -0.5;
	} else if (centerYType == fixed) {
		x2 = -0.5;
		x3 = centerYValue;
	} else if (bottomType == percent) {
		x1 = 1 - bottomValue;
		x2 = -1;
	} else if (bottomType == fixed) {
		x1 = 1;
		x2 = -1;
		x3 = -bottomValue;
	} else {
		switch((*element)._defaultVerticalAlignment) {
			case center:
				x1 = 0.5;
				x2 = -0.5;
				break;
			case end:
				x1 = 1;
				x2 = -1;
				break;
		}
	}

	(*element)._layoutCoefficients.top.x1 = x1;
	(*element)._layoutCoefficients.top.x2 = x2;
    (*element)._layoutCoefficients.top.x3 = x3;

	// Sandbox width/height rule evaluation
	(*element)._layoutCoefficients.sandboxWidth.x1 = (rightType == percent ? rightValue : 0);
	(*element)._layoutCoefficients.sandboxWidth.x2 = (rightType == fixed ? rightValue : 0);
	(*element)._layoutCoefficients.sandboxHeight.x1 = (bottomType == percent ? bottomValue : 0);
	(*element)._layoutCoefficients.sandboxHeight.x2 = (bottomType == fixed ? bottomValue : 0);
}
