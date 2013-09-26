/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include <stdio.h>
#include <stdlib.h>
#include "Layout/Common.h"
#include "Layout/ParseProperty.h"
#include "Layout/Element.h"
#include <vector>
#include <math.h>
#include <string.h>
#include <algorithm>

namespace Ti
{
namespace Layout
{

struct ComputedSize Horizontal::doHorizontalLayout(std::vector<struct Element*> children, double width, double height, bool isWidthSize, bool isHeightSize) {
	struct ComputedSize computedSize = {0, 0};
	struct Element* child;
	int i = 0;
	int j = 0;
	struct LayoutCoefficients  layoutCoefficients;
	struct ThreeCoefficients widthLayoutCoefficients, heightLayoutCoefficients, sandboxWidthLayoutCoefficients,
		sandboxHeightLayoutCoefficients, leftLayoutCoefficients, minWidthLayoutCoefficients, minHeightLayoutCoefficients;
	struct FourCoefficients topLayoutCoefficients;
	struct ComputedSize childSize;
	double	measuredWidth, measuredHeight, measuredSandboxHeight, measuredSandboxWidth, measuredLeft, measuredTop;
	std::string pixelUnits = "px";
	double runningHeight = 0;
	double runningWidth = 0;
	// ToDo Russ - remove hard coded c arrays
	Element* rows [200][200];
	Element* row[200];
	int elementsPerRow[200];
	double rowHeights[200];
	double rowHeight;
	std::vector<struct Element*> deferredTopCalculations;
	double deferHeight;
	double sizeHeight;
	double verticalAlignmentOffset = 0;
	int len = children.size();
	int rowLen = 0;
	int rowsLen = (len > 0 ) ? 1: 0;

	// Calculate horizontal size and position for the children
	for(i = 0; i < len; i++) {
	    child = children[i];
	    (*child)._measuredRunningWidth = runningWidth;

	    layoutCoefficients = (*child)._layoutCoefficients;
		widthLayoutCoefficients = layoutCoefficients.width;
		heightLayoutCoefficients = layoutCoefficients.height;
		sandboxWidthLayoutCoefficients = layoutCoefficients.sandboxWidth;
		leftLayoutCoefficients = layoutCoefficients.left;

		measuredWidth = widthLayoutCoefficients.x1 * width + widthLayoutCoefficients.x2 * (width - runningWidth) + widthLayoutCoefficients.x3;
		measuredHeight = heightLayoutCoefficients.x2 == 0 ? heightLayoutCoefficients.x1 * height + heightLayoutCoefficients.x3 : NAN;

		if (Common::isNaN(measuredWidth) || Common::isNaN(heightLayoutCoefficients.x1)) {

			childSize = Common::layoutNode(
				child,
				Common::isNaN(measuredWidth) ? width : measuredWidth - (*child)._borderLeftWidth - (*child)._borderRightWidth,
				Common::isNaN(measuredHeight) ? height : measuredHeight - (*child)._borderTopWidth - (*child)._borderBottomWidth,
				Common::isNaN(measuredWidth),
				Common::isNaN(measuredHeight));

			Common::isNaN(measuredWidth) && (measuredWidth = childSize.width + (*child)._borderLeftWidth + (*child)._borderRightWidth);
			Common::isNaN(heightLayoutCoefficients.x1) && (measuredHeight = childSize.height + (*child)._borderTopWidth + (*child)._borderBottomWidth);

			(*child)._childrenLaidOut = true;
			if (heightLayoutCoefficients.x2 != 0 && !Common::isNaN(heightLayoutCoefficients.x2)) {
				printf("Child of width SIZE and height FILL detected in a horizontal layout. Performance degradation may occur.");
				(*child)._childrenLaidOut = false;
			}
		} else {
			(*child)._childrenLaidOut = false;
		}

		(*child)._measuredWidth = measuredWidth;
		(*child)._measuredHeight = measuredHeight;

		measuredSandboxWidth = (*child)._measuredSandboxWidth = sandboxWidthLayoutCoefficients.x1 * width + sandboxWidthLayoutCoefficients.x2 + measuredWidth;

		measuredLeft = leftLayoutCoefficients.x1 * width + leftLayoutCoefficients.x2 + runningWidth;

		if (!isWidthSize && width > 0 && (int)(measuredSandboxWidth + runningWidth) > width) {
			rowsLen++;
			rowLen = 0;
			measuredLeft -= runningWidth;
			runningWidth = 0;
		}

		(*child)._measuredLeft = measuredLeft;
		rows[rowsLen - 1][rowLen] = child;
		rowLen++;
		elementsPerRow[rowsLen -1] = rowLen;
		runningWidth += measuredSandboxWidth;
		runningWidth > computedSize.width && (computedSize.width = runningWidth);
	}

