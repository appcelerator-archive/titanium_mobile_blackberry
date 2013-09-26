/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#ifndef VERTICAL_H_
#define VERTICAL_H_

#include "Headers.h"

namespace Ti
{
namespace Layout
{
class Vertical
{
public:
	static struct ComputedSize doVerticalLayout(std::vector<struct Element*>, double, double, bool, bool);
	static void measureNodeForVerticalLayout(struct LayoutProperties, struct Element*);
};
}
}
#endif /* VERTICAL_H_ */
