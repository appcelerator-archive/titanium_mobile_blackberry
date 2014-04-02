/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_ELEMENT_H_
#define TI_ELEMENT_H_

#include <string>
#include <vector>
#include "Headers.h"

namespace Ti
{
namespace Layout
{
class TiElement
{
public:


	static void elementInitialize(struct Element* element, enum LayoutType);
	static void addChildElement(struct Element* parent, struct Element* child);
	static void removeChildElement(struct Element* parent, struct Element* child);
};
}
}
#endif /* ELEMENT_H_ */