	// Calculate vertical size and position for the children
	len = rowsLen;
	for(i = 0; i < len; i++) {
		rowLen = elementsPerRow[i];
		memcpy(&row, &rows[i], rowLen * sizeof(struct Element*));
		rowHeight = 0;
		for (j = 0; j < rowLen; j++) {
			child = row[j];

			layoutCoefficients = (*child)._layoutCoefficients;
			topLayoutCoefficients = layoutCoefficients.top;
			heightLayoutCoefficients = layoutCoefficients.height;
			sandboxHeightLayoutCoefficients = layoutCoefficients.sandboxHeight;
			measuredHeight = (*child)._measuredHeight;
			if (Common::isNaN(measuredHeight)) {
			  (*child)._measuredHeight = measuredHeight = heightLayoutCoefficients.x1 *
				height + heightLayoutCoefficients.x2 * (height - runningHeight) + heightLayoutCoefficients.x3;
			}

			if (!(*child)._childrenLaidOut) {
				measuredWidth = (*child)._measuredWidth;
				(*child)._childrenLaidOut = true;
				Common::layoutNode(
					child,
					Common::isNaN(measuredWidth) ? width : measuredWidth - (*child)._borderLeftWidth - (*child)._borderRightWidth,
					Common::isNaN(measuredHeight) ? height : measuredHeight - (*child)._borderTopWidth - (*child)._borderBottomWidth,
					Common::isNaN(measuredWidth),
					Common::isNaN(measuredHeight));
			}

			if (topLayoutCoefficients.x2 != 0) {
				deferredTopCalculations.push_back(child);
				measuredTop = runningHeight; // Temporary for use in calculating row height
			} else {
				(*child)._measuredTop = measuredTop = topLayoutCoefficients.x1 * height +
					topLayoutCoefficients.x3 * measuredHeight + topLayoutCoefficients.x4 + runningHeight;
			}

			(*child)._measuredSandboxHeight = measuredSandboxHeight = sandboxHeightLayoutCoefficients.x1 * height + sandboxHeightLayoutCoefficients.x2 + measuredHeight + measuredTop - runningHeight;
			rowHeight < measuredSandboxHeight && (rowHeight = measuredSandboxHeight);
		}
		rowHeights[i] = rowHeight;
		runningHeight += rowHeight;
	}

	// Second pass, if necessary, to determine the top values
	runningHeight = 0;
	len = rowsLen;
	for(i = 0; i < len; i++) {
		rowLen = elementsPerRow[i];
		memcpy(&row, &rows[i], rowLen * sizeof(struct Element*));
		rowHeight = rowHeights[i];
		for (j = 0; j < rowLen; j++) {
			child = row[j];
			(*child)._measuredRunningHeight = runningHeight;
			(*child)._measuredRowHeight = rowHeight;

			if (std::find(deferredTopCalculations.begin(), deferredTopCalculations.end(), child) != deferredTopCalculations.end()) {
				measuredHeight = (*child)._measuredHeight;
				topLayoutCoefficients = (*child)._layoutCoefficients.top;
				(*child)._measuredTop = topLayoutCoefficients.x1 * height + topLayoutCoefficients.x2 * rowHeight + topLayoutCoefficients.x3 * measuredHeight + topLayoutCoefficients.x4 + runningHeight;
			}
		}
		runningHeight += rowHeight;
	}

	computedSize.height = runningHeight;

