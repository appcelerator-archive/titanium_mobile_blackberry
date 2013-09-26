/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#include "Layout/Element.h"
#include "Layout/Composite.h"
#include "Layout/Horizontal.h"
#include "Layout/Vertical.h"

namespace Ti
{
namespace Layout
{

bool Common::isNaN(float value) {
  if (value != value)
    return true;
  else
    return false;
}

ComputedSize Common::layoutNode(struct Element* element, double width, double height, bool isWidthSize, bool isHeightSize) {
  ComputedSize computedSize;

  switch ((*element)._layoutType) {
    case Composite:
      computedSize = Composite::doCompositeLayout((*element)._children, width, height, isWidthSize, isHeightSize);
      break;
    case Horizontal:
      computedSize = Horizontal::doHorizontalLayout((*element)._children, width, height, isWidthSize, isHeightSize);
      break;
    case Vertical:
      computedSize = Vertical::doVerticalLayout((*element)._children, width, height, isWidthSize, isHeightSize);
      break;
  }

  return computedSize;
}

void Common::measureNode(enum LayoutType type, struct LayoutProperties* properties, struct Element* element) {
  switch (type) {
    case Composite:
    	Composite::measureNodeForCompositeLayout(*properties, element);
      break;
    case Horizontal:
    	Horizontal::measureNodeForHorizontalLayout(*properties, element);
      break;
    case Vertical:
    	 Vertical::measureNodeForVerticalLayout(*properties, element);
      break;
  }
}

}
}
