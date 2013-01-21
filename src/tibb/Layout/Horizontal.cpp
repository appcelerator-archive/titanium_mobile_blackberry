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

struct ComputedSize doHorizontalLayout(std::vector<struct Element*> children, double width, double height, bool isWidthSize, bool isHeightSize) {
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
	std::vector<std::vector> rows;
	std::vector<struct Element*> row;
	std::vector<double> rowHeights;
	double rowHeight;
	std::vector<struct Element*> deferredTopCalculations;
	double deferHeight;
	double sizeHeight;
	double verticalAlignmentOffset = 0;
	int len = children.size();
	int rowLen;

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

		if (isNaN(measuredWidth) || isNaN(heightLayoutCoefficients.x1)) {

			childSize = layoutNode(
				child,
				isNaN(measuredWidth) ? width : measuredWidth - (*child)._borderLeftWidth - (*child)._borderRightWidth,
				isNaN(measuredHeight) ? height : measuredHeight - (*child)._borderTopWidth - (*child)._borderBottomWidth,
				isNaN(measuredWidth),
				isNaN(measuredHeight));

			isNaN(measuredWidth) && (measuredWidth = childSize.width + (*child)._borderLeftWidth + (*child)._borderRightWidth);
			isNaN(heightLayoutCoefficients.x1) && (measuredHeight = childSize.height + (*child)._borderTopWidth + (*child)._borderBottomWidth);

			(*child)._childrenLaidOut = true;
			if (heightLayoutCoefficients.x2 != 0 && !isNaN(heightLayoutCoefficients.x2)) {
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
		if (!isWidthSize && floor(measuredSandboxWidth + runningWidth) > std::ceil(width)) {
			measuredLeft -= runningWidth;
			runningWidth = 0;
		}
		(*child)._measuredLeft = measuredLeft;
		rows[rows.length - 1].push_back(child);
		runningWidth += measuredSandboxWidth;
		runningWidth > computedSize.width && (computedSize.width = runningWidth);
	}

	// Calculate vertical size and position for the children
	len = rows.size();
	for(i = 0; i < len; i++) {
		row = rows[i];
		rowHeight = 0;
		rowLen = row.size();
		for (j = 0; j < rowLen; j++) {
			child = row[j];

			layoutCoefficients = (*child)._layoutCoefficients;
			topLayoutCoefficients = layoutCoefficients.top;
			heightLayoutCoefficients = layoutCoefficients.height;
			sandboxHeightLayoutCoefficients = layoutCoefficients.sandboxHeight;
			measuredHeight = (*child)._measuredHeight;
			if (isNaN(measuredHeight)) {
			  (*child)._measuredHeight = measuredHeight = heightLayoutCoefficients.x1 *
				height + heightLayoutCoefficients.x2 * (height - runningHeight) + heightLayoutCoefficients.x3;
			}

			if (!(*child)._childrenLaidOut) {
				measuredWidth = (*child)._measuredWidth;
				(*child)._childrenLaidOut = true;
				layoutNode(
					child,
					isNaN(measuredWidth) ? width : measuredWidth - (*child)._borderLeftWidth - (*child)._borderRightWidth,
					isNaN(measuredHeight) ? height : measuredHeight - (*child)._borderTopWidth - (*child)._borderBottomWidth,
					isNaN(measuredWidth),
					isNaN(measuredHeight));
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
		rowHeights.push_back(rowHeight);
		runningHeight += rowHeight;
	}

	// Second pass, if necessary, to determine the top values
	runningHeight = 0;
	len = rows.size();
	for(i = 0; i < len; i++) {
		row = rows[i];
		rowHeight = rowHeights[i];
		rowLen = row.size();
		for (j = 0; j < rowLen; j++) {
			child = row[j];
			(*child)._measuredRunningHeight = runningHeight;
			(*child)._measuredRowHeight = rowHeight;

			auto result = std::find(deferredTopCalculations.begin(),
					deferredTopCalculations.end(), child);
			if (result == deferredTopCalculations.end()) {
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

void measureNodeForHorizontalLayout(struct LayoutProperties layoutProperties, struct Element* element) {
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

	// Width rule calculation
	if (widthType == size) {
		x1 = x2 = x3 = NAN;
	} else if (widthType == fill) {
		x2 = 1;
		leftType == percent && (x1 = -leftValue);
		leftType == fixed && (x3 = -leftValue);
		rightType == percent && (x1 = -rightValue);
		rightType == fixed && (x3 = -rightValue);
	} else if (widthType == percent) {
		x1 = widthValue;
	} else if (widthType == fixed) {
		x3 = widthValue;
	}
	widthLayoutCoefficients.x1 = x1;
	widthLayoutCoefficients.x2 = x2;
	widthLayoutCoefficients.x3 = x3;

	// Sandbox width rule calculation
	x1 = x2 = 0;
	leftType == percent && (x1 = leftValue);
	leftType == fixed && (x2 = leftValue);
	rightType == percent && (x1 += rightValue);
	rightType == fixed && (x2 += rightValue);
	sandboxWidthLayoutCoefficients.x1 = x1;
	sandboxWidthLayoutCoefficients.x2 = x2;

	// Height rule calculation
	x1 = x2 = x3 = 0;
	if (heightType == size) {
		x1 = x2 = x3 = NAN;
	} else if (heightType == fill) {
		x2 = 1;
		topType == percent && (x1 = -topValue);
		topType == fixed && (x3 = -topValue);
	} else if (heightType == percent) {
		x1 = heightValue;
	} else if (heightType == fixed) {
		x3 = heightValue;
	}
	heightLayoutCoefficients.x1 = x1;
	heightLayoutCoefficients.x2 = x2;
	heightLayoutCoefficients.x3 = x3;

	// Sandbox height rule calculation
	sandboxHeightLayoutCoefficients.x1 = bottomType == percent ? bottomValue : 0;
	sandboxHeightLayoutCoefficients.x2 = bottomType == fixed ? bottomValue : 0;

	// Left rule calculation
	leftLayoutCoefficients.x1 = leftType == percent ? leftValue : 0;
	leftLayoutCoefficients.x2 = leftType == fixed ? leftValue : 0;

	// Top rule calculation
	x1 = x2 = x3 = x4 = 0;
	if (topType == percent) {
		x1 = topValue;
	} else if(topType == fixed) {
		x4 = topValue;
	} else if(bottomType == percent) {
		x1 = 1 - bottomValue;
		x3 = -1;
	} else if(bottomType == fixed) {
		x1 = 1;
		x3 = -1;
		x4 = -bottomValue;
	} else {
		switch((*element)._defaultRowAlignment) {
			case center:
				x2 = 0.5;
				x3 = -0.5;
				break;
			case end:
				x2 = 1;
				x3 = -1;
				break;
		}
	}
	topLayoutCoefficients.x1 = x1;
	topLayoutCoefficients.x2 = x2;
	topLayoutCoefficients.x3 = x3;
	topLayoutCoefficients.x4 = x4;
}