	return computedSize;
}

static void setDefaultHorizontalWidthType(struct LayoutProperties layoutProperties, enum ValueType* measuredWidthType) {
	if (*measuredWidthType == None) {
		*measuredWidthType = layoutProperties.defaultWidthType;
	}
}

static void setDefaultHorizontalHeightType(struct LayoutProperties layoutProperties, enum ValueType* measuredHeightType) {
	if (*measuredHeightType == None) {
		*measuredHeightType = layoutProperties.defaultHeightType;
	}
}

void Horizontal::measureNodeForHorizontalLayout(struct LayoutProperties layoutProperties, struct Element* element) {
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

	setDefaultHorizontalWidthType(layoutProperties, &widthType);
	setDefaultHorizontalHeightType(layoutProperties, &heightType);

	double x1 = 0;
	double x2 = 0;
	double x3 = 0;
	double x4 = 0;

	// Width rule calculation
	if (widthType == Size) {
		x1 = x2 = x3 = NAN;
	} else if (widthType == Fill) {
		x2 = 1;
		leftType == Percent && (x1 = -leftValue);
		leftType == Fixed && (x3 = -leftValue);
		rightType == Percent && (x1 = -rightValue);
		rightType == Fixed && (x3 = -rightValue);
	} else if (widthType == Percent) {
		x1 = widthValue;
	} else if (widthType == Fixed) {
		x3 = widthValue;
	}
	(*element)._layoutCoefficients.width.x1 = x1;
	(*element)._layoutCoefficients.width.x2 = x2;
	(*element)._layoutCoefficients.width.x3 = x3;

	// Sandbox width rule calculation
	x1 = x2 = 0;
	leftType == Percent && (x1 = leftValue);
	leftType == Fixed && (x2 = leftValue);
	rightType == Percent && (x1 += rightValue);
	rightType == Fixed && (x2 += rightValue);
	(*element)._layoutCoefficients.sandboxWidth.x1 = x1;
	(*element)._layoutCoefficients.sandboxWidth.x2 = x2;

	// Height rule calculation
	x1 = x2 = x3 = 0;
	if (heightType == Size) {
		x1 = x2 = x3 = NAN;
	} else if (heightType == Fill) {
		x2 = 1;
		topType == Percent && (x1 = -topValue);
		topType == Fixed && (x3 = -topValue);
	} else if (heightType == Percent) {
		x1 = heightValue;
	} else if (heightType == Fixed) {
		x3 = heightValue;
	}
	(*element)._layoutCoefficients.height.x1 = x1;
	(*element)._layoutCoefficients.height.x2 = x2;
	(*element)._layoutCoefficients.height.x3 = x3;

	// Sandbox height rule calculation
	(*element)._layoutCoefficients.sandboxHeight.x1 = bottomType == Percent ? bottomValue : 0;
	(*element)._layoutCoefficients.sandboxHeight.x2 = bottomType == Fixed ? bottomValue : 0;

	// Left rule calculation
	(*element)._layoutCoefficients.left.x1 = leftType == Percent ? leftValue : 0;
	(*element)._layoutCoefficients.left.x2 = leftType == Fixed ? leftValue : 0;

	// Top rule calculation
	x1 = x2 = x3 = x4 = 0;
	if (topType == Percent) {
		x1 = topValue;
	} else if(topType == Fixed) {
		x4 = topValue;
	} else if(bottomType == Percent) {
		x1 = 1 - bottomValue;
		x3 = -1;
	} else if(bottomType == Fixed) {
		x1 = 1;
		x3 = -1;
		x4 = -bottomValue;
	} else {
		switch((*element)._defaultRowAlignment) {
			case Center:
				x2 = 0.5;
				x3 = -0.5;
				break;
			case End:
				x2 = 1;
				x3 = -1;
				break;
		}
	}
	(*element)._layoutCoefficients.top.x1 = x1;
	(*element)._layoutCoefficients.top.x2 = x2;
	(*element)._layoutCoefficients.top.x3 = x3;
	(*element)._layoutCoefficients.top.x4 = x4;
}
}
}
