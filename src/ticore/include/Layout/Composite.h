/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef COMPOSITE_H_
#define COMPOSITE_H_

#include "Headers.h"

namespace Ti
{
namespace Layout
{
class Composite
{
public:
	static struct ComputedSize doCompositeLayout(std::vector<struct Element*>, double, double, bool, bool);
	static void measureNodeForCompositeLayout(struct LayoutProperties, struct Element*);
};
}
}
#endif /* COMPOSITE_H_ */
