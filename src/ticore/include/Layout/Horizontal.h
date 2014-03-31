/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_HORIZONTAL_H_
#define TI_HORIZONTAL_H_

#include "Headers.h"

namespace Ti
{
namespace Layout
{
class Horizontal
{
public:
	static struct ComputedSize doHorizontalLayout(std::vector<struct Element*>, double, double, bool, bool);
	static void measureNodeForHorizontalLayout(struct LayoutProperties, struct Element*);

};
}
}
#endif /* HORIZONTAL_H_ */
