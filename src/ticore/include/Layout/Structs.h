/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#ifndef TI_LAYOUT_STRUCTS_H_
#define TI_LAYOUT_STRUCTS_H_

#include <vector>

namespace Ti
{
namespace Layout
{

enum LayoutType {Composite = 0, Horizontal, Vertical};
enum ElementAlignment {Start = 0, Center, End};
enum ValueName {
	Top = 0,
	Bottom,
	Left,
	Right,
	Width,
	MinWidth,
	Height,
	MinHeight,
	CenterX,
	CenterY
};
enum ValueType {
	Fill = 1,
	Size = 2,
	Percent = 3,
	Defer = 4,
	Auto = 5,
	Fixed = 0,
	None = -1
};

struct ComputedSize {
	double width;
	double height;
};

struct ThreeCoefficients {
	double x1;
	double x2;
	double x3;
};

struct FourCoefficients {
	double x1;
	double x2;
	double x3;
	double x4;
};

struct LayoutCoefficients {
	struct ThreeCoefficients width;
	struct ThreeCoefficients minWidth;
	struct ThreeCoefficients sandboxWidth;
	struct ThreeCoefficients height;
	struct ThreeCoefficients minHeight;
	struct ThreeCoefficients sandboxHeight;
	struct ThreeCoefficients left;
	struct FourCoefficients top;
};

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
	enum ElementAlignment _defaultRowAlignment;
	enum ElementAlignment _defaultHorizontalAlignment;
	enum ElementAlignment _defaultVerticalAlignment;
	double _measuredRunningHeight;
	double _measuredRunningWidth;
	double _measuredRowHeight;
	bool _childrenLaidOut;
};

struct layoutProp {
	// fill = UI.FILL, size = UI.SIZE, percent = values containing %, fixed = everything else
	enum ValueType valueType;
	float value;
};

struct LayoutProperties {
	struct layoutProp top;
	struct layoutProp bottom;
	struct layoutProp left;
	struct layoutProp right;
	struct layoutProp width;
	struct layoutProp minWidth;
	struct layoutProp height;
	struct layoutProp minHeight;
	struct layoutProp centerX;
	struct layoutProp centerY;
	enum ValueType defaultWidthType;
	enum ValueType defaultHeightType;
};

struct Node {
	struct Node *parent;
	struct Node *prev, *next;
	struct Node *firstChild, *lastChild;
	struct Element element;
	struct LayoutProperties properties;
	int flags;

	void(*onLayout)(struct Node*);
	void* data;
};
struct InputProperty {
	ValueName name;
	std::string value;
};



}
}

#endif
