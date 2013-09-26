/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_COMMON_H_
#define TI_COMMON_H_

#include "Headers.h"

namespace Ti
{
namespace Layout
{
class Common
{
public:


	static bool isNaN(float);
	static ComputedSize layoutNode(struct Element*, double, double, bool, bool);

	static void measureNode(enum LayoutType type, struct LayoutProperties* properties, struct Element* element);
};

}
}
#endif /* COMMON_H_ */
